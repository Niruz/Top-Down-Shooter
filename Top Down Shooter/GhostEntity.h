#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "glm\vec3.hpp"
#include "AABB.h"
class TileMap;
class GhostSprite;
class Group;
class Sprite;

//Simple enemy that patrols back and forth, might try and go for the player later
struct GhostEntity : public Entity
{

	StateMachine<GhostEntity>*  myStateMachine;
	StateMachine<GhostEntity>*  GetFSM()const { return myStateMachine; }

	GhostEntity(int id, const std::string& name);
	~GhostEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();

public:
	Group * mySprite;
	GhostSprite* myAnimatedSprite;
	TileMap* myTileMap;
	glm::vec3 mPosition;
	AABB* myAABB;
	Sprite* myPlayerAABB;
	glm::vec3 startPatrol;
	glm::vec3 endPatrol;

	float myXDirection;
};


