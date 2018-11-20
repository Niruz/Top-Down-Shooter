#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "glm\vec3.hpp"
#include "AABB.h"
class TileMap;
class Group;
class Sprite;
class AnimatedSprite;

//Simple enemy that patrols back and forth, might try and go for the player later
struct BaseEnemy : public Entity
{

	StateMachine<BaseEnemy>*  myStateMachine;
	StateMachine<BaseEnemy>*  GetFSM()const { return myStateMachine; }

	BaseEnemy(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
		: Entity(id, name), startPatrol(myStartPosition), endPatrol(patrolTo), mPosition(myStartPosition)
	{

	};
	virtual ~BaseEnemy() {};

	virtual void Update() = 0;
	virtual bool HandleMessage(const Message& msg) = 0;

	virtual void HandleMovement() = 0;

public:
	Group * mySprite;
	AnimatedSprite* myAnimatedSprite;
	TileMap* myTileMap;
	glm::vec3 mPosition;
	AABB* myAABB;
	Sprite* myPlayerAABB;
	glm::vec3 startPatrol;
	glm::vec3 endPatrol;

	float myXDirection;
};

