#include "SimpleTimer.h"
#include "FireGolemEntity.h"
#include "Group.h"
#include "FireGolemSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaFireGolemStates.h"
#include "ShakeInfo.h"
#include "CollisionManager.h"
FireGolemEntity::FireGolemEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo,false)
{
	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 16.0f, 16.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y-14.0f, 0.2f, 1.0f), glm::vec2(50.0f, 80.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	myAnimatedSprite = new FireGolemSprite(glm::vec4(mPosition.x, mPosition.y, 0.09f, 1), glm::vec2(128, 114), TextureMan->GetTexture("firegolem"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);
	//mySprite->Add(myPlayerAABB);
	myAnimatedSprite->SetAnimation("FireGolemRun");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
	myStateMachine = new StateMachine<FireGolemEntity>(this);

	myStateMachine->setCurrentState(FireGolemWaiting::Instance());
	myStateMachine->changeState(FireGolemWaiting::Instance());

	shakeAttack1 = false;
	shakeAttack2 = false;
	firstTimeSeeingPlayer = true;
	myShakeInfoBasicAttack = new ShakeInfo(500, 40, 5);
	myShakeInfoSlamAttack = new ShakeInfo(600, 55, 7); 

	myAttackCooldown = 0.0f;

	CollisionMan->RegisterEntity(this);
}
FireGolemEntity::~FireGolemEntity()
{
	delete myShakeInfoBasicAttack;
	delete myShakeInfoSlamAttack;
}
void FireGolemEntity::Update()
{
	myStateMachine->update();
	if(myIsDamaged)
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
bool FireGolemEntity::HandleMessage(const Message& msg)
{
	myStateMachine->HandleMessage(msg);
	return false;
}
void FireGolemEntity::SetFacing()
{
	if (IsPlayerToTheRight() && myAnimatedSprite->myHeading != Heading::LEFTFACING)
	{
		myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	else if( !IsPlayerToTheRight() && myAnimatedSprite->myHeading != Heading::RIGHTFACING)
	{
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
}
void FireGolemEntity::HandleMovement()
{
	if(GetFSM()->isInState(*FireGolemPatrol::Instance()))
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

	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y - 14.0f, mPosition.z, 1.0f);

}
void FireGolemEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void FireGolemEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTime();
}
bool FireGolemEntity::FirstTimeSeeingPlayer()
{
	return myTileMap->myPlayerWorldPosition.x < endPatrol.x && firstTimeSeeingPlayer;
	//return myTileMap->lastPlayerTile->myWorldPosition.x < endPatrol.x && firstTimeSeeingPlayer;
}
bool FireGolemEntity::IsPlayerWithinPatrolRange()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	return  playerPos.x >= startPatrol.x && playerPos.x <= endPatrol.x;
}
bool FireGolemEntity::IsPlayerWithinAttackDistance()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	glm::vec2 myPos = glm::vec2(mPosition);

	float distance = glm::length(myPos - playerPos);
	return distance < 60.0f;
}
bool FireGolemEntity::AmIWithinMyPatrolDistance()
{
	return (mPosition.x >= startPatrol.x && mPosition.x <= endPatrol.x);
}
bool FireGolemEntity::IsPlayerToTheRight()
{
	return myTileMap->myPlayerWorldPosition.x > mPosition.x;
	//return myTileMap->lastPlayerTile->myWorldPosition.x > mPosition.x;
}
bool FireGolemEntity::IsAttackCoolDownReady()
{
	return Clock->GetCurrentTime() > myAttackCooldown;
}
void FireGolemEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	if(myHealth <= 0)
		GetFSM()->changeState(FireGolemDie::Instance());
}