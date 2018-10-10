#include "Player.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "ShaderManager.h"
#include <iostream>

#include "TileMap.h"
# define M_PI3           3.14159265358979323846  /* pi */

Player::Player() : translationMatrix(1.0f),
rotationMatrix(1.0f), modelMatrix(1.0f), mAngle(0.0f)
{
	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
}
Player::~Player()
{

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

	std::cout << "angle: " << mAngle << std::endl;
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

void Player::processKeyBoard(camMovement direction, GLfloat deltaTime, TileMap& map)
{
	GLfloat velocity = 200.5f * deltaTime;

	int tileX = map.lastPlayerTile->myX;
	int tileY = map.lastPlayerTile->myY;
	glm::vec2 tilePos = map.lastPlayerTile->myWorldPosition;

	if (direction == FORWARD) 
	{
		if (map.IsDirectionWalkable(tileX, tileY - 1))
			mPosition += glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
		else
		{
			if (mPosition.y <= map.GetTile2(tileX, tileY)->myWorldPosition.y )
			{
				mPosition += glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
			}
		}
	}
	else if (direction == BACKWARD)
	{
		if (map.IsDirectionWalkable(tileX , tileY + 1))
			mPosition -= glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
		else
		{
			if (mPosition.y >= map.GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				mPosition -= glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
			}
		}
	}	
	else if (direction == RIGHT)
	{
		if (map.IsDirectionWalkable(tileX + 1, tileY ))
			mPosition += glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
		else
		{
			if (mPosition.x <= map.GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition += glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
			}
		}
	}	
	else if (direction == LEFT)
	{
		if (map.IsDirectionWalkable(tileX - 1, tileY))
			mPosition -= glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
		else
		{
			if (mPosition.x >= map.GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				mPosition -= glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
			}
		}
	}
		
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