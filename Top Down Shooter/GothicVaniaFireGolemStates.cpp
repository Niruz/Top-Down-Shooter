#include "SimpleTimer.h"
#include "GothicVaniaFireGolemStates.h"
#include "FireGolemEntity.h"
#include "FireGolemSprite.h"

//------------------------------------------------------------------------methods for GhostAttack
FireGolemIdle* FireGolemIdle::Instance()
{
	static FireGolemIdle instance;

	return &instance;
}
void FireGolemIdle::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemIdle");
	entity->ResetAttackTimer();
}
void FireGolemIdle::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if ((Clock->GetCurrentTime() - entity->myAttackTimer) >= 3.0f)
	{
		entity->GetFSM()->changeState(FireGolemAttack1::Instance());
	}
}
void FireGolemIdle::Exit(FireGolemEntity* entity)
{

}
bool FireGolemIdle::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemAttack1* FireGolemAttack1::Instance()
{
	static FireGolemAttack1 instance;

	return &instance;
}
void FireGolemAttack1::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemAttack");
	entity->ResetAttackTimer();
}
void FireGolemAttack1::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4)
	{
		int shit = 5;
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
}
void FireGolemAttack1::Exit(FireGolemEntity* entity)
{

}
bool FireGolemAttack1::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}