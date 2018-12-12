#include "SimpleTimer.h"
#include "BaseProjectileEntity.h"
#include "Group.h"
#include "Sprite.h"
#include "AABB.h"
#include "AnimatedSprite.h"
#include <glm/gtc/matrix_transform.hpp>


BaseProjectileEntity::BaseProjectileEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction)
	:Entity(id,name), mPosition(myStartPosition), myDirection(direction), myStartPos(myStartPosition), isHeroProjectile(false)
{
	
	//myAnimatedSprite = new DemonSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z, 1), glm::vec2(160, 144), TextureMan->GetTexture("demonidle"), Heading::RIGHTFACING);

}
void BaseProjectileEntity::Update() 
{

}
bool BaseProjectileEntity::HandleMessage(const Message& msg) 
{
	return false;
}
void BaseProjectileEntity::MarkForDeletion()
{
	SetMarkedForDeletion(true);
	mySprite->myMarkedForDeletion = true;
	myAnimatedSprite->myMarkedForDeletion = true;
	myHitboxAABB->myMarkedForDeletion = true;
}