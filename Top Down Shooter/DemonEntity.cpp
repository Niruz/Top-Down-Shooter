#include "DemonEntity.h"
#include "Group.h"
#include "DemonSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
DemonEntity::DemonEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo) :
	BaseEnemy(id, name, myStartPosition, patrolTo)
{
	//THe facing is weird since all the enemies from the sprites look in the opposite direction from the start
	myAnimatedSprite = new DemonSprite(glm::vec4(mPosition.x, mPosition.y, 0.09f, 1), glm::vec2(240, 192), TextureMan->GetTexture("demon"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myAnimatedSprite->SetAnimation("DemonAttack");
	myXDirection = 1.0f;
	mySprite->Add(myPlayerAABB);
}
DemonEntity::~DemonEntity()
{

}
void DemonEntity::Update()
{
	myAnimatedSprite->Update();
	HandleMovement();

}
bool DemonEntity::HandleMessage(const Message& msg)
{
	return false;
}
void DemonEntity::HandleMovement()
{
	/*if (myXDirection > 0.0f)
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
	*/
	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myPlayerAABB->myPosition = glm::vec4(mPosition, 1.0f);

}
void DemonEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}