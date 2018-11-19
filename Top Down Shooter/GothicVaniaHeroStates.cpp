#include "GothicVaniaHeroStates.h"
#include "HeroEntity.h"
#include "HeroSprite.h"

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

	return false;
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
}


void HeroAttack::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if(entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(HeroIdle::Instance());
	}
}


void HeroAttack::Exit(HeroEntity* entity)
{

}


bool HeroAttack::OnMessage(HeroEntity* entity, const Message& msg)
{

	return false;
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

	return false;
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

	return false;
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
	entity->HandleMovement();
	entity->HandleGravity();
}


void HeroFalling::Exit(HeroEntity* entity)
{

}


bool HeroFalling::OnMessage(HeroEntity* entity, const Message& msg)
{

	return false;
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
}


void HeroJumping::Execute(HeroEntity* entity)
{
	if(!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	entity->HandleJump();
}


void HeroJumping::Exit(HeroEntity* entity)
{

}


bool HeroJumping::OnMessage(HeroEntity* entity, const Message& msg)
{

	return false;
}