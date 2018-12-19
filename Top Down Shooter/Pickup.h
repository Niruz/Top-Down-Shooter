#pragma once
#include "Entity.h"
#include "glm\vec3.hpp"

class Group;
class Sprite;
class AABB;
class AnimatedSprite;
struct Pickup : public Entity
{
	Pickup(int id, const std::string& name, const glm::vec3& myStartPosition);
	~Pickup()
	{
		delete myAABB;
	};

	virtual void Update();
	virtual bool HandleMessage(const Message& msg);

	Group * mySprite;
	AnimatedSprite* myAnimatedSprite;
	glm::vec3 mPosition;
	AABB* myAABB;
	Sprite* myHitboxAABB;
	std::string myType;
	void MarkForDeletion();
};
