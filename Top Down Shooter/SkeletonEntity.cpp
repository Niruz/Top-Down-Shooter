#include "SkeletonEntity.h"
#include "Group.h"
#include "SkeletonSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
SkeletonEntity::SkeletonEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo):
	BaseEnemy(id, name,myStartPosition, patrolTo)
{
	//THe facing is weird since all the enemies from the sprites look in the opposite direction from the start
	myAnimatedSprite = new SkeletonSprite(glm::vec4(mPosition.x, mPosition.y, 0.09f, 1), glm::vec2(44, 52), TextureMan->GetTexture("skeleton"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);
	myAnimatedSprite->SetAnimation("SkeletonWalk");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
}
SkeletonEntity::~SkeletonEntity()
{

}
void SkeletonEntity::Update() 
{
	myAnimatedSprite->Update();
	HandleMovement();

}
bool SkeletonEntity::HandleMessage(const Message& msg)
{
	return false;
}
void SkeletonEntity::HandleMovement()
{
	if (myXDirection > 0.0f)
	{
		if (mPosition.x <= endPatrol.x)
		{
			mPosition.x += myXDirection;
			myAnimatedSprite->myPosition.x = mPosition.x;
		}
		else
		{
			myXDirection = -1.0f;
			myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		}
	}
	if (myXDirection < 0.0f)
	{
		if (mPosition.x >= startPatrol.x)
		{
			mPosition.x += myXDirection;
			myAnimatedSprite->myPosition.x = mPosition.x;
		}
		else
		{
			myXDirection = 1.0f;
			myAnimatedSprite->SetHeading(Heading::LEFTFACING);
		}
	}

	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myPlayerAABB->myPosition = glm::vec4(mPosition, 1.0f);

}
void SkeletonEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}