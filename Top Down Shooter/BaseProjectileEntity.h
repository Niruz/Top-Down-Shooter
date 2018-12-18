#pragma once
#include "Entity.h"
#include "glm\vec3.hpp"

class Group;
class Sprite;
class AABB;
class AnimatedSprite;
struct BaseProjectileEntity : public Entity
{
	BaseProjectileEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction);
	~BaseProjectileEntity() 
	{
		delete myAABB;
	};

	virtual void Update();
	virtual bool HandleMessage(const Message& msg);

	Group * mySprite;
	AnimatedSprite* myAnimatedSprite;
	glm::vec3 mPosition;
	glm::vec3 myStartPos;
	AABB* myAABB;
	Sprite* myHitboxAABB;
	glm::vec3 myDirection;
	
	void MarkForDeletion();

	bool isHeroProjectile;
};
