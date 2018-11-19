#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "glm\vec3.hpp"
#include "AABB.h"
class TileMap;
class SkeletonSprite;
class Group;
class Sprite;

//Simple enemy that patrols back and forth, might try and go for the player later
struct SkeletonEntity : public Entity
{

	StateMachine<SkeletonEntity>*  myStateMachine;
	StateMachine<SkeletonEntity>*  GetFSM()const { return myStateMachine; }

	SkeletonEntity(int id, const std::string& name);
	~SkeletonEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();

public:
	Group* mySprite;
	SkeletonSprite* myAnimatedSprite;
	TileMap* myTileMap;
	glm::vec3 mPosition;
	AABB* myAABB;
	Sprite* myPlayerAABB;
	glm::vec3 startPatrol;
	glm::vec3 endPatrol;

	float myXDirection;
};


