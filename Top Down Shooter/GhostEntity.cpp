#include "GhostEntity.h"
#include "Group.h"
#include "GhostSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
GhostEntity::GhostEntity(int id, const std::string& name) :
	Entity(id, name)
{
	mPosition = glm::vec3(-128.0f, -32.0f, 0.1f);
	mySprite = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.1f)));
	//THe facing is weird since all the enemies from the sprites look in the opposite direction from the start
	myAnimatedSprite = new GhostSprite(glm::vec4(-128.0f, -32.0f, 0.09f, 1), glm::vec2(37, 65), TextureMan->GetTexture("ghost"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);

	myAnimatedSprite->SetAnimation("GhostPatrol");

	endPatrol = glm::vec3(-128.0f, 32.0f, 0.1f);
	startPatrol = glm::vec3(-128.0f, -96.0f, 0.1f);

	myXDirection = 1.0f;

	myAABB = new AABB(glm::vec2(mPosition.x, mPosition.y), 16.0f, 16.0f);

	myPlayerAABB = new Sprite(glm::vec4(mPosition.x, mPosition.y, 0.2f, 1.0f), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
	//mySprite->Add(myPlayerAABB);
}
GhostEntity::~GhostEntity()
{

}
void GhostEntity::Update()
{
	myAnimatedSprite->Update();

	if (myXDirection > 0.0f)
	{
		if (mPosition.y <= endPatrol.y)
		{
			mPosition.y += myXDirection;
			myAnimatedSprite->myPosition.y = mPosition.y;
		}
		else
		{
			myXDirection = -1.0f;
			myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		}
	}
	if (myXDirection < 0.0f)
	{
		if (mPosition.y >= startPatrol.y)
		{
			mPosition.y += myXDirection;
			myAnimatedSprite->myPosition.y = mPosition.y;
		}
		else
		{
			myXDirection = 1.0f;
			myAnimatedSprite->SetHeading(Heading::LEFTFACING);
		}
	}

	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myPlayerAABB->myPosition = glm::vec4(mPosition, 1.0f);
	//	glm::mat4  translationMatrix = glm::mat4(1.0f);
	//translationMatrix = glm::translate(translationMatrix, mPosition);

	//modelMatrix = camera.mTranslationMatrix* translationMatrix *rotationMatrix;


	//mySprite->SetTransformationMatrix(translationMatrix);
}
bool GhostEntity::HandleMessage(const Message& msg)
{
	return false;
}
void GhostEntity::HandleMovement()
{

}
