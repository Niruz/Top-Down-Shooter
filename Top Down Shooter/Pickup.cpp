#include "SimpleTimer.h"
#include "Pickup.h"
#include "Group.h"
#include "Sprite.h"
#include "AABB.h"
#include "AnimatedSprite.h"
#include <glm/gtc/matrix_transform.hpp>

Pickup::Pickup(int id, const std::string& name, const glm::vec3& myStartPosition)
	:Entity(id, name), mPosition(myStartPosition)
{

}
void Pickup::Update()
{

}
bool Pickup::HandleMessage(const Message& msg)
{
	return false;
}
void Pickup::MarkForDeletion()
{
	SetMarkedForDeletion(true);
	mySprite->myMarkedForDeletion = true;
	myAnimatedSprite->myMarkedForDeletion = true;
	myHitboxAABB->myMarkedForDeletion = true;
}