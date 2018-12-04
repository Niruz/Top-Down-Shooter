#include "SimpleTimer.h"
#include "GhoulEntity.h"
#include "Group.h"
#include "GhoulSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaGhoulStates.h"
#include "ShakeInfo.h"
#include "CollisionManager.h"
GhoulEntity::GhoulEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo, false)
{
	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 20.0f, 15.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x - 10, mPosition.y, mPosition.z+0.01, 1.0f), glm::vec2(40.0f, 30.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	myAnimatedSprite = new GhoulSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1), glm::vec2(102, 40), TextureMan->GetTexture("ghoul"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);
//	mySprite->Add(myPlayerAABB);
	myAnimatedSprite->SetAnimation("GhoulRun");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
	myStateMachine = new StateMachine<GhoulEntity>(this);

	myStateMachine->setCurrentState(GhoulIdle::Instance());
	myStateMachine->changeState(GhoulIdle::Instance());


	myAttackCooldown = 0.0f;

	CollisionMan->RegisterEntity(this);
}
GhoulEntity::~GhoulEntity()
{

}
void GhoulEntity::Update()
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
bool GhoulEntity::HandleMessage(const Message& msg)
{
	myStateMachine->HandleMessage(msg);
	return false;
}
void GhoulEntity::SetFacing()
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
void GhoulEntity::HandleMovement()
{
	if (GetFSM()->isInState(*GhoulPatrol::Instance()))
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
		myAABB->myOrigin = glm::vec2(mPosition.x + 10.0f, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x + 10.0f, mPosition.y, mPosition.z, 1.0f);
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x - 10.0f, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x - 10.0f, mPosition.y, mPosition.z, 1.0f);
	}
	

}
void GhoulEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void GhoulEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTime();
}
bool GhoulEntity::IsPlayerWithinPatrolRange()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	return  playerPos.x >= startPatrol.x && playerPos.x <= endPatrol.x;
}
bool GhoulEntity::IsPlayerWithinAttackDistance()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	glm::vec2 myPos = glm::vec2(mPosition);

	float distance = glm::length(myPos - playerPos);
	return distance < 40.0f;
}
bool GhoulEntity::AmIWithinMyPatrolDistance()
{
	return (mPosition.x >= startPatrol.x && mPosition.x <= endPatrol.x);
}
bool GhoulEntity::IsPlayerToTheRight()
{
	return myTileMap->myPlayerWorldPosition.x > mPosition.x;
	//return myTileMap->lastPlayerTile->myWorldPosition.x > mPosition.x;
}
bool GhoulEntity::IsAttackCoolDownReady()
{
	return Clock->GetCurrentTime() > myAttackCooldown;
}
void GhoulEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	if (myHealth <= 0)
		GetFSM()->changeState(GhoulDie::Instance());
}