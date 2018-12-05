#include "NecromancerProjectile.h"
#include "Group.h"
#include "Sprite.h"
#include "AABB.h"
#include "AnimatedSprite.h"
#include "NecromancerProjectileSprite.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "World.h"
#include "Level.h"
NecromancerProjectile::NecromancerProjectile(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction)
	:BaseProjectileEntity(id, name, myStartPosition, direction)
{


	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 30.0f, 7.0f);
	myHitboxAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.3f, 1.0f), glm::vec2(60.0f, 14.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	//mySprite->Add(myHitboxAABB);

	myAnimatedSprite = new NecromancerProjectileSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z+0.2f, 1), glm::vec2(68, 18), TextureMan->GetTexture("necromancerProjectile"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myAnimatedSprite->SetAnimation("NecromancerProjectile");
	if (myDirection.x > 0)
		myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	else
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);

}
void NecromancerProjectile::Update()
{
	myAnimatedSprite->Update();
	mPosition.x += myDirection.x*2.0f;
	myAnimatedSprite->myPosition.x = mPosition.x;
	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myHitboxAABB->myPosition = glm::vec4(mPosition.x, mPosition.y, mPosition.z - 0.3f, 1.0f);

	if (glm::length(mPosition - myStartPos) > 1000.0f && !GetMarkedForDeletion())
	{
		SetMarkedForDeletion(true);
		mySprite->myMarkedForDeletion = true;
		myAnimatedSprite->myMarkedForDeletion = true;
		myHitboxAABB->myMarkedForDeletion = true;
	}
		
}
bool NecromancerProjectile::HandleMessage(const Message& msg)
{
	return false;
}