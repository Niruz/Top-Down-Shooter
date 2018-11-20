#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "glm\vec3.hpp"
#include "AABB.h"
class TileMap;
class HellCatSprite;
class Group;
class Sprite;

//Simple enemy that patrols back and forth, might try and go for the player later
struct HellCatEntity : public Entity
{

	StateMachine<HellCatEntity>*  myStateMachine;
	StateMachine<HellCatEntity>*  GetFSM()const { return myStateMachine; }

	HellCatEntity(int id, const std::string& name);
	~HellCatEntity();

	void Update() override;
	bool HandleMessage(const Message& msg) override;

	void HandleMovement();

public:
	Group * mySprite;
	HellCatSprite* myAnimatedSprite;
	TileMap* myTileMap;
	glm::vec3 mPosition;
	AABB* myAABB;
	Sprite* myPlayerAABB;
	glm::vec3 startPatrol;
	glm::vec3 endPatrol;

	float myXDirection;
};