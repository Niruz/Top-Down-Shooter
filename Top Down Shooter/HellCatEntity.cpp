#include "HellCatEntity.h"
#include "Group.h"
#include "HellCatSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
HellCatEntity::HellCatEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name,myStartPosition,patrolTo)
{
	myAnimatedSprite = new HellCatSprite(glm::vec4(mPosition.x, mPosition.y, 0.09f, 1), glm::vec2(96, 53), TextureMan->GetTexture("gato"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);

	myAnimatedSprite->SetAnimation("HellCatPatrol");
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
HellCatEntity::~HellCatEntity()
{

}
void HellCatEntity::Update()
{
	myAnimatedSprite->Update();
	HandleMovement();

}
bool HellCatEntity::HandleMessage(const Message& msg)
{
	return false;
}
void HellCatEntity::HandleMovement()
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
void HellCatEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}