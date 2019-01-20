#include "SimpleTimer.h"
#include "ShriekerEntity.h"
#include "Group.h"
#include "ShriekerSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaShriekerStates.h"
#include "ShakeInfo.h"
#include "CollisionManager.h"
#include "NecromancerEntity.h"
ShriekerEntity::ShriekerEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo, false)
{
	myAABB = new AABB(glm::vec2(mPosition.x - 10.0f, mPosition.y), 20.0f, 20.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x - 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f), glm::vec2(40.0f, 40.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));

	myAnimatedSprite = new ShriekerSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1), glm::vec2(64.0f, 80.0f), TextureMan->GetTexture("shrieker"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	//mySprite->Add(myPlayerAABB);
	myAnimatedSprite->SetAnimation("ShriekerIdle");


	myStateMachine = new StateMachine<ShriekerEntity>(this);

	myStateMachine->setCurrentState(ShriekerIdle::Instance());
	myStateMachine->changeState(ShriekerIdle::Instance());
	myShakeInfoSlamAttack = new ShakeInfo(500, 30, 6);

	myAttackCooldown = 0.0f;

	CollisionMan->RegisterEntity(this);
	//myShakeInfoSlamAttack = new ShakeInfo(600, 55, 7);
	myHitAABB = new AABB(glm::vec2(mPosition.x - 10.0f, mPosition.y), 20.0f, 20.0f);
	myHitSpriteAABB = new Sprite(glm::vec4(mPosition.x - 10.0f, mPosition.y, mPosition.z + 0.01, 1.0f), glm::vec2(40.0f, 40.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	//	mySprite->Add(myHitSpriteAABB);

	myAlreadyAttacked = false;

	myHealth = 60;
	myCurrentAppearIndex = 0;

}
ShriekerEntity::~ShriekerEntity()
{
	delete myStateMachine;
}
void ShriekerEntity::Update()
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
}
bool ShriekerEntity::HandleMessage(const Message& msg)
{
	myStateMachine->HandleMessage(msg);
	return false;
}
void ShriekerEntity::SetFacing()
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
		myHitAABB->myOrigin = glm::vec2(mPosition.x + 50.0f, mPosition.y);
		myHitSpriteAABB->myPosition.x = mPosition.x + 50.0f;
		myHitSpriteAABB->myPosition.y = mPosition.y;
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
void ShriekerEntity::HandleMovement()
{

}
void ShriekerEntity::ChooseAppearPoint()
{
	mPosition = glm::vec3(myAppearPoints[myCurrentAppearIndex], mPosition.z);

	myAnimatedSprite->myPosition.x = mPosition.x;
	myAnimatedSprite->myPosition.y = mPosition.y;


	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myPlayerAABB->myPosition = glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.01, 1.0f);
	myHitAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myHitSpriteAABB->myPosition.x = mPosition.x ;
	myHitSpriteAABB->myPosition.y = mPosition.y;

	myCurrentAppearIndex++;
	if (myCurrentAppearIndex >= myAppearPoints.size())
		myCurrentAppearIndex = 0;
}
void ShriekerEntity::AddAppearPoint(const glm::vec2& point)
{
	myAppearPoints.push_back(point);
}
void ShriekerEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void ShriekerEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTimeInSeconds();
}
bool ShriekerEntity::IsPlayerWithinPatrolRange()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = myTileMap->myPlayerWorldPosition;
	return  playerPos.x >= startPatrol.x && playerPos.x <= endPatrol.x;
}
bool ShriekerEntity::IsPlayerWithinAttackDistance()
{
	//glm::vec2 playerPos = myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 playerPos = glm::vec2(myTileMap->myPlayerWorldPosition.x, 0);
	glm::vec2 myPos = glm::vec2(mPosition.x, 0);

	float distance = glm::length(myPos - playerPos);
	return distance < 240.0f;
}
bool ShriekerEntity::AmIWithinMyPatrolDistance()
{
	return (mPosition.x >= startPatrol.x && mPosition.x <= endPatrol.x);
}
bool ShriekerEntity::IsPlayerToTheRight()
{
	return myTileMap->myPlayerWorldPosition.x > mPosition.x;
	//return myTileMap->lastPlayerTile->myWorldPosition.x > mPosition.x;
}
bool ShriekerEntity::IsAttackCoolDownReady()
{
	return Clock->GetCurrentTimeInSeconds() > myAttackCooldown;
}
void ShriekerEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	if (myHealth <= 0)
		GetFSM()->changeState(ShriekerDie::Instance());
}