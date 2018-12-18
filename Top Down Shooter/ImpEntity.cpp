#include "SimpleTimer.h"
#include "ImpEntity.h"
#include "Group.h"
#include "ImpSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaImpStates.h"
#include "ShakeInfo.h"
#include "CollisionManager.h"
#include "World.h"
#include "Level.h"
# define M_PI           3.14159265358979323846  /* pi */
ImpEntity::ImpEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo, false)
{
	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 10.0f, 10.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z+0.01f, 1.0f), glm::vec2(20.0f, 20.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	myAnimatedSprite = new ImpSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1), glm::vec2(50, 50), TextureMan->GetTexture("imp"), Heading::LEFTFACING);
//	mySprite->Add(myPlayerAABB);
	mySprite->Add(myAnimatedSprite);
	
	myAnimatedSprite->SetAnimation("ImpRun");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
	myStateMachine = new StateMachine<ImpEntity>(this);

	myStateMachine->setCurrentState(ImpIdle::Instance());
	myStateMachine->changeState(ImpIdle::Instance());

	myFiredProjectile = false;
	myAttackCooldown = 0.0f;
	angle = 0.0f;
	CollisionMan->RegisterEntity(this);
}
ImpEntity::~ImpEntity()
{
	delete myStateMachine;
}
void ImpEntity::Update()
{
	myStateMachine->update();
	if (myIsDamaged)
	{
		myDamageFrameCounter++;
		//fix this later
		if (myDamageFrameCounter > 0 && myDamageFrameCounter < 5)
			myAnimatedSprite->SetInverted(1);
		if (myDamageFrameCounter >= 5 && myDamageFrameCounter < 10)
			myAnimatedSprite->SetInverted(0);
		if (myDamageFrameCounter >= 10 && myDamageFrameCounter < 15)
			myAnimatedSprite->SetInverted(1);
		if (myDamageFrameCounter >= 15)
		{
			myIsDamaged = false;
			myAnimatedSprite->SetInverted(0);
		}

	}
/*	if (myIsDamaged)
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
	}*/
}
bool ImpEntity::HandleMessage(const Message& msg)
{
	myStateMachine->HandleMessage(msg);
	return false;
}
void ImpEntity::SetFacing()
{
	if (IsPlayerToTheRight() && myAnimatedSprite->myHeading != Heading::LEFTFACING)
	{
		myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	else if (!IsPlayerToTheRight() && myAnimatedSprite->myHeading != Heading::RIGHTFACING)
	{
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
}
void ImpEntity::HandleMovement()
{
	if (GetFSM()->isInState(*ImpPatrol::Instance()))
	{
		if (myXDirection > 0.0f)
		{
			if (mPosition.x <= endPatrol.x)
			{
				if (myAnimatedSprite->myHeading != Heading::LEFTFACING)
					myAnimatedSprite->SetHeading(Heading::LEFTFACING);
				mPosition.x += myXDirection;
				myAnimatedSprite->myPosition.x = mPosition.x;
				mPosition.y += sin(angle * M_PI / 180.0f);
				myAnimatedSprite->myPosition.y += sin(angle * M_PI / 180.0f);
				angle += 5;
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
				mPosition.y += sin(angle * M_PI / 180.0f);
				myAnimatedSprite->myPosition.y += sin(angle * M_PI / 180.0f);
				angle += 5;
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
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.01, 1.0f);
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x , mPosition.y, mPosition.z + 0.01, 1.0f);
	}


}
void ImpEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void ImpEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTimeInSeconds();
}
bool ImpEntity::IsPlayerWithinPatrolRange()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	return  playerPos.x >= startPatrol.x && playerPos.x <= endPatrol.x;
}
bool ImpEntity::IsPlayerWithinAttackDistance()
{
	return IsPlayerWithinPatrolRange();
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	/*glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	glm::vec2 myPos = glm::vec2(mPosition);

	float distance = glm::length(myPos - playerPos);
	return distance < 40.0f;*/
}
bool ImpEntity::AmIWithinMyPatrolDistance()
{
	return (mPosition.x >= startPatrol.x && mPosition.x <= endPatrol.x);
}
bool ImpEntity::IsPlayerToTheRight()
{
	return myTileMap->myPlayerWorldPosition.x > mPosition.x;
	//return myTileMap->lastPlayerTile->myWorldPosition.x > mPosition.x;
}
bool ImpEntity::IsAttackCoolDownReady()
{
	return Clock->GetCurrentTimeInSeconds() > myAttackCooldown;
}
void ImpEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	if (myHealth <= 0)
		GetFSM()->changeState(ImpDie::Instance());
}
void ImpEntity::SpawnProjectile()
{
	if (myFiredProjectile)
		return;
	if (myAnimatedSprite->myHeading == Heading::LEFTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Imp Projectile", glm::vec3(mPosition.x + 28.0f, mPosition.y - 8.5f, mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
		myFiredProjectile = true;
	}
	else if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Imp Projectile", glm::vec3(mPosition.x - 28.0f, mPosition.y - 8.5f, mPosition.z), glm::vec3(-1.0f, 0.0f, 0.0f));
		myFiredProjectile = true;
	}
}