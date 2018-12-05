#include "SimpleTimer.h"
#include "NecromancerEntity.h"
#include "Group.h"
#include "NecromancerSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaNecromancerStates.h"
#include "ShakeInfo.h"
#include "CollisionManager.h"
#include "World.h"
#include "Level.h"
NecromancerEntity::NecromancerEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo, false)
{
	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 20.0f, 46.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x -10, mPosition.y-26.0f, mPosition.z+0.01, 1.0f), glm::vec2(40.0f, 92.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	myAnimatedSprite = new NecromancerSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1), glm::vec2(204, 122), TextureMan->GetTexture("necromancer"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);
	//mySprite->Add(myPlayerAABB);
	myAnimatedSprite->SetAnimation("NecromancerRun");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
	myStateMachine = new StateMachine<NecromancerEntity>(this);

	myStateMachine->setCurrentState(NecromancerIdle::Instance());
	myStateMachine->changeState(NecromancerIdle::Instance());
	myFiredProjectile = false;

	myAttackCooldown = 0.0f;

	CollisionMan->RegisterEntity(this);
}
NecromancerEntity::~NecromancerEntity()
{

}
void NecromancerEntity::Update()
{
	myStateMachine->update();
	if (myIsDamaged)
	{
		myDamageFrameCounter++;
		//fix this later
		if (myDamageFrameCounter > 0 && myDamageFrameCounter < 10)
			myAnimatedSprite->SetInverted(1);
		if (myDamageFrameCounter >= 10 && myDamageFrameCounter < 20)
			myAnimatedSprite->SetInverted(0);
		if (myDamageFrameCounter >= 20 && myDamageFrameCounter < 30)
			myAnimatedSprite->SetInverted(1);
		if (myDamageFrameCounter >= 30)
		{
			myIsDamaged = false;
			myAnimatedSprite->SetInverted(0);
		}
	}
}
bool NecromancerEntity::HandleMessage(const Message& msg)
{
	myStateMachine->HandleMessage(msg);
	return false;
}
void NecromancerEntity::SetFacing()
{
	if (IsPlayerToTheRight() && myAnimatedSprite->myHeading != Heading::LEFTFACING)
	{
		myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	else if (!IsPlayerToTheRight() && myAnimatedSprite->myHeading != Heading::RIGHTFACING)
	{
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		myAABB->myOrigin = glm::vec2(mPosition.x - 10.0f, mPosition.y - 26.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x - 10.0f, mPosition.y - 26.0f, mPosition.z, 1.0f);
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x + 10.0f, mPosition.y - 26.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x + 10.0f, mPosition.y - 26.0f, mPosition.z, 1.0f);
	}
}
void NecromancerEntity::HandleMovement()
{
	if (GetFSM()->isInState(*NecromancerPatrol::Instance()))
	{
		if (myXDirection > 0.0f)
		{
			if (mPosition.x <= endPatrol.x)
			{
				if (myAnimatedSprite->myHeading != Heading::LEFTFACING)
					myAnimatedSprite->SetHeading(Heading::LEFTFACING);
				mPosition.x += myXDirection;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
			else
			{

				myXDirection = -1.0f;
				myAnimatedSprite->SetHeading(Heading::LEFTFACING);
			}
		}
		if (myXDirection < 0.0f)
		{
			if (mPosition.x >= startPatrol.x)
			{

				if (myAnimatedSprite->myHeading != Heading::RIGHTFACING)
					myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
				mPosition.x += myXDirection;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
			else
			{
				myXDirection = 1.0f;
				myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
			}
		}
	}
	else
	{
		if (!IsPlayerWithinAttackDistance() && IsPlayerWithinPatrolRange() && AmIWithinMyPatrolDistance())
		{
			if (IsPlayerToTheRight())
			{
				if (myAnimatedSprite->myHeading != Heading::LEFTFACING)
					myAnimatedSprite->SetHeading(Heading::LEFTFACING);
				mPosition.x += 1.3f;
				if (!AmIWithinMyPatrolDistance())
					mPosition.x -= 1.3f;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
			else
			{
				if (myAnimatedSprite->myHeading != Heading::RIGHTFACING)
					myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
				mPosition.x -= 1.3f;
				if (!AmIWithinMyPatrolDistance())
					mPosition.x += 1.3f;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
		}
	}


	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		myAABB->myOrigin = glm::vec2(mPosition.x - 10.0f, mPosition.y - 26.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x - 10.0f, mPosition.y - 26.0f, mPosition.z, 1.0f);
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x + 10.0f, mPosition.y - 26.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x + 10.0f, mPosition.y - 26.0f, mPosition.z, 1.0f);
	}


}
void NecromancerEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void NecromancerEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTimeInSeconds();
}
bool NecromancerEntity::IsPlayerWithinPatrolRange()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	return  playerPos.x >= startPatrol.x && playerPos.x <= endPatrol.x;
}
bool NecromancerEntity::IsPlayerWithinAttackDistance()
{
	return IsPlayerWithinPatrolRange();
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
/*	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	glm::vec2 myPos = glm::vec2(mPosition);

	float distance = glm::length(myPos - playerPos);
	return distance < 40.0f;*/
}
bool NecromancerEntity::AmIWithinMyPatrolDistance()
{
	return (mPosition.x >= startPatrol.x && mPosition.x <= endPatrol.x);
}
bool NecromancerEntity::IsPlayerToTheRight()
{
	return myTileMap->myPlayerWorldPosition.x > mPosition.x;
	//return myTileMap->lastPlayerTile->myWorldPosition.x > mPosition.x;
}
bool NecromancerEntity::IsAttackCoolDownReady()
{
	return Clock->GetCurrentTimeInSeconds() > myAttackCooldown;
}
void NecromancerEntity::SpawnProjectile()
{
	if (myFiredProjectile)
		return;
	if (myAnimatedSprite->myHeading == Heading::LEFTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Necromancer Projectile", glm::vec3(mPosition.x + 56.0f, mPosition.y-17.0f, mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
		myFiredProjectile = true;
	}
	else if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Necromancer Projectile", glm::vec3(mPosition.x - 56.0f, mPosition.y - 17.0f, mPosition.z), glm::vec3(-1.0f, 0.0f, 0.0f));
		myFiredProjectile = true;
	}
}
void NecromancerEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	if (myHealth <= 0)
		GetFSM()->changeState(NecromancerDie::Instance());
}