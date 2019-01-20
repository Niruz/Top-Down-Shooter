#include "EarthProjectile.h"
#include "Group.h"
#include "Sprite.h"
#include "AABB.h"
#include "AnimatedSprite.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "World.h"
#include "Level.h"
#include "EarthProjectileSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include "SoundManager.h"
EarthProjectile::EarthProjectile(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& direction)
	:BaseProjectileEntity(id, name, myStartPosition, direction)
{


	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 15.0f, 3.5f);
	myHitboxAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.3f, 1.0f), glm::vec2(30.0f, 7.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	//	mySprite->Add(myHitboxAABB);

	myAnimatedSprite = new EarthProjectileSprite(glm::vec4(0.0f, 0.0f, 0.3f, 1.0f), glm::vec2(32, 128), TextureMan->GetTexture("earth"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myAnimatedSprite->SetAnimation("EarthProjectile");

	isHeroProjectile = false;
	myShakeInfoBasicAttack = new ShakeInfo(500, 100, 6);
}
void EarthProjectile::Update()
{
	myAnimatedSprite->Update();
	myAnimatedSprite->myPosition.x = mPosition.x;
	myAnimatedSprite->myPosition.y = mPosition.y;
	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myHitboxAABB->myPosition = glm::vec4(mPosition.x, mPosition.y, mPosition.z - 0.3f, 1.0f);
	mPosition.y -= 7.0f;

	if (mPosition.y <= -530.0f)
	{
		SetMarkedForDeletion(true);
		mySprite->myMarkedForDeletion = true;
		myAnimatedSprite->myMarkedForDeletion = true;
		myHitboxAABB->myMarkedForDeletion = true;
		//
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(mPosition.x, -520.0f, mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		SoundMan->GetSoundEngine()->play2D("Audio/Golem Hit.wav", GL_FALSE);
		MessageMan->dispatchMessage(0, GetID(), 666, Msg_ShakeCamera, myShakeInfoBasicAttack);
	}


/*	mPosition.y += -5.0f;
	myAnimatedSprite->myPosition.y = mPosition.y;
	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myHitboxAABB->myPosition = glm::vec4(mPosition.x, mPosition.y, mPosition.z - 0.3f, 1.0f);

	if (glm::length(mPosition - myStartPos) > 500.0f && !GetMarkedForDeletion())
	{
		SetMarkedForDeletion(true);
		mySprite->myMarkedForDeletion = true;
		myAnimatedSprite->myMarkedForDeletion = true;
		myHitboxAABB->myMarkedForDeletion = true;
	}*/

}
bool EarthProjectile::HandleMessage(const Message& msg)
{
	return false;
}