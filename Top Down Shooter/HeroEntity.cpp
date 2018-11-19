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


# define M_PI3           3.14159265358979323846  /* pi */

HeroEntity::HeroEntity(int id, const std::string& name) : Entity(id, name), translationMatrix(1.0f),
rotationMatrix(1.0f), modelMatrix(1.0f), mAngle(0.0f)
{
	mPosition = glm::vec3(0.0f, 0.0f, 0.1f);
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	myAnimatedSprite = new HeroSprite(glm::vec4(0.0f, 5.0f, 0.1f, 1), glm::vec2(100, 59), TextureMan->GetTexture("hero"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myDirection = glm::vec3(0.0f);

	currentKeyInput = 0;
	myState = IDLE;
	myPosXDirection = 0;
	myNegXDirection = 0;
	myPosYDirection = 0;
	myNegYDirection = 0;
	//SetAnimation("heroIdle");

	myStateMachine = new StateMachine<HeroEntity>(this);

	myStateMachine->setCurrentState(HeroIdle::Instance());
	myStateMachine->changeState(HeroIdle::Instance());

	inAir = false;
	myStartJumpTime = 0.0f;
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

	//Step X then step y
	if (myPosXDirection == 1.0f)
	{
		if (myTileMap->IsDirectionWalkable(tileX + 1, tileY))
			mPosition.x += myPosXDirection * velocity;
		else
		{
			if (mPosition.x <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition.x += myPosXDirection * velocity;
			}
		}
	}
	else if (myNegXDirection == -1.0f)
	{
		if (myTileMap->IsDirectionWalkable(tileX - 1, tileY))
			mPosition.x += myNegXDirection * velocity;
		else
		{
			if (mPosition.x >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition.x += myNegXDirection * velocity;
			}
		}
	}
	if (myPosYDirection == 1.0f)
	{
		if (myTileMap->IsDirectionWalkable(tileX, tileY - 1))
			mPosition.y += myPosYDirection * velocity;
		else
		{
			if (mPosition.y <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
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
			if (mPosition.y >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition.y += myNegYDirection * velocity;
			}
		}
	}
	myNegYDirection = myPosYDirection = myNegXDirection = myPosXDirection = 0.0f;
	mPosition.z = 0.1f;


}
void HeroEntity::CheckIfFalling()
{
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	if (myTileMap->IsDirectionWalkable(tileX, tileY + 1))
		myStateMachine->changeState(HeroFalling::Instance());
}
void HeroEntity::HandleGravity()
{
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	float fallingSpeed = -3.5f;
	if (myTileMap->IsDirectionWalkable(tileX, tileY + 1))
		mPosition.y += fallingSpeed;
	else
	{
		if (mPosition.y >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
		{
			mPosition.y += fallingSpeed;
		}
		else
		{
			myStateMachine->changeState(HeroIdle::Instance());
		}
	}
	mPosition.z = 0.1f;
}
void HeroEntity::StartJump()
{
	myStartJumpTime = Clock->GetCurrentTime();
}
void HeroEntity::HandleJump()
{
	if(Clock->GetCurrentTime() - myStartJumpTime> 0.5f)
		myStateMachine->changeState(HeroFalling::Instance());
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	float jumpSpeed = 3.5f;
	if (myTileMap->IsDirectionWalkable(tileX, tileY - 1))
		mPosition.y += jumpSpeed;
	else
	{
		if (mPosition.y >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
		{
			mPosition.y += jumpSpeed;
		}
		else
		{
			myStateMachine->changeState(HeroFalling::Instance());
		}
	}
}
void HeroEntity::Update()
{

	//HandleMovement();
	if ((myPosXDirection == 0 && myPosYDirection == 0 && myNegXDirection == 0 && myNegYDirection == 0))
	{
			if (!myStateMachine->isInState(*HeroCrouch::Instance()) && !myStateMachine->isInState(*HeroAttack::Instance()) && !myStateMachine->isInState(*HeroIdle::Instance()) && !myStateMachine->isInState(*HeroFalling::Instance()) && !myStateMachine->isInState(*HeroJumping::Instance()))
				myStateMachine->changeState(HeroIdle::Instance());
	}
	
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
	return false;
}
void HeroEntity::processKeyBoard(int key, float deltaTime, int action)
{
	currentKeyInput = 0;

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
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


	}

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