#include "SimpleTimer.h"
#include "DemonEntity.h"
#include "Group.h"
#include "DemonSprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureManager.h"
#include "Sprite.h"
#include "GothicVaniaDemonStates.h"
DemonEntity::DemonEntity(int id, const std::string& name, const glm::vec3& myStartPosition, const glm::vec3& patrolTo) :
	BaseEnemy(id, name, myStartPosition, patrolTo)
{


	//THe facing is weird since all the enemies from the sprites look in the opposite direction from the start
	//myAnimatedSprite = new DemonSprite(glm::vec4(mPosition.x+16.0f, mPosition.y - 11, 0.09f, 1), glm::vec2(160, 144), TextureMan->GetTexture("demonidle"), Heading::RIGHTFACING);
	myAnimatedSprite = new DemonSprite(glm::vec4(mPosition.x, mPosition.y, 0.09f, 1), glm::vec2(160, 144), TextureMan->GetTexture("demonidle"), Heading::RIGHTFACING);
	mySprite->Add(myAnimatedSprite);
	myAnimatedSprite->SetAnimation("DemonIdle");
	myXDirection = 1.0f;
	//mySprite->Add(myPlayerAABB);
	myStartTime = Clock->GetCurrentTime();
	setonce = false;
	breatheFire = false;


	myStateMachine = new StateMachine<DemonEntity>(this);
/*	myStateMachine->setCurrentState(DemonIdle::Instance());
	myStateMachine->changeState(DemonIdle::Instance());
	myStateMachine->update();*/
	myStateMachine->setCurrentState(DemonAwaitingOrders::Instance());
	myStateMachine->changeState(DemonAwaitingOrders::Instance());
/*	myStateMachine->setCurrentState(DemonIdle::Instance());
	myStateMachine->changeState(DemonIdle::Instance());*/
	touchedDown = false;
	firstAttack = true;
}
DemonEntity::~DemonEntity()
{

}
void DemonEntity::Update()
{
	myStateMachine->update();
	/*myAnimatedSprite->Update();
	HandleMovement();

	if(Clock->GetCurrentTime() - myStartTime >= 3.0f && !setonce)
		breatheFire = true;

	if(breatheFire)
	{

	}
	myAnimatedSprite->myTexture = TextureMan->GetTexture("demon");
	myAnimatedSprite->SetAnimation("DemonAttack");
	setonce = true;
	myAnimatedSprite->mySize = glm::vec2(240, 192);
	myAnimatedSprite->myPosition.x = mPosition.x - 16.0f;
	myAnimatedSprite->myPosition.y = mPosition.y + 11.0f;*/
}
bool DemonEntity::HandleMessage(const Message& msg)
{
	return myStateMachine->HandleMessage(msg);
}
void DemonEntity::HandleSwoopDown()
{
	myAABB->myOrigin = glm::vec2(mPosition.x, mPosition.y);
	myPlayerAABB->myPosition = glm::vec4(mPosition, 1.0f);
	if (myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		myAnimatedSprite->myPosition.x = mPosition.x + 16.0f;
		myAnimatedSprite->myPosition.y = mPosition.y - 11.0f;
	}
	else
	{
		myAnimatedSprite->myPosition.x = mPosition.x - 16.0f;
		myAnimatedSprite->myPosition.y = mPosition.y - 11.0f;
	}

	if (!touchedDown)
	{
		//-96 - 15
		if (mPosition.y > -95 - 15)
			mPosition.y--;
		else
		{
			touchedDown = true;
			mPosition.y = -95 - 15;
		}
			
	}
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
	//myAnimatedSprite->myPosition.x = mPosition.x;
	//myAnimatedSprite->myPosition.y = mPosition.y;

}
void DemonEntity::SetAnimation(const std::string& name)
{
	myAnimatedSprite->SetAnimation(name);
	myAnimatedSprite->Reset();
}
void DemonEntity::ResetAttackTimer()
{
	myAttackTimer = Clock->GetCurrentTime();
}