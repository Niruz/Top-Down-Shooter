#include "SimpleTimer.h"
#include "Effect.h"
#include "Group.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include <glm/gtc/matrix_transform.hpp>


Effect::Effect(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction, AnimatedSprite* animatedSprite, const std::string& animation)
	:Entity(id, name), mPosition(myStartPosition), myAnimatedSprite(animatedSprite), myAnimation(animation)
{
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	myAnimatedSprite->SetAnimation(animation);
	mySprite->Add(myAnimatedSprite);
}
Effect::Effect(int id, const std::string& name, const glm::vec3& myStartPosition, AnimatedSprite* animatedSprite, const std::string& animation)
	: Entity(id, name), mPosition(myStartPosition), myAnimatedSprite(animatedSprite), myAnimation(animation)
{
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	myAnimatedSprite->SetAnimation(animation);	
	mySprite->Add(myAnimatedSprite);
}
void Effect::Update()
{
	myAnimatedSprite->Update();
	if (myAnimatedSprite->IsDone())
		MarkForDeletion();
}
bool Effect::HandleMessage(const Message& msg)
{
	return false;
}
void Effect::MarkForDeletion()
{
	SetMarkedForDeletion(true);
	mySprite->myMarkedForDeletion = true;
	myAnimatedSprite->myMarkedForDeletion = true;
}