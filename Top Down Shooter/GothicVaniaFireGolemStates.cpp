#include "SimpleTimer.h"
#include "GothicVaniaFireGolemStates.h"
#include "FireGolemEntity.h"
#include "FireGolemSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"

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
		entity->GetFSM()->changeState(FireGolemAttack2::Instance());
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
	entity->shakeAttack1 = false;
}
void FireGolemAttack1::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5 && !entity->shakeAttack1)
	{
		
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfo);
		entity->shakeAttack1 = true;
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
//------------------------------------------------------------------------methods for GhostAttack
FireGolemAttack2* FireGolemAttack2::Instance()
{
	static FireGolemAttack2 instance;

	return &instance;
}
void FireGolemAttack2::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemAttack2");
	entity->ResetAttackTimer();
	entity->shakeAttack1 = false;
	entity->shakeAttack2 = false;
}
void FireGolemAttack2::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5 && !entity->shakeAttack1)
	{

		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfo);
		entity->shakeAttack1 = true;
	}
	else if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 9 && !entity->shakeAttack2)
	{

		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfo);
		entity->shakeAttack2 = true;
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
}
void FireGolemAttack2::Exit(FireGolemEntity* entity)
{

}
bool FireGolemAttack2::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}