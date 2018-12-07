#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "glm\vec3.hpp"
#include "AABB.h"
#include "Group.h"
#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>

class TileMap;
class AnimatedSprite;
class Group;
class Sprite;

//Simple enemy that patrols back and forth, might try and go for the player later

struct BaseEnemy : public Entity
{
	
	BaseEnemy(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo, bool createAABB = true);
	virtual ~BaseEnemy() 
	{
		delete myAABB;
		delete myHitAABB;
	};

	virtual void Update() = 0;
	virtual bool HandleMessage(const Message& msg) = 0;

	virtual void HandleMovement() = 0;
	virtual void SetAnimation(const std::string& name) = 0;

	virtual void HandleDamaged(int damageRecieved) = 0;
	
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

	float myAttackTimer;

	int myHealth;
	int myDamageFrameCounter;
	bool myIsDamaged;


	Sprite* myHitSpriteAABB;
	AABB* myHitAABB;

	bool myIsActive;
};

