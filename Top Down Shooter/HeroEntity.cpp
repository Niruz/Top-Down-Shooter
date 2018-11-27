#include "HeroEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "ShaderManager.h"
#include <iostream>

#include "TileMap.h"
#include "Group.h"
#include "HeroSprite.h"
#include "TextureManager.h"
#include "GLFW\glfw3.h"
#include "GothicVaniaHeroStates.h"
#include "Sprite.h"

# define M_PI3           3.14159265358979323846  /* pi */

HeroEntity::HeroEntity(int id, const std::string& name) : Entity(id, name), translationMatrix(1.0f),
rotationMatrix(1.0f), modelMatrix(1.0f), mAngle(0.0f)
{
	mPosition = glm::vec3(0.0f, 0.0f, 0.1f);
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	myAnimatedSprite = new HeroSprite(glm::vec4(0.0f, 5.0f, 0.1f, 1), glm::vec2(100, 59), TextureMan->GetTexture("hero"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myDirection = glm::vec3(0.0f);
	myPlayerAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y-2.5, 0.2f, 1.0f),glm::vec2(18.0f,44.0f),glm::vec4(0.0f,1.0f,0.0f,0.5f));
	//mySprite->Add(myPlayerAABB);

	

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

	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y - 2.5), 9.0f, 22.0f);
}
HeroEntity::~HeroEntity()
{
	delete myStateMachine;
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
void HeroEntity::HandleMovement()
{
	if (myStateMachine->isInState(*HeroCrouch::Instance()) || myStateMachine->isInState(*HeroAttack::Instance()))
		return;
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;

	float velocity = 1.6f;

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
	
	
}
void HeroEntity::CheckIfFalling()
{
	/*int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	if (myTileMap->IsDirectionWalkable(tileX, tileY + 1))
		myStateMachine->changeState(HeroFalling::Instance());*/
	if(!myTileMap->lastPlayerTileBottomRight->myIsBlockingFlag && !myTileMap->lastPlayerTileBottomLeft->myIsBlockingFlag)
		myStateMachine->changeState(HeroFalling::Instance());
}
void HeroEntity::HandleGravity()
{
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	float fallingSpeed = -4.0f;

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
		if( (myAABB->myOrigin.y - myAABB->halfY) > (myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 10.0f) )
		{
			mPosition = oldPosition;
			mPosition.y = myTileMap->lastPlayerTileBottomLeft->myWorldPosition.y + 16.0f + myAABB->halfY;
			myAABB->myOrigin.y = mPosition.y;
			myTileMap->SetPlayerTile2(myAABB);
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
			myStateMachine->changeState(HeroIdle::Instance());
		}

	}
	

	myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;

}
void HeroEntity::StartJump()
{
	myStartJumpTime = Clock->GetCurrentTime();
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
	if (myYVelocity < 3.5f)
	{
		myYVelocity = 3.5f;
		myStateMachine->changeState(HeroFalling::Instance());
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
		myStateMachine->changeState(HeroFalling::Instance());
	}

	myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;
	//Last failcheck, need to look into clipping
	//if (!myTileMap->IsDirectionWalkable(tileX, tileY))
	//	mPosition.y = myTileMap->GetTile2(tileX, tileY + 1)->myWorldPosition.y;
}
void HeroEntity::HandleDamaged()
{

}
void HeroEntity::Update()
{

	//HandleMovement();
	if ((myPosXDirection == 0 && myPosYDirection == 0 && myNegXDirection == 0 && myNegYDirection == 0))
	{
			if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroIdle::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()))
				myStateMachine->changeState(HeroIdle::Instance());
	}
	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y - 2.5);
	myStateMachine->update();
	
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
	myStateMachine->HandleMessage(msg);
	return true;
}
void HeroEntity::processKeyBoard(int key, float deltaTime, int action)
{
	currentKeyInput = 0;

	myStateMachine->HandleInput(key, action);

	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroRunning::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()))
			myStateMachine->changeState(HeroRunning::Instance());
		currentKeyInput = GLFW_KEY_W;
		myPosYDirection = 1.0f;
		myState = RUNNING;
		
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		if(myStateMachine->isInState(*HeroRunning::Instance()))
			myStateMachine->changeState(HeroIdle::Instance());
		myPosYDirection = 0.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroRunning::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()))
			myStateMachine->changeState(HeroRunning::Instance());
		currentKeyInput = GLFW_KEY_S;
		myNegYDirection = -1.0f;
		myState = RUNNING;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		if (myStateMachine->isInState(*HeroRunning::Instance()))
			myStateMachine->changeState(HeroIdle::Instance());
		myNegYDirection = 0.0f;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroRunning::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()))
			myStateMachine->changeState(HeroRunning::Instance());
		currentKeyInput = GLFW_KEY_D;
		myPosXDirection = 1.0f;
		myState = RUNNING;
		if (!myStateMachine->isInState(*HeroAttack::Instance()))
			myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		if (myStateMachine->isInState(*HeroRunning::Instance()))
			myStateMachine->changeState(HeroIdle::Instance());
		myPosXDirection = 0.0f;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroRunning::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()))
			myStateMachine->changeState(HeroRunning::Instance());
		currentKeyInput = GLFW_KEY_A;
		myNegXDirection = -1.0f;
		myState = RUNNING;
		if(!myStateMachine->isInState(*HeroAttack::Instance()))
			myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		if (myStateMachine->isInState(*HeroRunning::Instance()))
			myStateMachine->changeState(HeroIdle::Instance());
		myNegXDirection = 0.0f;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		//myAnimatedSprite->SetAnimation("HeroCrouch");
		currentKeyInput = GLFW_KEY_C;

		//myPosXDirection = myPosYDirection = myNegXDirection = myNegYDirection = 0.0f;

		myState = CROUCH;
		//myXDirection = myYDirection = 0.0f;
		if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()))
			myStateMachine->changeState(HeroCrouch::Instance());
		else if (myStateMachine->isInState(*HeroCrouch::Instance()))
			myStateMachine->changeState(HeroIdle::Instance());

	}
	if (key == GLFW_KEY_C && action == GLFW_RELEASE)
	{
		if(myStateMachine->isInState(*HeroCrouch::Instance()))
			myStateMachine->changeState(HeroIdle::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		currentKeyInput = GLFW_KEY_V;
		myState = ATTACKING;

		if(!myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()))
			myStateMachine->changeState(HeroAttack::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		currentKeyInput = GLFW_KEY_SPACE;
		if (!myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()))
			myStateMachine->changeState(HeroJumping::Instance());

		
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		currentKeyInput = GLFW_KEY_SPACE;
		if (myStateMachine->isInState(*HeroJumping::Instance()))
			myStateMachine->changeState(HeroFalling::Instance());


	}*/

	if (currentKeyInput == 0)
	{
	//	myStateMachine->changeState(HeroIdle::Instance());
	}
	if ((myPosXDirection == 0 && myPosYDirection == 0 && myNegXDirection == 0 && myNegYDirection))
	{
	//	if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()))
		//	myStateMachine->changeState(HeroIdle::Instance());
	}
		
/*	if ((myPosXDirection == -1* myNegXDirection) || (myPosYDirection == -1 * myNegYDirection))
	{
		if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroIdle::Instance()))
			myStateMachine->changeState(HeroIdle::Instance());
	}*/
}