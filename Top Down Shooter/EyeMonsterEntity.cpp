#include "EyeMonsterEntity.h"
#include "Group.h"
#include "EyeMonsterSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
# define M_PI           3.14159265358979323846  /* pi */

EyeMonsterEntity::EyeMonsterEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo) :
	BaseEnemy(id, name, myStartPosition, patrolTo)
{
	//THe facing is weird since all the enemies from the sprites look in the opposite direction from the start
	myAnimatedSprite = new EyeMonsterSprite(glm::vec4(mPosition.x, mPosition.y, myStartPosition.z, 1), glm::vec2(80, 80), TextureMan->GetTexture("eyemonster"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);
	myAnimatedSprite->SetAnimation("EyePatrol");
	myXDirection = 1.0f;
	angle = 0;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
}
EyeMonsterEntity::~EyeMonsterEntity()
{

}
void EyeMonsterEntity::Update()
{
	myAnimatedSprite->Update();
	HandleMovement();

}
bool EyeMonsterEntity::HandleMessage(const Message& msg)
{
	return false;
}
void EyeMonsterEntity::HandleMovement()
{
	if (myXDirection > 0.0f)
	{
		if (mPosition.x <= endPatrol.x)
		{
			mPosition.x += myXDirection;
			myAnimatedSprite->myPosition.x = mPosition.x;
			myAnimatedSprite->myPosition.y += sin(angle * M_PI/180.0f);
			angle+=5;
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
			myAnimatedSprite->myPosition.y += sin(angle * M_PI / 180.0f);
			angle += 5;
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
void EyeMonsterEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}