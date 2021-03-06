#include "SimpleTimer.h"
#include "ReaperEntity.h"
#include "Group.h"
#include "ReaperSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaReaperStates.h"
#include "ShakeInfo.h"
#include "CollisionManager.h"
ReaperEntity::ReaperEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo, false)
{
	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 20.0f, 15.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x - 10, mPosition.y, mPosition.z+0.01, 1.0f), glm::vec2(40.0f, 30.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	myAnimatedSprite = new ReaperSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1), glm::vec2(48+ 24, 46 + 23), TextureMan->GetTexture("reaper"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);
	//mySprite->Add(myPlayerAABB);
	myAnimatedSprite->SetAnimation("ReaperRun");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
	myStateMachine = new StateMachine<ReaperEntity>(this);

	myStateMachine->setCurrentState(ReaperIdle::Instance());
	myStateMachine->changeState(ReaperIdle::Instance());


	myAttackCooldown = 0.0f;

	CollisionMan->RegisterEntity(this);

	myHitAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 30.0f, 20.0f);
	myHitSpriteAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.01, 1.0f), glm::vec2(60.0f, 40.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	//mySprite->Add(myHitSpriteAABB);

	myAlreadyAttacked = false;
	myHealth = 60;
}
ReaperEntity::~ReaperEntity()
{
	delete myStateMachine;
}
void ReaperEntity::Update()
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
	/*if (myIsDamaged)
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
bool ReaperEntity::HandleMessage(const Message& msg)
{
	myStateMachine->HandleMessage(msg);
	return false;
}
void ReaperEntity::SetFacing()
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
		myHitAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
		myHitSpriteAABB->myPosition.x = mPosition.x;
	}
	else
	{
		myHitAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
		myHitSpriteAABB->myPosition.x = mPosition.x;
	}
}
void ReaperEntity::HandleMovement()
{
	if (GetFSM()->isInState(*ReaperPatrol::Instance()))
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
				mPosition.x += 1.9f;
				if (!AmIWithinMyPatrolDistance())
					mPosition.x -= 1.9f;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
			else
			{
				if (myAnimatedSprite->myHeading != Heading::RIGHTFACING)
					myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
				mPosition.x -= 1.9f;
				if (!AmIWithinMyPatrolDistance())
					mPosition.x += 1.9f;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
		}
	}


	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		myAABB->myOrigin = glm::vec2(mPosition.x + 10.0f, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x + 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
		myHitSpriteAABB->myPosition.x = mPosition.x;
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x - 10.0f, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x - 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
		myHitSpriteAABB->myPosition.x = mPosition.x;
	}

}
void ReaperEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void ReaperEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTimeInSeconds();
}
bool ReaperEntity::IsPlayerWithinPatrolRange()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;

	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos2 = glm::vec2(myTileMap->myPlayerWorldPosition.y, 0);
	glm::vec2 myPos2 = glm::vec2(mPosition.y, 0);

	float distance2 = glm::length(myPos2 - playerPos2);

	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	return  (playerPos.x >= startPatrol.x && playerPos.x <= endPatrol.x) && distance2 < 30.0f;
}
bool ReaperEntity::IsPlayerWithinAttackDistance()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = glm::vec2(myTileMap->myPlayerWorldPosition.x, 0);
	glm::vec2 myPos = glm::vec2(mPosition.x, 0);

	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos2 = glm::vec2(myTileMap->myPlayerWorldPosition.y, 0);
	glm::vec2 myPos2 = glm::vec2(mPosition.y, 0);


	float distance = glm::length(myPos - playerPos);
	float distance2 = glm::length(myPos2 - playerPos2);
	return (distance < 85.0f) && (distance2 < 30.0f);
}
bool ReaperEntity::AmIWithinMyPatrolDistance()
{
	return (mPosition.x >= startPatrol.x && mPosition.x <= endPatrol.x);
}
bool ReaperEntity::IsPlayerToTheRight()
{
	return myTileMap->myPlayerWorldPosition.x > mPosition.x;
	//return myTileMap->lastPlayerTile->myWorldPosition.x > mPosition.x;
}
bool ReaperEntity::IsAttackCoolDownReady()
{
	return Clock->GetCurrentTimeInSeconds() > myAttackCooldown;
}
void ReaperEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	if (myHealth <= 0)
		GetFSM()->changeState(ReaperDie::Instance());
}