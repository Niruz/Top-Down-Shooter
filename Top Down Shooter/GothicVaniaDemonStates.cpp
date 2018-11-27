#include "SimpleTimer.h"
#include "GothicVaniaDemonStates.h"
#include "DemonEntity.h"
#include "TextureManager.h"
#include "AnimatedSprite.h"
//------------------------------------------------------------------------methods for GhostPatrol
DemonIdle* DemonIdle::Instance()
{
	static DemonIdle instance;

	return &instance;
}
void DemonIdle::Enter(DemonEntity* entity)
{
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demonidle");
	entity->SetAnimation("DemonIdle");
	entity->myAnimatedSprite->mySize = glm::vec2(160, 144);
	entity->myAnimatedSprite->myPosition.x = entity->mPosition.x + 16.0f;
	entity->myAnimatedSprite->myPosition.y = entity->mPosition.y - 11.0f;
	entity->ResetAttackTimer();
}
void DemonIdle::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();

	if ((Clock->GetCurrentTime() - entity->myAttackTimer) >= 4.0f)
	{
		entity->GetFSM()->changeState(DemonWindup::Instance());
	}
}
void DemonIdle::Exit(DemonEntity* entity)
{

}
bool DemonIdle::OnMessage(DemonEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonAttack* DemonAttack::Instance()
{
	static DemonAttack instance;

	return &instance;
}
void DemonAttack::Enter(DemonEntity* entity)
{
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demon");
	entity->SetAnimation("DemonAttack");
//	entity->myAnimatedSprite->mySize = glm::vec2(240, 192);
//	entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
//	entity->myAnimatedSprite->myPosition.y = entity->mPosition.y + 11.0f;
	entity->ResetAttackTimer();
}
void DemonAttack::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if ((Clock->GetCurrentTime() - entity->myAttackTimer) >= 5.0f)
	{
		entity->GetFSM()->changeState(DemonWindDown::Instance());
	}
}
void DemonAttack::Exit(DemonEntity* entity)
{

}
bool DemonAttack::OnMessage(DemonEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonWindup* DemonWindup::Instance()
{
	static DemonWindup instance;

	return &instance;
}
void DemonWindup::Enter(DemonEntity* entity)
{
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demon");
	entity->SetAnimation("DemonWindUp");
	entity->myAnimatedSprite->mySize = glm::vec2(240, 192);
	entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
	entity->myAnimatedSprite->myPosition.y = entity->mPosition.y + 11.0f;
	entity->ResetAttackTimer();
}
void DemonWindup::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(DemonAttack::Instance());
	}
}
void DemonWindup::Exit(DemonEntity* entity)
{

}
bool DemonWindup::OnMessage(DemonEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonWindDown* DemonWindDown::Instance()
{
	static DemonWindDown instance;

	return &instance;
}
void DemonWindDown::Enter(DemonEntity* entity)
{
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demon");
	entity->SetAnimation("DemonWindDown");
/*	entity->myAnimatedSprite->mySize = glm::vec2(240, 192);
	entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
	entity->myAnimatedSprite->myPosition.y = entity->mPosition.y + 11.0f;*/
//	entity->ResetAttackTimer();
}
void DemonWindDown::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(DemonIdle::Instance());
	}
}
void DemonWindDown::Exit(DemonEntity* entity)
{

}
bool DemonWindDown::OnMessage(DemonEntity* entity, const Message& msg)
{
	return false;
}