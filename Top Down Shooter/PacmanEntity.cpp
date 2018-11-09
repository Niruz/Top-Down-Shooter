#include "PacmanEntity.h"
#include "Sprite.h"
#include "TileMap.h"
#include "glm\vec4.hpp"
void PacmanEntity::Update()
{

}
bool PacmanEntity::HandleMessage(const Message& msg)
{
	return true;
}

Sprite* PacmanEntity::GetSprite()
{
	return mySprite;
}
void PacmanEntity::SetSprite(Sprite* sprite)
{
	mySprite = sprite;
}
void PacmanEntity::ProcessKeyBoard(Movement direction, float deltaTime, TileMap& map)
{
	GLfloat velocity = 200.5f * deltaTime;

	/*int tileX = map.lastPlayerTile->myX;
	int tileY = map.lastPlayerTile->myY;
	glm::vec2 tilePos = map.lastPlayerTile->myWorldPosition;
*/


	if (direction == FORWARD)
	{
		//if (map.IsDirectionWalkable(tileX, tileY - 1))
			myDirection = glm::vec2(0.0f, 1.0f);

		//if (map.IsDirectionWalkable(tileX, tileY - 1))
			myPosition += glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
	/*	else
		{
			if (myPosition.y <= map.GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				myPosition += glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
			}
		}*/
	}
	else if (direction == BACKWARD)
	{
		//if (map.IsDirectionWalkable(tileX, tileY + 1))
			myPosition -= glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
		/*else
		{
			if (myPosition.y >= map.GetTile2(tileX, tileY)->myWorldPosition.y)
			{
				myPosition -= glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
			}
		}*/
	}
	else if (direction == RIGHT)
	{
	//	if (map.IsDirectionWalkable(tileX + 1, tileY))
			myPosition += glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
		/*else
		{
			if (myPosition.x <= map.GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				myPosition += glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
			}
		}*/
	}
	else if (direction == LEFT)
	{
		//if (map.IsDirectionWalkable(tileX - 1, tileY))
			myPosition -= glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
	/*	else
		{
			if (myPosition.x >= map.GetTile2(tileX, tileY)->myWorldPosition.x)
			{
				myPosition -= glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
			}
		}*/
	}
	myPosition.z = 0.1f;
	mySprite->SetPosition(glm::vec4(myPosition, 1.0f));
}