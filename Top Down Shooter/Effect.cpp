#include "SimpleTimer.h"
#include "Effect.h"
#include "Group.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include <glm/gtc/matrix_transform.hpp>


Effect::Effect(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction, AnimatedSprite* animatedSprite, const std::string& animation, bool fading)
	:Entity(id, name), mPosition(myStartPosition), myAnimatedSprite(animatedSprite), myAnimation(animation), myAlpha(1.0f), myFading(fading)
{
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	myAnimatedSprite->SetAnimation(animation);
	mySprite->Add(myAnimatedSprite);

	if (myFading)
		myAnimatedSprite->SetInverted(2);
	
}
Effect::Effect(int id, const std::string& name, const glm::vec3& myStartPosition, AnimatedSprite* animatedSprite, const std::string& animation, bool fading)
	: Entity(id, name), mPosition(myStartPosition), myAnimatedSprite(animatedSprite), myAnimation(animation), myAlpha(1.0f), myFading(fading)
{
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	myAnimatedSprite->SetAnimation(animation);	
	mySprite->Add(myAnimatedSprite);

	if (myFading)
		myAnimatedSprite->SetInverted(2);
}
void Effect::Update()
{
	if (myFading)
	{
		myAnimatedSprite->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, myAlpha));
		myAnimatedSprite->Update();
		myAlpha -= 0.03f;
		if (myAlpha <= 0.0f)
			myAlpha = 0.0f;
	}
	else 
	{
		myAnimatedSprite->Update();
		if (myAnimatedSprite->IsDone())
			MarkForDeletion();
	}

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