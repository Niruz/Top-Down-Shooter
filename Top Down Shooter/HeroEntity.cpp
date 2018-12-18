#include "SimpleTimer.h"
#include "HeroEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "ShaderManager.h"
#include <iostream>

#include "TileMap.h"
#include "Group.h"
#include "AdventurerSprite.h"
#include "TextureManager.h"
#include "GLFW\glfw3.h"
#include "GothicVaniaHeroStates.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "ShakeInfo.h"
#include "World.h"
#include "Level.h"
#include "HitEffectSprite.h"
#include "BubblesSprite.h"
#include "MidnightSprite.h"
#include "SpellSprite.h"
# define M_PI3           3.14159265358979323846  /* pi */

HeroEntity::HeroEntity(int id, const std::string& name) : Entity(id, name), translationMatrix(1.0f),
rotationMatrix(1.0f), modelMatrix(1.0f), mAngle(0.0f)
{
	mPosition = glm::vec3(0.0f, 0.0f, 0.1f);
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	myAnimatedSprite = new AdventurerSprite(glm::vec4(0.0f, 5.0f, 0.1f, 1), glm::vec2(100, 59), TextureMan->GetTexture("adventurer2"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myDirection = glm::vec3(0.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y-2.5, 0.2f, 1.0f),glm::vec2(18.0f,44.0f),glm::vec4(0.0f,1.0f,0.0f,0.5f));
	//mySprite->Add(myPlayerAABB);
	myHitEffect = new HitEffectSprite(glm::vec4(0.0f, 0.0f, 0.3f, 1.0f), glm::vec2(200, 200),TextureMan->GetTexture("hiteffect"),Heading::RIGHTFACING);
	myHitEffect->SetAnimation("HitEffect");
	//mySprite->Add(myHitEffect);

	myBubblesSprite = new BubblesSprite(glm::vec4(0.0f, 0.0f, 0.3f, 1.0f), glm::vec2(100, 100), TextureMan->GetTexture("bubbles"), Heading::RIGHTFACING);
	myBubblesSprite->SetAnimation("BubblesEffect");
	//mySprite->Add(myBubblesSprite);

	myMidnightSprite = new MidnightSprite(glm::vec4(0.0f, 0.0f, 0.3f, 1.0f), glm::vec2(100, 100), TextureMan->GetTexture("midnight"), Heading::RIGHTFACING);
	myMidnightSprite->SetAnimation("MidnightEffect");
	//mySprite->Add(myMidnightSprite);

	mySpellSprite = new SpellSprite(glm::vec4(0.0f, 0.0f, 0.3f, 1.0f), glm::vec2(100, 100), TextureMan->GetTexture("spell"), Heading::RIGHTFACING);
	mySpellSprite->SetAnimation("SpellEffect");
//	mySprite->Add(mySpellSprite);

	myShouldSwitchAttack = false;
	myShouldEnterNextSwordAttack = false;
	myCurrentSwordAttackCooldownTimer = 0;
	currentKeyInput = 0;
	myState = IDLE;
	myPosXDirection = 0;
	myNegXDirection = 0;
	myPosYDirection = 0;
	myNegYDirection = 0;
	myYVelocity     = 0;
	myGravity       = -0.35f;
	//SetAnimation("heroIdle");

	myStateMachine = new StateMachine<HeroEntity>(this);

	myStateMachine->setCurrentState(HeroIdle::Instance());
	myStateMachine->changeState(HeroIdle::Instance());

	inAir = false;
	myStartJumpTime = 0.0f;
	myStartSlidingTime = 0.0f;
	myXVelocity = 0.0f;

	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y - 2.5), 9.0f, 22.0f);

	myFiredProjectile = false;

	mySwordAABB = new AABB(glm::vec2(mPosition.x + 30.0f, mPosition.y + 1.5), 17.0f, 15.0f);
	mySwordSpriteAABB = new Sprite(glm::vec4(mPosition.x + 30.0f, mPosition.y + 1.5, 0.25f, 1.0f), glm::vec2(34.0f, 10.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));
	//mySprite->Add(mySwordSpriteAABB);

	mySwordAABBRightX = mPosition.x + 30.0f;
	mySwordAABBLeftX = mPosition.y - 30.0f;
	myHealth = 100;
	myDamageFrameCounter = 0;
	myIsDamaged = false;
	CollisionMan->RegisterPlayer(this);
	basicAttack = false;
	myShouldChangeStance = false;
	myShouldKickNext = false;
	myShouldPunchNext = false;
	myShouldSwordNext = false;
	myAirSlamReceived = false;
	myShouldDropKick = false;
	myShouldChangeDirectionLeft = false;
	myShouldChangeDirectionRight = false;
	myShakeInfoBasicAttack = new ShakeInfo(500, 100, 1);
	//myShakeInfoBasicAttack = new ShakeInfo(1000, 10, 3);
	myDirectionWhenEnteringFallState = 0.0f;
	myDirectionChangeDuringFallState = 0.0f;
	myStartDeadTimer = 0.0f;
	myFallStateJumpTimer = 0.0f;
	myTimerToReceiveInputInFallState = 0.0f;
	myStartedToFallInJump = false;
	myShouldJumpInGlidingState = false;
	myDirectionWhenEnteringWallRunningState = 0.0f;
	myShouldStopWallRunning = false;
}
HeroEntity::~HeroEntity()
{
	delete myShakeInfoBasicAttack;
	delete myStateMachine;
}
void HeroEntity::Respawn()
{
	Tile* closestTile = myTileMap->getClosestRespawnTile(glm::vec2(myAABB->myOrigin.x, myAABB->myOrigin.y));

	mPosition.x = closestTile->myWorldPosition.x;
	mPosition.y = closestTile->myWorldPosition.y;
}
void HeroEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void HeroEntity::setDirection(const glm::vec2& direction)
{
	float angle = atan2(direction.y, direction.x);// *(180.0f / M_PI3);
	float degreesRadians = (M_PI3 / 180)*90.0f;

	mAngle = angle - degreesRadians;

	//std::cout << "angle: " << mAngle << std::endl;
}
float HeroEntity::map(float s, float a1, float a2, float b1, float b2)
{
	return b1 + (s - a1)*(b2 - b1) / (a2 - a1);
}
void HeroEntity::UpdateTransformationMatrix(const Camera& camera)
{

	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, mAngle, glm::vec3(0.0f, 0.0f, 1.0f));

	translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, mPosition);

	modelMatrix = camera.mTranslationMatrix* translationMatrix *rotationMatrix;
																			   

	mySprite->SetTransformationMatrix(modelMatrix);
}
void HeroEntity::HandleWallRunning()
{
	//is this necessary anymore?
	if (myStateMachine->isInState(*HeroCrouch::Instance()) || myStateMachine->isInState(*HeroAttackSword1::Instance()) || myStateMachine->isInState(*HeroAttackSword2::Instance()) || myStateMachine->isInState(*HeroAttackSword3::Instance()))
		return;
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;

	float velocity = 1.6f;


	if (myPosXDirection > 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.y += myPosXDirection * velocity;
		myAABB->myOrigin.y = mPosition.y;
		myTileMap->SetPlayerTile2(myAABB);

		bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
		bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;


		bool topBlocking = topLeftFree || topRightFree;

		if (topBlocking)
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileTopLeft->myWorldPosition.y - 16.0f - myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
		}
		
		if(!myTileMap->GetTile2(myTileMap->lastPlayerTile->myX +1,myTileMap->lastPlayerTile->myY)->myIsBlockingFlag)
		{
			if(mPosition.y > myTileMap->GetTile2(myTileMap->lastPlayerTile->myX + 1, myTileMap->lastPlayerTile->myY)->myWorldPosition.y+10.0f)
				myStateMachine->changeState(HeroFalling::Instance());
		}
	}
	else if (myNegXDirection < 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.y += myNegXDirection * velocity * -1.0f;
		myAABB->myOrigin.y = mPosition.y;
		myTileMap->SetPlayerTile2(myAABB);

		bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
		bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;


		bool topBlocking = topLeftFree || topRightFree;

		if (topBlocking)
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileTopLeft->myWorldPosition.y - 16.0f - myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
		}
		if (!myTileMap->GetTile2(myTileMap->lastPlayerTile->myX - 1, myTileMap->lastPlayerTile->myY)->myIsBlockingFlag)
		{
			if (mPosition.y > myTileMap->GetTile2(myTileMap->lastPlayerTile->myX + 1, myTileMap->lastPlayerTile->myY)->myWorldPosition.y + 10.0f)
				myStateMachine->changeState(HeroFalling::Instance());
		}
	}

	myNegYDirection = myPosYDirection = myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;

	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		mySwordAABB->myOrigin.x = mPosition.x + 30;
		mySwordAABB->myOrigin.y = mPosition.y + 1.5;
		mySwordSpriteAABB->myPosition.x = mySwordAABBRightX;
	}
	else
	{
		mySwordAABB->myOrigin.x = mPosition.x - 30;
		mySwordAABB->myOrigin.y = mPosition.y + 1.5;
		mySwordSpriteAABB->myPosition.x = mySwordAABBLeftX;
	}


}
void HeroEntity::HandleMovement()
{
	//is this necessary anymore?
	if (myStateMachine->isInState(*HeroCrouch::Instance()) || myStateMachine->isInState(*HeroAttackSword1::Instance()) || myStateMachine->isInState(*HeroAttackSword2::Instance()) || myStateMachine->isInState(*HeroAttackSword3::Instance()))
		return;
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;

	float velocity = 2.2f;

	/*Tile* bottomRight = myTileMap->lastPlayerTileBottomRight;
	if (myPosXDirection == 1.0f)
	{
		if(!bottomRight->myIsBlockingFlag)
		{
			mPosition.x += myPosXDirection * velocity;
		}
		else
		{
			if ((myAABB->myOrigin.x + myAABB->halfX) <= (bottomRight->myWorldPosition.x - 16.0f))
			{
				mPosition.x += myPosXDirection * velocity;
			}
			else
			{
				mPosition.x = bottomRight->myWorldPosition.x - 16.0f - myAABB->halfX;
			}
		}
	}
	
	myNegYDirection = myPosYDirection = myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;*/
	//Step X then step Y

	//Step X then step y
	
	if (myPosXDirection > 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myPosXDirection * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);
		
		bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
		bool midRightFree = myTileMap->lastPlayerTileMidRight->myIsBlockingFlag && !myTileMap->lastPlayerTileMidRight->myIsOneWayTile;
		bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
		bool rightBlocking = /*bottomRightFree && */midRightFree || topRightFree;

		if (rightBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomRight->myWorldPosition.x - 16.5f - myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
			myDirectionWhenEnteringWallRunningState = 1.0f;
			this->GetFSM()->changeState(HeroWallRunning::Instance());
		}
			

		/*if (myTileMap->IsDirectionWalkable(tileX + 1, tileY))
			mPosition.x += myPosXDirection * velocity;
		else
		{
			if ((myAABB->myOrigin.x + myAABB->halfX) <= myTileMap->GetTile2(tileX + 1, tileY)->myWorldPosition.x - 16.0f)
			//if (mPosition.x <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition.x += myPosXDirection * velocity;
			}
		}*/
	}
	else if (myNegXDirection < 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myNegXDirection * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
		bool midLeftFree = myTileMap->lastPlayerTileMidLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileMidLeft->myIsOneWayTile;
		bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;
		bool leftBlocking = /*bottomRightFree && */midLeftFree || topLeftFree;

		if (leftBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.x + 16.0f + myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
			myDirectionWhenEnteringWallRunningState = -1.0f;
			this->GetFSM()->changeState(HeroWallRunning::Instance());
		}
		/*if (myTileMap->IsDirectionWalkable(tileX - 1, tileY))
			mPosition.x += myNegXDirection * velocity;
		else
		{
			if ((myAABB->myOrigin.x - myAABB->halfX) >= myTileMap->GetTile2(tileX - 1, tileY)->myWorldPosition.x + 16.0f)
			//if (mPosition.x >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition.x += myNegXDirection * velocity;
			}
		}*/
	}
	/*if (myPosYDirection == 1.0f)
	{
		if (myTileMap->IsDirectionWalkable(tileX, tileY - 1))
			mPosition.y += myPosYDirection * velocity;
		else
		{
			if ((myAABB->myOrigin.y + myAABB->halfY) <= myTileMap->GetTile2(tileX, tileY - 1)->myWorldPosition.y - 16.0f)
			//if (mPosition.y <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition.y += myPosYDirection * velocity;
			}
		}
	}
	else if (myNegYDirection == -1.0f)
	{
		if (myTileMap->IsDirectionWalkable(tileX, tileY + 1))
			mPosition.y += myNegYDirection * velocity;
		else
		{
			if ((myAABB->myOrigin.y - myAABB->halfY) >= myTileMap->GetTile2(tileX, tileY + 1)->myWorldPosition.y + 16.0f)
			//if (mPosition.y >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition.y += myNegYDirection * velocity;
			}
			else
			{
				myStateMachine->changeState(HeroIdle::Instance());
			}
		}
	}
	myNegYDirection = myPosYDirection = myNegXDirection = myPosXDirection = 0.0f;*/
	myNegYDirection = myPosYDirection = myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;

	if(myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		mySwordAABB->myOrigin.x = mPosition.x + 30;
		mySwordAABB->myOrigin.y = mPosition.y + 1.5;
		mySwordSpriteAABB->myPosition.x = mySwordAABBRightX;
	}
	else
	{
		mySwordAABB->myOrigin.x = mPosition.x - 30;
		mySwordAABB->myOrigin.y = mPosition.y + 1.5;
		mySwordSpriteAABB->myPosition.x = mySwordAABBLeftX;
	}
	
}
void HeroEntity::CheckIfFalling()
{
	/*int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	if (myTileMap->IsDirectionWalkable(tileX, tileY + 1))
		myStateMachine->changeState(HeroFalling::Instance());*/
	if (!myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag)
	{
		if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
			myStateMachine->changeState(HeroMeleeFalling::Instance());
		else
			myStateMachine->changeState(HeroFalling::Instance());
	}
		//	myStateMachine->changeState(HeroFalling::Instance());
}
bool HeroEntity::LeftBlocking()
{
	bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;
	bool midLeftFree = myTileMap->lastPlayerTileMidLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileMidLeft->myIsOneWayTile;
	bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;
	bool leftBlocking =/* bottomLeftFree ||*/ midLeftFree || topLeftFree;
	return leftBlocking;
}
bool HeroEntity::RightBlocking()
{
	bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
	bool midRightFree = myTileMap->lastPlayerTileMidRight->myIsBlockingFlag && !myTileMap->lastPlayerTileMidRight->myIsOneWayTile;
	bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
	bool rightBlocking = /*bottomRightFree ||*/ midRightFree || topRightFree;
	return rightBlocking;
}
void HeroEntity::HandleWallSliding()
{
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	float fallingSpeed = -0.5f;

	float velocity = 1.6f;

	if (myPosXDirection > 0.0f)
	{

		glm::vec3 oldPosition = mPosition;
		mPosition.x += myPosXDirection * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
		bool midRightFree = myTileMap->lastPlayerTileMidRight->myIsBlockingFlag && !myTileMap->lastPlayerTileMidRight->myIsOneWayTile;
		bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
		bool rightBlocking = /*bottomRightFree ||*/ midRightFree || topRightFree;

		if (rightBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomRight->myWorldPosition.x - 16.5f - myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
		}

	}
	else if (myNegXDirection < 0.0f)
	{

		glm::vec3 oldPosition = mPosition;
		mPosition.x += myNegXDirection * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;
		bool midLeftFree = myTileMap->lastPlayerTileMidLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileMidLeft->myIsOneWayTile;
		bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;
		bool leftBlocking =/* bottomLeftFree ||*/ midLeftFree || topLeftFree;

		if (leftBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.x + 16.0f + myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
		}

	}


	glm::vec3 oldPosition = mPosition;
	mPosition.y += fallingSpeed;
	//myYVelocity += myGravity;
	//mPosition.y += myYVelocity/2.0f;
	myAABB->myOrigin.y = mPosition.y;
	myTileMap->SetPlayerTile2(myAABB);
	bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag;
	bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag;
	bool bottomRightOneWay = myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
	bool bottomLeftOneWay = myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;

	bool bottomBlocking = bottomLeftFree || bottomRightFree;
	bool bottomIsOneWayTile = bottomRightOneWay || bottomLeftOneWay;

	if (bottomIsOneWayTile)
	{
		if ((myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f))
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
			if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeIdle::Instance());
			else
				myStateMachine->changeState(HeroIdle::Instance());
		}
	}
	else if (bottomBlocking)
	{
		//This will prevent clipping upwards
		if ((myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f))
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
			if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeIdle::Instance());
			else
				myStateMachine->changeState(HeroIdle::Instance());
		}

	}


	myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;

}
void HeroEntity::HandleGravity()
{
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	float fallingSpeed = -5.5f;

	float velocity = 2.1f;

	if (myPosXDirection > 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myPosXDirection * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
		bool midRightFree = myTileMap->lastPlayerTileMidRight->myIsBlockingFlag && !myTileMap->lastPlayerTileMidRight->myIsOneWayTile;
		bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
		bool rightBlocking = /*bottomRightFree ||*/ midRightFree || topRightFree;

		if (rightBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomRight->myWorldPosition.x - 16.5f - myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
			myDirectionWhenEnteringFallState = 1.0f;
			this->GetFSM()->changeState(HeroWallSliding::Instance());
		//	return;
		}
	}
	else if (myNegXDirection < 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myNegXDirection * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;
		bool midLeftFree = myTileMap->lastPlayerTileMidLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileMidLeft->myIsOneWayTile;
		bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;
		bool leftBlocking =/* bottomLeftFree ||*/ midLeftFree || topLeftFree;

		if (leftBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.x + 16.0f + myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
			myDirectionWhenEnteringFallState = -1.0f;
			this->GetFSM()->changeState(HeroWallSliding::Instance());
	//		return;
		}

	}


	glm::vec3 oldPosition = mPosition;
	mPosition.y += fallingSpeed;
	//myYVelocity += myGravity;
	//mPosition.y += myYVelocity/2.0f;
	myAABB->myOrigin.y = mPosition.y;
	myTileMap->SetPlayerTile2(myAABB);
	bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag;
	bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag;
	bool bottomRightOneWay = myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
	bool bottomLeftOneWay = myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;

	bool bottomBlocking = bottomLeftFree || bottomRightFree;
	bool bottomIsOneWayTile = bottomRightOneWay || bottomLeftOneWay;

	if (bottomIsOneWayTile) 
	{
		if( (myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f) )
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
			if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeIdle::Instance());
			else
				myStateMachine->changeState(HeroIdle::Instance());
		}
	}
	else if (bottomBlocking)
	{
		//This will prevent clipping upwards
		if ((myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f))
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
			if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeIdle::Instance());
			else
				myStateMachine->changeState(HeroIdle::Instance());
		}

	}
	

	myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;

}
void HeroEntity::StartJump()
{
	myStartJumpTime = Clock->GetCurrentTimeInSeconds();
}
void HeroEntity::StartSliding(int direction)
{
	myStartSlidingTime = Clock->GetCurrentTimeInSeconds();
	if (direction < 0)
		myXVelocity = -3.0f;
	else
		myXVelocity = 3.0f;
}
void HeroEntity::StartDropKick(int direction)
{
	if (direction < 0)
		myXVelocity = -3.0f;
	else
		myXVelocity = 3.0f;
}
void HeroEntity::HandleAirSlam(float speed)
{
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	//float fallingSpeed = -6.0f;
	float fallingSpeed = speed;

	float velocity = 1.6f;


	glm::vec3 oldPosition = mPosition;
	mPosition.y += fallingSpeed;
	//myYVelocity += myGravity;
	//mPosition.y += myYVelocity/2.0f;
	myAABB->myOrigin.y = mPosition.y;
	myTileMap->SetPlayerTile2(myAABB);
	bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag;
	bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag;
	bool bottomRightOneWay = myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
	bool bottomLeftOneWay = myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;

	bool bottomBlocking = bottomLeftFree || bottomRightFree;
	bool bottomIsOneWayTile = bottomRightOneWay || bottomLeftOneWay;

	if (bottomIsOneWayTile)
	{
		if ((myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f))
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
			myStateMachine->changeState(HeroAttackSwordAir5::Instance());
		}
	}
	else if (bottomBlocking)
	{
		//This will prevent clipping upwards
		if ((myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f))
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
			myStateMachine->changeState(HeroAttackSwordAir5::Instance());
		}

	}


	myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;
}
void HeroEntity::HandleDropKick()
{
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	float fallingSpeed = -6.0f;

	float velocity = 1.6f;

	if (myXVelocity > 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myXVelocity * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
		bool midRightFree = myTileMap->lastPlayerTileMidRight->myIsBlockingFlag && !myTileMap->lastPlayerTileMidRight->myIsOneWayTile;
		bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
		bool rightBlocking = /*bottomRightFree ||*/ midRightFree || topRightFree;

		if (rightBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomRight->myWorldPosition.x - 16.5f - myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
		}
	}
	else if (myXVelocity < 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myXVelocity * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;
		bool midLeftFree = myTileMap->lastPlayerTileMidLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileMidLeft->myIsOneWayTile;
		bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;
		bool leftBlocking =/* bottomLeftFree ||*/ midLeftFree || topLeftFree;

		if (leftBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.x + 16.0f + myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
		}

	}


	glm::vec3 oldPosition = mPosition;
	mPosition.y += fallingSpeed;
	//myYVelocity += myGravity;
	//mPosition.y += myYVelocity/2.0f;
	myAABB->myOrigin.y = mPosition.y;
	myTileMap->SetPlayerTile2(myAABB);
	bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag;
	bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag;
	bool bottomRightOneWay = myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
	bool bottomLeftOneWay = myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;

	bool bottomBlocking = bottomLeftFree || bottomRightFree;
	bool bottomIsOneWayTile = bottomRightOneWay || bottomLeftOneWay;

	if (bottomIsOneWayTile)
	{
		if ((myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f))
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
			//myStateMachine->changeState(HeroIdle::Instance());
			if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeIdle::Instance());
			else
				myStateMachine->changeState(HeroIdle::Instance());
		}
	}
	else if (bottomBlocking)
	{
		//This will prevent clipping upwards
		if ((myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f))
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
		//	myStateMachine->changeState(HeroIdle::Instance());
			if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeIdle::Instance());
			else
				myStateMachine->changeState(HeroIdle::Instance());
		}

	}


	myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;
}
bool HeroEntity::IsOnSpikes()
{
	return myTileMap->lastPlayerTile->myIsSpikedFloor;
/*	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	if (myTileMap->IsDirectionWalkable(tileX, tileY + 1) && myTileMap->GetTile2(tileX, tileY + 1)->myIsSpikedFloor)
	{
		float length = glm::length(glm::vec2(mPosition.x, mPosition.y) - myTileMap->GetTile2(tileX, tileY + 1)->myWorldPosition);
		return length < 28.0f;
	}
	return false;*/
}
void HeroEntity::HandleJump()
{
/*	if(Clock->GetCurrentTime() - myStartJumpTime> 0.5f)
		myStateMachine->changeState(HeroFalling::Instance());*/
	if (myYVelocity < 5.5f)
	{
		myYVelocity = 5.5f;
		//myStateMachine->changeState(HeroFalling::Instance());
		if(!myShouldDropKick)
		{
			if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeFalling::Instance());
			else
				myStateMachine->changeState(HeroFalling::Instance());
		}
	}

	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	float jumpSpeed = 3.5f;

	/*if (!myTileMap->IsDirectionWalkable(tileX + 1, tileY))
	{
		mPosition.x = myTileMap->lastPlayerTile->myWorldPosition.x;
	}
	if (!myTileMap->IsDirectionWalkable(tileX - 1, tileY))
	{
		mPosition.x = myTileMap->lastPlayerTile->myWorldPosition.x;
	}*/

	//Step X then step y
	float velocity = 1.6f;
	if (myPosXDirection > 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myPosXDirection * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
		bool midRightFree = myTileMap->lastPlayerTileMidRight->myIsBlockingFlag && !myTileMap->lastPlayerTileMidRight->myIsOneWayTile;
		bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
		bool rightBlocking = /*bottomRightFree ||*/ midRightFree || topRightFree;

		if (rightBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomRight->myWorldPosition.x - 16.5f - myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
		}
	}
	else if (myNegXDirection < 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myNegXDirection * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomLeft->myIsOneWayTile;
		bool midLeftFree = myTileMap->lastPlayerTileMidLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileMidLeft->myIsOneWayTile;
		bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;
		bool leftBlocking =/* bottomLeftFree ||*/ midLeftFree || topLeftFree;

		if (leftBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.x + 16.0f + myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
		}

	}
	

	glm::vec3 oldPosition = mPosition;
	//mPosition.y += jumpSpeed;
	myYVelocity += myGravity;
	mPosition.y += myYVelocity;
	myAABB->myOrigin.y = mPosition.y;
	myTileMap->SetPlayerTile2(myAABB);
	bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
	bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;


	bool topBlocking = topLeftFree || topRightFree;

	if (topBlocking)
	{
		mPosition = oldPosition;
		mPosition.y = myTileMap->lastPlayerTileTopLeft->myWorldPosition.y - 16.0f - myAABB->halfY;
		myAABB->myOrigin.y = mPosition.y;
		myTileMap->SetPlayerTile2(myAABB);
		//myStateMachine->changeState(HeroFalling::Instance());
		if(!myShouldDropKick)
		{
			if (myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeFalling::Instance());
			else
				myStateMachine->changeState(HeroFalling::Instance());
		}

	}

	myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;
	//Last failcheck, need to look into clipping
	//if (!myTileMap->IsDirectionWalkable(tileX, tileY))
	//	mPosition.y = myTileMap->GetTile2(tileX, tileY + 1)->myWorldPosition.y;
}
void HeroEntity::HandleSliding()
{
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;

	float velocity = 1.6f;

	if (myXVelocity > 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myXVelocity * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomRightFree = myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
		bool midRightFree = myTileMap->lastPlayerTileMidRight->myIsBlockingFlag && !myTileMap->lastPlayerTileMidRight->myIsOneWayTile;
		bool topRightFree = myTileMap->lastPlayerTileTopRight->myIsBlockingFlag && !myTileMap->lastPlayerTileTopRight->myIsOneWayTile;
		bool rightBlocking = /*bottomRightFree && */midRightFree || topRightFree;

		if (rightBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomRight->myWorldPosition.x - 16.5f - myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
		}
	}
	else if (myXVelocity < 0.0f)
	{
		glm::vec3 oldPosition = mPosition;
		mPosition.x += myXVelocity * velocity;
		myAABB->myOrigin.x = mPosition.x;
		myTileMap->SetPlayerTile2(myAABB);

		bool bottomLeftFree = myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomRight->myIsOneWayTile;
		bool midLeftFree = myTileMap->lastPlayerTileMidLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileMidLeft->myIsOneWayTile;
		bool topLeftFree = myTileMap->lastPlayerTileTopLeft->myIsBlockingFlag && !myTileMap->lastPlayerTileTopLeft->myIsOneWayTile;
		bool leftBlocking = /*bottomRightFree && */midLeftFree || topLeftFree;

		if (leftBlocking)
		{
			mPosition = oldPosition;
			mPosition.x = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.x + 16.0f + myAABB->halfX;
			myAABB->myOrigin.x = mPosition.x;
			myTileMap->SetPlayerTile2(myAABB);
		}

	}

	myNegYDirection = myPosYDirection = myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;

	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		mySwordAABB->myOrigin.x = mPosition.x + 30;
		mySwordAABB->myOrigin.y = mPosition.y + 1.5;
		mySwordSpriteAABB->myPosition.x = mySwordAABBRightX;
	}
	else
	{
		mySwordAABB->myOrigin.x = mPosition.x - 30;
		mySwordAABB->myOrigin.y = mPosition.y + 1.5;
		mySwordSpriteAABB->myPosition.x = mySwordAABBLeftX;
	}
}
void HeroEntity::HandleDamaged(int damageRecieved)
{
	myAnimatedSprite->SetInverted(1);
	myIsDamaged = true;
	myDamageFrameCounter = 0;
	myHealth -= damageRecieved;
	//if (myHealth <= 0)
	//	GetFSM()->changeState(HeroDie::Instance());
}
void HeroEntity::Update()
{
	myHitEffect->Update();
	myBubblesSprite->Update();
	myMidnightSprite->Update();
	mySpellSprite->Update();
	//HandleMovement();
	//Really need to remove this nonsense and add it to the states instead
	if ((myPosXDirection == 0 && myPosYDirection == 0 && myNegXDirection == 0 && myNegYDirection == 0))
	{
		if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttackSword1::Instance()) && !myStateMachine->isInState(*HeroWallRunning::Instance()) && !myStateMachine->isInState(*HeroWallSliding::Instance()) && !myStateMachine->isInState(*HeroKnockedDownMelee::Instance()) && !myStateMachine->isInState(*HeroKnockedDownSword::Instance()) && !myStateMachine->isInState(*HeroMeleeGetUp::Instance()) && !myStateMachine->isInState(*HeroSwordGetUp::Instance()) && !myStateMachine->isInState(*HeroMeleePunch2::Instance()) && !myStateMachine->isInState(*HeroMeleePunch3::Instance()) && !myStateMachine->isInState(*HeroMeleePunch1::Instance()) && !myStateMachine->isInState(*HeroMeleeKick2::Instance()) && !myStateMachine->isInState(*HeroMeleeKick1::Instance()) && !myStateMachine->isInState(*HeroMeleeJump::Instance()) && !myStateMachine->isInState(*HeroMeleeDamaged::Instance()) && !myStateMachine->isInState(*HeroMeleeFalling::Instance()) && !myStateMachine->isInState(*HeroSheatheSword::Instance()) && !myStateMachine->isInState(*HeroMeleeDrawSword::Instance()) && !myStateMachine->isInState(*HeroMeleeIdle::Instance()) && !myStateMachine->isInState(*HeroAttackSwordAir5::Instance()) && !myStateMachine->isInState(*HeroCastSpell::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroDie::Instance()) && !myStateMachine->isInState(*HeroSliding::Instance()) && !myStateMachine->isInState(*HeroMeleeSliding::Instance()) && !myStateMachine->isInState(*HeroFireBowGround::Instance()) && !myStateMachine->isInState(*HeroAttackSword2::Instance()) && !myStateMachine->isInState(*HeroAttackSword3::Instance()) && !myStateMachine->isInState(*HeroIdle::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()) && !myStateMachine->isInState(*HeroDamaged::Instance()))
		{
			if(myStateMachine->GetNameOfCurrentState().find("Melee") != std::string::npos)
				myStateMachine->changeState(HeroMeleeIdle::Instance());
			else
				myStateMachine->changeState(HeroIdle::Instance());
		}	
	}
	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y - 2.5);
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

	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		mySwordAABB->myOrigin.x = mPosition.x + 30;
		mySwordAABB->myOrigin.y = mPosition.y + 1.5;
		mySwordSpriteAABB->myPosition.x = mySwordAABBRightX;
	}
	else
	{
		mySwordAABB->myOrigin.x = mPosition.x - 30;
		mySwordAABB->myOrigin.y = mPosition.y + 1.5;
		mySwordSpriteAABB->myPosition.x = mySwordAABBLeftX;
	}

	if (myDirectionWhenEnteringWallRunningState > 0.0f)
		myAnimatedSprite->myPosition.x = -10.0f;
	else if (myDirectionWhenEnteringWallRunningState < 0.0f)
		myAnimatedSprite->myPosition.x = 10.0f;
	else
	{
		myAnimatedSprite->myPosition.x = 0.0f;
	}
	/*if(!inAir)
		HandleGravity();
	if (inAir)
		HandleJump();*/
/*	if (myState == IDLE)
		myAnimatedSprite->SetAnimation("HeroIdle");
	if (myState == RUNNING)
		myAnimatedSprite->SetAnimation("HeroRun");
	if (myState == CROUCH)
		myAnimatedSprite->SetAnimation("HeroCrouch");
	if (myState == ATTACKING)
		myAnimatedSprite->SetAnimation("HeroAttack");*/
	
}
bool HeroEntity::HandleMessage(const Message& msg)
{
	return myStateMachine->HandleMessage(msg);
}
void HeroEntity::SpawnArrow()
{
	if (myFiredProjectile)
		return;
	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Adventurer Arrow", glm::vec3(mPosition.x + 26.0f, mPosition.y + 2.0f, mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
		myFiredProjectile = true;
	}
	else if (myAnimatedSprite->myHeading == Heading::LEFTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Adventurer Arrow", glm::vec3(mPosition.x - 26.0f, mPosition.y + 2.0f, mPosition.z), glm::vec3(-1.0f, 0.0f, 0.0f));
		myFiredProjectile = true;
	}
}
void HeroEntity::SpawnHitEffect()
{
	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(mPosition.x + 26.0f, mPosition.y + 2.0f, mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if (myAnimatedSprite->myHeading == Heading::LEFTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(mPosition.x - 26.0f, mPosition.y + 2.0f, mPosition.z + 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f));
	}
}
void HeroEntity::SpawnProjectile()
{
	if (myFiredProjectile)
		return;
	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Adventurer Projectile", glm::vec3(mPosition.x + 26.0f, mPosition.y + 2.0f, mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
		myFiredProjectile = true;
	}
	else if (myAnimatedSprite->myHeading == Heading::LEFTFACING)
	{
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Adventurer Projectile", glm::vec3(mPosition.x - 26.0f, mPosition.y + 2.0f, mPosition.z), glm::vec3(-1.0f, 0.0f, 0.0f));
		myFiredProjectile = true;
	}
}
void HeroEntity::processKeyBoard(int key, float deltaTime, int action)
{
	currentKeyInput = 0;

	myStateMachine->HandleInput(key, action);

}