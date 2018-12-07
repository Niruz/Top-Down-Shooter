#include "SimpleTimer.h"
#include "GothicVaniaHeroStates.h"
#include "HeroEntity.h"
#include "HeroSprite.h"
#include "GLFW\glfw3.h"
#include "CollisionManager.h"
#include "Messages.h"
#include "MessageDispatcher.h"
//------------------------------------------------------------------------methods for HeroIdle
HeroIdle* HeroIdle::Instance()
{
	static HeroIdle instance;

	return &instance;
}


void HeroIdle::Enter(HeroEntity* entity)
{
	entity->SetAnimation("HeroIdle");
}


void HeroIdle::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->CheckIfFalling();
}


void HeroIdle::Exit(HeroEntity* entity)
{

}


bool HeroIdle::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroIdle::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myNegYDirection = -1.0f;
	}*/
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCrouch::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttack::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroAttack* HeroAttack::Instance()
{
	static HeroAttack instance;

	return &instance;
}


void HeroAttack::Enter(HeroEntity* entity)
{
	entity->SetAnimation("HeroAttack");
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
}


void HeroAttack::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	//if(entity->myAnimatedSprite->IsDone())
	if(entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->basicAttack)
	{
		if(CollisionMan->CheckSwordEnemyCollision(entity->mySwordAABB))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
			entity->basicAttack = true;
		}
		entity->GetFSM()->changeState(HeroIdle::Instance());
	}
}


void HeroAttack::Exit(HeroEntity* entity)
{

}


bool HeroAttack::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttack::HandleInput(HeroEntity* entity, int key, int action)
{
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroCrouch* HeroCrouch::Instance()
{
	static HeroCrouch instance;

	return &instance;
}


void HeroCrouch::Enter(HeroEntity* entity)
{
	entity->SetAnimation("HeroCrouch");
	entity->myAnimatedSprite->Reset();
}


void HeroCrouch::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
}


void HeroCrouch::Exit(HeroEntity* entity)
{

}


bool HeroCrouch::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroCrouch::HandleInput(HeroEntity* entity, int key, int action)
{
/*	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myNegYDirection = -1.0f;
	}*/
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_C && action == GLFW_RELEASE)
	{
		entity->GetFSM()->changeState(HeroIdle::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttack::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroRunning
HeroRunning* HeroRunning::Instance()
{
	static HeroRunning instance;

	return &instance;
}


void HeroRunning::Enter(HeroEntity* entity)
{
	entity->SetAnimation("HeroRun");
	entity->myAnimatedSprite->Reset();
}


void HeroRunning::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();

	entity->HandleMovement();
	entity->CheckIfFalling();
}


void HeroRunning::Exit(HeroEntity* entity)
{

}


bool HeroRunning::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroRunning::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		entity->myNegYDirection = -1.0f;
	}*/
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCrouch::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttack::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
HeroFalling* HeroFalling::Instance()
{
	static HeroFalling instance;

	return &instance;
}


void HeroFalling::Enter(HeroEntity* entity)
{
	entity->SetAnimation("HeroFall");
	entity->myAnimatedSprite->Reset();
}


void HeroFalling::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->IsOnSpikes())
		entity->GetFSM()->changeState(HeroDamaged::Instance());
	entity->myNegYDirection = -1.0f;
	//entity->HandleMovement();
	entity->HandleGravity();
}


void HeroFalling::Exit(HeroEntity* entity)
{

}


bool HeroFalling::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroFalling::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
HeroJumping* HeroJumping::Instance()
{
	static HeroJumping instance;

	return &instance;
}


void HeroJumping::Enter(HeroEntity* entity)
{
	entity->SetAnimation("HeroJump");
	entity->myAnimatedSprite->Reset();
	entity->StartJump();
	entity->myYVelocity = 9.0f;
}


void HeroJumping::Execute(HeroEntity* entity)
{
	if(!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	//entity->HandleMovement();
	entity->HandleJump();
}


void HeroJumping::Exit(HeroEntity* entity)
{

}


bool HeroJumping::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroJumping::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		if (entity->myYVelocity < 3.5f)
			entity->myYVelocity = 3.5f;
		entity->GetFSM()->changeState(HeroFalling::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
HeroDamaged* HeroDamaged::Instance()
{
	static HeroDamaged instance;

	return &instance;
}


void HeroDamaged::Enter(HeroEntity* entity)
{
	entity->SetAnimation("HeroHurt");
	entity->myAnimatedSprite->Reset();
	entity->myStartDeadTimer = Clock->GetCurrentTimeInSeconds();
	entity->HandleDamaged(10);
}


void HeroDamaged::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if(Clock->GetCurrentTimeInSeconds() > entity->myStartDeadTimer + 0.3f)
	{
		entity->Respawn();
		
		entity->GetFSM()->changeState(HeroRunning::Instance());
	}
//	entity->HandleDamaged();
}


void HeroDamaged::Exit(HeroEntity* entity)
{
	entity->HandleDamaged(10);
}


bool HeroDamaged::OnMessage(HeroEntity* entity, const Message& msg)
{
	return false;
}
bool HeroDamaged::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	return true;
}