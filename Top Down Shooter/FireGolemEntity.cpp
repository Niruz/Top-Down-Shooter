#include "SimpleTimer.h"
#include "FireGolemEntity.h"
#include "Group.h"
#include "FireGolemSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaFireGolemStates.h"
FireGolemEntity::FireGolemEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo)
	: BaseEnemy(id, name, myStartPosition, patrolTo)
{
	myAnimatedSprite = new FireGolemSprite(glm::vec4(mPosition.x, mPosition.y, 0.09f, 1), glm::vec2(64, 57), TextureMan->GetTexture("firegolem"), Heading::LEFTFACING);
	mySprite->Add(myAnimatedSprite);

	myAnimatedSprite->SetAnimation("FireGolemRun");
	myXDirection = 1.0f;
	if (myStartPosition.x > patrolTo.x)
	{
		myXDirection = -1.0f;
		myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
		glm::vec3 temp = startPatrol;
		startPatrol = endPatrol;
		endPatrol = temp;
	}
	myStateMachine = new StateMachine<FireGolemEntity>(this);

	myStateMachine->setCurrentState(FireGolemIdle::Instance());
	myStateMachine->changeState(FireGolemIdle::Instance());
}
FireGolemEntity::~FireGolemEntity()
{

}
void FireGolemEntity::Update()
{
	myStateMachine->update();
	//myAnimatedSprite->Update();
	//HandleMovement();

}
bool FireGolemEntity::HandleMessage(const Message& msg)
{
	return false;
}
void FireGolemEntity::HandleMovement()
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
void FireGolemEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void FireGolemEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTime();
}