#include "Player.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "ShaderManager.h"
#include <iostream>

#include "TileMap.h"
#include "Group.h"
#include "HeroSprite.h"
#include "TextureManager.h"
#include "GLFW\glfw3.h"
# define M_PI3           3.14159265358979323846  /* pi */

Player::Player() : translationMatrix(1.0f),
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
}
Player::~Player()
{

}
void Player::SetAnimation(const std::string& name)
{
	myAnimatedSprite->Reset();
	myAnimatedSprite->SetAnimation(name);
}
void Player::updatePosition(const glm::vec3& position)
{
	mPosition += position;
}
void Player::setPosition(const glm::vec3& pos)
{
	mPosition = pos;
	translationMatrix = glm::translate(translationMatrix, mPosition);
}
void Player::setDirection(const glm::vec2& direction)
{
	float angle = atan2(direction.y, direction.x);// *(180.0f / M_PI3);
	float degreesRadians = (M_PI3 / 180)*90.0f;

	mAngle = angle - degreesRadians;

	//std::cout << "angle: " << mAngle << std::endl;
}
void Player::render(const Camera& camera)
{
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, mAngle, glm::vec3(0.0f, 0.0f, 1.0f));

	translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, mPosition);

	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(16, 16, 16));

	modelMatrix =  camera.mTranslationMatrix* translationMatrix *rotationMatrix *scaleMatrix;
	//modelMatrix = rotationMatrix;

	ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, modelMatrix);

	mTexture->bind();

	mMesh->render();


	mTexture->unbind();
}
float Player::map(float s, float a1, float a2, float b1, float b2)
{
	return b1 + (s - a1)*(b2 - b1) / (a2 - a1);
}
void Player::UpdateTransformationMatrix(const Camera& camera)
{
	
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, mAngle, glm::vec3(0.0f, 0.0f, 1.0f));

	translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, mPosition);

	//glm::mat4 scaleMatrix = glm::mat4(1.0f);
	//scaleMatrix = glm::scale(scaleMatrix, glm::vec3(16, 16, 16));

	modelMatrix = camera.mTranslationMatrix* translationMatrix *rotationMatrix;// *scaleMatrix;
	//modelMatrix = rotationMatrix;

	mySprite->SetTransformationMatrix(modelMatrix);
}
void Player::HandleMovement()
{
	if (myState == CROUCH)
		return;
	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	glm::vec2 tilePos = myTileMap->lastPlayerTile->myWorldPosition;

	float yPos = mPosition.y;
	float xPos = mPosition.x;
	float tileX2 = (yPos / 32.0f) + (xPos / 32.0f);

	float tileY2 = (xPos / 32.0f) - (yPos / 32.0f);

	float tileX3 = round(xPos / 32.0f) * 32.0f;
	float tileY3 = round(yPos / 32.0f) * 32.0f;

	float shitX = this->map(mPosition.x, -320, 288, 0, 19);
	float shitY = this->map(mPosition.y, 160, -192, 0, 11);


	float roundX2 = round(shitX);
	float roundY2 = round(shitY);



	glm::vec2 startRange(-320.0f, 192);
	glm::vec2 endRange(288.0f, -192.0f);

	glm::vec2 range = endRange - startRange;

	glm::vec2 test = glm::vec2(mPosition.x / range.x, mPosition.y / range.y);

	glm::vec2 testTilePos;
	testTilePos.x = glm::floor(test.x);
	testTilePos.y = glm::floor(test.y);

	glm::vec2 test2;
	test.x = mPosition.x / 32.0f;
	test.x = mPosition.y / 32.0f;
	int shit = 5;

	float a = -320.0f;
	float b = 288.0f;
	float c = 0;
	float d = 19;


	float a2 = 192;
	float b2 = -192;
	float c2 = 0;
	float d2 = 11;
	float testNew = ((mPosition.x - a) * ((d - c) / (b - a))) + c;
	float testNew2 = ((mPosition.y - a2) * ((d2 - c2) / (b2 - a2))) + c2;

	float roundX = round(testNew);
	float roundY = round(testNew2);

	float velocity = 1.6f;

	//Step X then step y
	if (myPosXDirection == 1.0f)
	{
		if (myTileMap->IsDirectionWalkable(tileX + 1, tileY ))
			mPosition.x += myPosXDirection * velocity;
		else
		{
			if (mPosition.x <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition.x += myPosXDirection * velocity;
			}
		}
	}
	if(myNegXDirection == -1.0f)
	{
		if (myTileMap->IsDirectionWalkable(tileX-1, tileY))
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
		if (myTileMap->IsDirectionWalkable(tileX , tileY -1))
			mPosition.y += myPosYDirection * velocity;
		else
		{
			if (mPosition.y <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition.y += myPosYDirection * velocity;
			}
		}
	}
	if (myNegYDirection == -1.0f)
	{
		if (myTileMap->IsDirectionWalkable(tileX , tileY + 1))
			mPosition.y += myNegYDirection * velocity;
		else
		{
			if (mPosition.y >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition.y += myNegYDirection * velocity;
			}
		}
	}
	mPosition.z = 0.1f;


	/*
	if (currentKeyInput == GLFW_KEY_W)
	{
		if (myTileMap->IsDirectionWalkable(tileX, tileY - 1))
			mPosition += myDirection *velocity;
		else
		{
			if (mPosition.y <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition += myDirection *velocity;
			}
		}
	}
	else if (currentKeyInput == GLFW_KEY_S)
	{
		if (myTileMap->IsDirectionWalkable(tileX, tileY + 1))
			mPosition += myDirection *velocity;
		else
		{
			if (mPosition.y >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition += myDirection *velocity;
			}
		}
	}
	else if (currentKeyInput == GLFW_KEY_D)
	{
		if (myTileMap->IsDirectionWalkable(tileX + 1, tileY))
			mPosition += myDirection *velocity;
		else
		{
			if (mPosition.x <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition += myDirection *velocity;
			}
		}
	}
	else if (currentKeyInput == GLFW_KEY_A)
	{
		if (myTileMap->IsDirectionWalkable(tileX - 1, tileY))
			mPosition += myDirection *velocity;
		else
		{
			if (mPosition.x >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition += myDirection *velocity;
			}
		}
	}
	mPosition.z = 0.1f;*/
}
void Player::Update()
{
/*	float velocity = 1.6;
	mPosition += myDirection * velocity;
	mPosition.z = 0.1f;
	*/
	HandleMovement();
	if(myState == IDLE)
		myAnimatedSprite->SetAnimation("HeroIdle");
	if (myState == RUNNING)
		myAnimatedSprite->SetAnimation("HeroRun");
	if (myState == CROUCH)
		myAnimatedSprite->SetAnimation("HeroCrouch");
	if (myState == ATTACKING)
		myAnimatedSprite->SetAnimation("HeroAttack");
	myAnimatedSprite->Update();
}
void Player::processKeyBoard(int key, GLfloat deltaTime, int action)
{
	/*GLfloat velocity = 200.5f * deltaTime;

	int tileX = myTileMap->lastPlayerTile->myX;
	int tileY = myTileMap->lastPlayerTile->myY;
	glm::vec2 tilePos = myTileMap->lastPlayerTile->myWorldPosition;

	float yPos = mPosition.y;
	float xPos = mPosition.x;
	float tileX2 = (yPos / 32.0f) + (xPos / 32.0f);

	float tileY2 = (xPos / 32.0f) - (yPos / 32.0f);

	float tileX3 = round(xPos / 32.0f) * 32.0f;
	float tileY3 = round(yPos / 32.0f) * 32.0f;

	float shitX = this->map(mPosition.x, -320, 288, 0, 19 );
	float shitY = this->map(mPosition.y, 160, -192, 0, 11 );


	float roundX2 = round(shitX);
	float roundY2 = round(shitY);



	glm::vec2 startRange(-320.0f, 192);
	glm::vec2 endRange(288.0f, -192.0f);

	glm::vec2 range = endRange - startRange;

	glm::vec2 test = glm::vec2(mPosition.x / range.x, mPosition.y / range.y);

	glm::vec2 testTilePos;
	testTilePos.x = glm::floor(test.x);
	testTilePos.y = glm::floor(test.y);

	glm::vec2 test2;
	test.x = mPosition.x / 32.0f;
	test.x = mPosition.y / 32.0f;
	int shit = 5;

	float a = -320.0f;
	float b = 288.0f;
	float c = 0;
	float d = 19;


	float a2 = 192;
	float b2 = -192;
	float c2 = 0;
	float d2 = 11;
	float testNew = ((mPosition.x - a) * ((d - c) / (b - a))) + c;
	float testNew2 = ((mPosition.y - a2) * ((d2 - c2) / (b2 - a2))) + c2;

	float roundX = round(testNew);
	float roundY = round(testNew2);


	int hohh = 5;*/

	currentKeyInput = 0;

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		currentKeyInput = GLFW_KEY_W;
		//myDirection = glm::vec3(0.0f, 1.0f, 0.0f);
		myPosYDirection = 1.0f;
		myState = RUNNING;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		myPosYDirection = 0.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		currentKeyInput = GLFW_KEY_S;
		//myDirection -= glm::vec3(0.0f, 1.0f, 0.0f);
		myNegYDirection = -1.0f;
		myState = RUNNING;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		myNegYDirection = 0.0f;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		currentKeyInput = GLFW_KEY_D;
		//myDirection = glm::vec3(1.0f, 0.0f, 0.0f);
		myPosXDirection = 1.0f;
		myState = RUNNING;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		myPosXDirection = 0.0f;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		currentKeyInput = GLFW_KEY_A;
		//myDirection -= glm::vec3(1.0f, 0.0f, 0.0f);
		myNegXDirection = -1.0f;
		myState = RUNNING;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		myNegXDirection = 0.0f;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		//myAnimatedSprite->SetAnimation("HeroCrouch");
		currentKeyInput = GLFW_KEY_C;

		//myPosXDirection = myPosYDirection = myNegXDirection = myNegYDirection = 0.0f;

		myState = CROUCH;
		//myXDirection = myYDirection = 0.0f;
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		currentKeyInput = GLFW_KEY_V;
		myState = ATTACKING;

	}

	if (currentKeyInput == 0)
	{
		myState = IDLE;
	}
	if (myPosXDirection == 0 && myPosYDirection == 0 && myNegXDirection == 0 && myNegYDirection == 0 && myState != CROUCH && myState != ATTACKING)
		myState = IDLE;

/*	if (myPosXDirection != 0.0f || myPosYDirection != 0.0f || myNegXDirection != 0.0f || myNegYDirection != 0.0f)
	{
		myState = RUNNING;
	}	*/








/*
	
	if (key == GLFW_KEY_W)
	{
		myAnimatedSprite->SetAnimation("HeroRun");
		if (myTileMap->IsDirectionWalkable(tileX, tileY - 1))
			mPosition += glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
		else
		{
			if (mPosition.y <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y )
			{
				mPosition += glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
			}
		}
	}
	else if (key == GLFW_KEY_S)
	{
		myAnimatedSprite->SetAnimation("HeroRun");
		if (myTileMap->IsDirectionWalkable(tileX , tileY + 1))
			mPosition -= glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
		else
		{
			if (mPosition.y >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition -= glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
			}
		}
	}	
	else if (key == GLFW_KEY_D)
	{
		myAnimatedSprite->SetAnimation("HeroRun");
		if (myTileMap->IsDirectionWalkable(tileX + 1, tileY ))
			mPosition += glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
		else
		{
			if (mPosition.x <= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition += glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
			}
		}
	}	
	else if (key == GLFW_KEY_A)
	{
		myAnimatedSprite->SetAnimation("HeroRun");
		if (myTileMap->IsDirectionWalkable(tileX - 1, tileY))
			mPosition -= glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
		else
		{
			if (mPosition.x >= myTileMap->GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition -= glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
			}
		}
	}
	else
	{
		myAnimatedSprite->Reset();
		myAnimatedSprite->SetAnimation("HeroIdle");
	}
	mPosition.z = 0.1f;*/
	//mySprite->SetPosition(glm::vec4(mPosition, 1.0f));
		
	/*	else if (direction == UP)
	mPosition += mWorldUp*velocity;
	else if (direction == DOWN)
	mPosition -= mWorldUp*velocity;*/
}
/*
northWalkable = IsDirectionWalkable(currentTile->myX, currentTile->myY - 1);
eastWalkable = IsDirectionWalkable(currentTile->myX + 1, currentTile->myY);
southWalkable = IsDirectionWalkable(currentTile->myX, currentTile->myY + 1);
westWalkable = IsDirectionWalkable(currentTile->myX - 1, currentTile->myY);*/