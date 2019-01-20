#include "SimpleTimer.h"
#include "BigSkeletonEntity.h"
#include "Group.h"
#include "BigSkeletonSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaBigSkeletonStates.h"
#include "ShakeInfo.h"
#include "CollisionManager.h"
#include "NecromancerEntity.h"
BigSkeletonEntity::BigSkeletonEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo, false)
{
	myAABB = new AABB(glm::vec2(mPosition.x - 10.0f, mPosition.y), 20.0f, 50.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x - 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f), glm::vec2(40.0f, 100.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	myAnimatedSprite = new BigSkeletonSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1), glm::vec2(256, 128), TextureMan->GetTexture("bigskeleton"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	//mySprite->Add(myPlayerAABB);
	myAnimatedSprite->SetAnimation("SkeletonIdle");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::LEFTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
	myStateMachine = new StateMachine<BigSkeletonEntity>(this);

	myStateMachine->setCurrentState(BigSkeletonIdle::Instance());
	myStateMachine->changeState(BigSkeletonIdle::Instance());
	myShakeInfoSlamAttack = new ShakeInfo(600, 50, 10);

	myAttackCooldown = 0.0f;

	CollisionMan->RegisterEntity(this);

	myHitAABB = new AABB(glm::vec2(mPosition.x - 50.0f, mPosition.y - 10.0f), 75.0f, 40.0f);
	myHitSpriteAABB = new Sprite(glm::vec4(mPosition.x - 50.0f, mPosition.y - 10.0f, mPosition.z + 0.01, 1.0f), glm::vec2(150.0f, 80.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
//	mySprite->Add(myHitSpriteAABB);

	myAlreadyAttacked = false;

	myHealth = 60;

}
BigSkeletonEntity::~BigSkeletonEntity()
{
	delete myStateMachine;
}
void BigSkeletonEntity::Update()
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
bool BigSkeletonEntity::HandleMessage(const Message& msg)
{
	myStateMachine->HandleMessage(msg);
	return false;
}
void BigSkeletonEntity::SetFacing()
{
	if (IsPlayerToTheRight() && myAnimatedSprite->myHeading != Heading::RIGHTFACING)
	{
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (!IsPlayerToTheRight() && myAnimatedSprite->myHeading != Heading::LEFTFACING)
	{
		myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		myAABB->myOrigin = glm::vec2(mPosition.x - 10.0f, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x - 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x + 50.0f, mPosition.y );
		myHitSpriteAABB->myPosition.x = mPosition.x + 50.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y;
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x + 10.0f, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x + 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x - 50.0f, mPosition.y );
		myHitSpriteAABB->myPosition.x = mPosition.x - 50.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y ;
	}
}
void BigSkeletonEntity::HandleMovement()
{
	if (GetFSM()->isInState(*BigSkeletonPatrol::Instance()))
	{
		if (myXDirection > 0.0f)
		{
			if (mPosition.x <= endPatrol.x)
			{
				if (myAnimatedSprite->myHeading != Heading::RIGHTFACING)
					myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
				mPosition.x += myXDirection;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
			else
			{

				myXDirection = -1.0f;
				myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
			}
		}
		if (myXDirection < 0.0f)
		{
			if (mPosition.x >= startPatrol.x)
			{

				if (myAnimatedSprite->myHeading != Heading::LEFTFACING)
					myAnimatedSprite->SetHeading(Heading::LEFTFACING);
				mPosition.x += myXDirection;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
			else
			{
				myXDirection = 1.0f;
				myAnimatedSprite->SetHeading(Heading::LEFTFACING);
			}
		}
	}
	else
	{
		if (!IsPlayerWithinAttackDistance() && IsPlayerWithinPatrolRange() && AmIWithinMyPatrolDistance())
		{
			if (IsPlayerToTheRight())
			{
				if (myAnimatedSprite->myHeading != Heading::RIGHTFACING)
					myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
				mPosition.x += 1.3f;
				if (!AmIWithinMyPatrolDistance())
					mPosition.x -= 1.3f;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
			else
			{
				if (myAnimatedSprite->myHeading != Heading::LEFTFACING)
					myAnimatedSprite->SetHeading(Heading::LEFTFACING);
				mPosition.x -= 1.3f;
				if (!AmIWithinMyPatrolDistance())
					mPosition.x += 1.3f;
				myAnimatedSprite->myPosition.x = mPosition.x;
			}
		}
	}


	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		myAABB->myOrigin = glm::vec2(mPosition.x - 10.0f, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x - 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x + 50.0f, mPosition.y );
		myHitSpriteAABB->myPosition.x = mPosition.x + 50.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y ;
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x + 10.0f, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x + 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x - 50.0f, mPosition.y);
		myHitSpriteAABB->myPosition.x = mPosition.x - 50.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y;
	}


}
void BigSkeletonEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void BigSkeletonEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTimeInSeconds();
}
bool BigSkeletonEntity::IsPlayerWithinPatrolRange()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	return  playerPos.x >= startPatrol.x && playerPos.x <= endPatrol.x;
}
bool BigSkeletonEntity::IsPlayerWithinAttackDistance()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = glm::vec2(myTileMap->myPlayerWorldPosition.x, 0);
	glm::vec2 myPos = glm::vec2(mPosition.x, 0);

	float distance = glm::length(myPos - playerPos);
	return distance < 60.0f;
}
bool BigSkeletonEntity::AmIWithinMyPatrolDistance()
{
	return (mPosition.x >= startPatrol.x && mPosition.x <= endPatrol.x);
}
bool BigSkeletonEntity::IsPlayerToTheRight()
{
	return myTileMap->myPlayerWorldPosition.x > mPosition.x;
	//return myTileMap->lastPlayerTile->myWorldPosition.x > mPosition.x;
}
bool BigSkeletonEntity::IsAttackCoolDownReady()
{
	return Clock->GetCurrentTimeInSeconds() > myAttackCooldown;
}
void BigSkeletonEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	if (myHealth <= 0)
		GetFSM()->changeState(BigSkeletonDie::Instance());
}