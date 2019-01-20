#include "PotionPickup.h"
#include "Group.h"
#include "Sprite.h"
#include "AABB.h"
#include "AnimatedSprite.h"
#include "PotionSprite.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "World.h"
#include "Level.h"
#include "Messages.h"
#include "SoundManager.h"
PotionPickup::PotionPickup(int id, const std::string& name, const glm::vec3& myStartPosition, const std::string& texture)
	:Pickup(id, name, myStartPosition)
{
	myType = texture;
	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 8.0f, 8.0f);
	myHitboxAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.3f, 1.0f), glm::vec2(16.0f, 16.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
		

	myAnimatedSprite = new PotionSprite(glm::vec4(mPosition.x, mPosition.y, mPosition.z + 0.2f, 1), glm::vec2(16, 16), TextureMan->GetTexture(texture), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myAnimatedSprite->SetAnimation("PotionMove");
	//myAnimatedSprite->SetInverted(2);
//	mySprite->Add(myHitboxAABB);
}
void PotionPickup::Update()
{
	myAnimatedSprite->Update();
	/*if (glm::length(mPosition - myStartPos) > 500.0f && !GetMarkedForDeletion())
	{
		SetMarkedForDeletion(true);
		mySprite->myMarkedForDeletion = true;
		myAnimatedSprite->myMarkedForDeletion = true;
		myHitboxAABB->myMarkedForDeletion = true;
	}*/

}
bool PotionPickup::HandleMessage(const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_YouveBeenPickedUp:
		GameWorld->GetActiveLevel()->SpawnEntity("Pickup Destroyed", glm::vec3(mPosition.x, mPosition.y, mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		SoundMan->GetSoundEngine()->play2D("Audio/pickup.ogg", GL_FALSE);
		MarkForDeletion();
		return true;
	}
	return false;

}