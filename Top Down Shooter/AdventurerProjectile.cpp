#include "AdventurerProjectile.h"
#include "Group.h"
#include "Sprite.h"
#include "AABB.h"
#include "AnimatedSprite.h"
#include "AdventurerProjectileSprite.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "World.h"
#include "Level.h"
AdventurerProjectile::AdventurerProjectile(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction)
	:BaseProjectileEntity(id, name, myStartPosition, direction)
{


	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 15.0f, 3.5f);
	myHitboxAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.3f, 1.0f), glm::vec2(30.0f, 7.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
//	mySprite->Add(myHitboxAABB);

	myAnimatedSprite = new AdventurerProjectileSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.2f, 1), glm::vec2(34, 9), TextureMan->GetTexture("adventurerProjectile"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myAnimatedSprite->SetAnimation("AdventurerProjectile");
	if (myDirection.x > 0)
		myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	else
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);

	isHeroProjectile = true;

}
void AdventurerProjectile::Update()
{
	myAnimatedSprite->Update();
	mPosition.x += myDirection.x*4.0f;
	myAnimatedSprite->myPosition.x = mPosition.x;
	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myHitboxAABB->myPosition = glm::vec4(mPosition.x, mPosition.y, mPosition.z - 0.3f, 1.0f);

	if (glm::length(mPosition - myStartPos) > 500.0f && !GetMarkedForDeletion())
	{
		SetMarkedForDeletion(true);
		mySprite->myMarkedForDeletion = true;
		myAnimatedSprite->myMarkedForDeletion = true;
		myHitboxAABB->myMarkedForDeletion = true;
	}

}
bool AdventurerProjectile::HandleMessage(const Message& msg)
{
	return false;
}