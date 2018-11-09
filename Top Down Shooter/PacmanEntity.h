#pragma once
#include "Entity.h"
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"


enum Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class TileMap;
class Sprite;
class PacmanEntity : public Entity
{
public:
	PacmanEntity(int id, std::string name, const glm::vec3& pos, Sprite* sprite)
		: Entity(id, name), myPosition(pos), mySprite(sprite)
	{
		myDirection = glm::vec2(0.0f, 0.0f);
	}

	void Update() override;
    bool HandleMessage(const Message& msg) override;

	Sprite* GetSprite();
	void    SetSprite(Sprite* sprite);

	void ProcessKeyBoard(Movement direction, float deltaTime, TileMap& map);
private:

	glm::vec3 myPosition;
	glm::vec2 myDirection;
	Sprite* mySprite;
}; 