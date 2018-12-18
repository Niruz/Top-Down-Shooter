#pragma once
#include "Entity.h"
#include "glm\vec3.hpp"

class Group;
class Sprite;
class AnimatedSprite;
struct Effect : public Entity
{
	Effect(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction, AnimatedSprite* animatedSprite, const std::string& animation, bool fading = false);
	Effect(int id, const std::string& name, const glm::vec3& myStartPosition,  AnimatedSprite* animatedSprite, const std::string& animation, bool fading = false);
	~Effect() { };

	virtual void Update();
	virtual bool HandleMessage(const Message& msg);

	Group * mySprite;
	AnimatedSprite* myAnimatedSprite;
	glm::vec3 mPosition;
	std::string myAnimation;

	void MarkForDeletion();

	bool myFading;
	float myAlpha;
};
