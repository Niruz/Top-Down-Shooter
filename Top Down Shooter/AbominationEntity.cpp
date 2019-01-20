#include "SimpleTimer.h"
#include "AbominationEntity.h"
#include "Group.h"
#include "AbominationSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaAbominationStates.h"
#include "ShakeInfo.h"
#include "CollisionManager.h"
#include "NecromancerEntity.h"
#include "glm\vec2.hpp"
AbominationEntity::AbominationEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo, false)
{
	myStartPosition.x > patrolTo.x ? myMinX = patrolTo.x : myMinX = myStartPosition.x;
	myStartPosition.x > patrolTo.x ? myMaxX = myStartPosition.x : myMaxX = patrolTo.x;
	myStartY = myStartPosition.y;
	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y - 100.0f), 100.0f, 100.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f), glm::vec2(200.0f, 200.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	myAnimatedSprite = new AbominationSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1), glm::vec2(376, 376), TextureMan->GetTexture("abomination"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
//	mySprite->Add(myPlayerAABB);
	myAnimatedSprite->SetAnimation("AbominationIdle");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::LEFTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
	myStateMachine = new StateMachine<AbominationEntity>(this);

	myStateMachine->setCurrentState(AbominationWaitForPlayer::Instance());
	myStateMachine->changeState(AbominationWaitForPlayer::Instance());
	myShakeInfoSlamAttack = new ShakeInfo(600, 50, 10);
	myJumpShake = new ShakeInfo(1000, 60, 12);

	myAttackCooldown = 0.0f;

	CollisionMan->RegisterEntity(this);

	myHitAABB = new AABB(glm::vec2(mPosition.x - 70.0f, mPosition.y - 125.0f), 75.0f, 60.0f);
	myHitSpriteAABB = new Sprite(glm::vec4(mPosition.x - 70.0f, mPosition.y - 125.0f, mPosition.z + 0.01, 1.0f), glm::vec2(150.0f, 120.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	//mySprite->Add(myHitSpriteAABB);

	myAlreadyAttacked = false;

	myHealth = 120;
	myYVelocity = 10.0f;
	myNegYVelocity = -2.0f;
	myGravity = -0.25f;
	myStartedJump = false;
	myJumpXDirection = 0.0f;
	myJumpCooldown = Clock->GetCurrentTimeInSeconds() + 13.0f;
	mySpawnProjectileCooldown = Clock->GetCurrentTimeInSeconds() + 10.0f;
}
AbominationEntity::~AbominationEntity()
{
	delete myStateMachine;
}
void AbominationEntity::StartJump()
{
	if (this->IsPlayerToTheRight())
		myJumpXDirection = 1.0f;
	else
		myJumpXDirection = -1.0f;
	if (!this->IsPlayerWithinAttackDistance())
		myJumpXDirection *= 3.0f;
}
void AbominationEntity::HandleJump()
{
	mPosition.y += myYVelocity;
	myAnimatedSprite->myPosition.y = mPosition.y;

	mPosition.x += myJumpXDirection;
	myAnimatedSprite->myPosition.x = mPosition.x;
	if (mPosition.x > myMaxX)
	{
		mPosition.x = myMaxX - 1.0f;
		myAnimatedSprite->myPosition.x = mPosition.x;
	}
	if (mPosition.x < myMinX)
	{
		mPosition.x = myMinX + 1.0f;
		myAnimatedSprite->myPosition.x = mPosition.x;
	}

	myYVelocity += myGravity;
	if(myYVelocity <= 0)
	{
		myYVelocity = 10.0f;
		this->GetFSM()->changeState(AbominationFalling::Instance());
	}

	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y - 100.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x + 70.0f, mPosition.y - 125.0f);
		myHitSpriteAABB->myPosition.x = mPosition.x + 70.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y - 125.0f;
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y - 100.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x - 70.0f, mPosition.y - 125.0f);
		myHitSpriteAABB->myPosition.x = mPosition.x - 70.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y - 125.0f;
	}
}
void AbominationEntity::HandleFalling()
{
	mPosition.y += myNegYVelocity;
	myAnimatedSprite->myPosition.y = mPosition.y;
	myNegYVelocity += myGravity;

	mPosition.x += myJumpXDirection;
	myAnimatedSprite->myPosition.x = mPosition.x;
	if(mPosition.x > myMaxX)
	{
		mPosition.x = myMaxX -1.0f;
		myAnimatedSprite->myPosition.x = mPosition.x;
	}
	if (mPosition.x < myMinX)
	{
		mPosition.x = myMinX + 1.0f;
		myAnimatedSprite->myPosition.x = mPosition.x;
	}

	if (mPosition.y <= myStartY)
	{
		mPosition.y = myStartY;
		myAnimatedSprite->myPosition.y = mPosition.y;
		myNegYVelocity = -2.0f;
		this->GetFSM()->changeState(AbominationIdle::Instance());
	}

	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y - 100.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x + 70.0f, mPosition.y - 125.0f);
		myHitSpriteAABB->myPosition.x = mPosition.x + 70.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y - 125.0f;
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y - 100.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x - 70.0f, mPosition.y - 125.0f);
		myHitSpriteAABB->myPosition.x = mPosition.x - 70.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y - 125.0f;
	}
}
void AbominationEntity::Update()
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
bool AbominationEntity::HandleMessage(const Message& msg)
{
	myStateMachine->HandleMessage(msg);
	return false;
}
void AbominationEntity::SetFacing()
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
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y - 100.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x + 70.0f, mPosition.y - 125.0f);
		myHitSpriteAABB->myPosition.x = mPosition.x + 70.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y - 125.0f;
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y - 100.0f);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x - 70.0f, mPosition.y - 125.0f);
		myHitSpriteAABB->myPosition.x = mPosition.x - 70.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y - 125.0f;
	}
}
void AbominationEntity::HandleMovement()
{
	if (GetFSM()->isInState(*AbominationPatrol::Instance()))
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
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x + 70.0f, mPosition.y - 125.0f);
		myHitSpriteAABB->myPosition.x = mPosition.x + 70.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y - 125.0f;
	}
	else
	{
		myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
		myPlayerAABB->myPosition = glm::vec4(mPosition.x , mPosition.y - 100.0f, mPosition.z + 0.01, 1.0f);
		myHitAABB->myOrigin = glm::vec2(mPosition.x - 70.0f, mPosition.y - 125.0f);
		myHitSpriteAABB->myPosition.x = mPosition.x - 70.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y - 125.0f;
	}


}
void AbominationEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void AbominationEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTimeInSeconds();
}
bool AbominationEntity::IsPlayerWithinPatrolRange()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	return  playerPos.x >= startPatrol.x && playerPos.x <= endPatrol.x;
}
bool AbominationEntity::IsPlayerWithinAttackDistance()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = glm::vec2(myTileMap->myPlayerWorldPosition.x, 0);
	glm::vec2 myPos = glm::vec2(mPosition.x, 0);

	float distance = glm::length(myPos - playerPos);
	return distance < 90.0f;
}
bool AbominationEntity::AmIWithinMyPatrolDistance()
{
	return (mPosition.x >= startPatrol.x && mPosition.x <= endPatrol.x);
}
bool AbominationEntity::IsPlayerToTheRight()
{
	return myTileMap->myPlayerWorldPosition.x > mPosition.x;
	//return myTileMap->lastPlayerTile->myWorldPosition.x > mPosition.x;
}
bool AbominationEntity::IsAttackCoolDownReady()
{
	return Clock->GetCurrentTimeInSeconds() > myAttackCooldown;
}
void AbominationEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	if (myHealth <= 0)
		GetFSM()->changeState(AbominationDie::Instance());
}
bool AbominationEntity::IsPlayerWithinAttackDistance2()
{

//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
glm::vec2 playerPos = glm::vec2(myTileMap->myPlayerWorldPosition.x, 0);
glm::vec2 myPos = glm::vec2(mPosition.x, 0);

	float distance = glm::length(myPos - playerPos);
	return distance < 650.0f;
}