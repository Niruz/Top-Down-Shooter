#include "SimpleTimer.h"
#include "GothicVaniaFireGolemStates.h"
#include "FireGolemEntity.h"
#include "FireGolemSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
#include "CollisionManager.h"
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
	

	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(FireGolemRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		srand(time(NULL));
		int nextAttack = rand() % 3;
		if (nextAttack == 0)
			entity->GetFSM()->changeState(FireGolemSlam::Instance());
		if (nextAttack == 1)
			entity->GetFSM()->changeState(FireGolemAttack1::Instance());
		if (nextAttack == 2)
			entity->GetFSM()->changeState(FireGolemAttack2::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(FireGolemPatrol::Instance());
	}

}
void FireGolemIdle::Exit(FireGolemEntity* entity)
{

}
bool FireGolemIdle::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(FireGolemHurt::Instance());
		return true;

	}
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
	entity->SetAnimation("FireGolemAttack1");
	entity->ResetAttackTimer();
	entity->shakeAttack1 = false;
}
void FireGolemAttack1::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->shakeAttack1)
	{
		CollisionMan->CheckSwordHeroCollisiion(entity);
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->shakeAttack1 = true;
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
}
void FireGolemAttack1::Exit(FireGolemEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool FireGolemAttack1::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	}
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
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->shakeAttack1)
	{
		CollisionMan->CheckSwordHeroCollisiion(entity);
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->shakeAttack1 = true;
	}
	else if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 8 && !entity->shakeAttack2)
	{
		CollisionMan->CheckSwordHeroCollisiion(entity);
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->shakeAttack2 = true;
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
}
void FireGolemAttack2::Exit(FireGolemEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool FireGolemAttack2::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemRunToPlayer* FireGolemRunToPlayer::Instance()
{
	static FireGolemRunToPlayer instance;

	return &instance;
}
void FireGolemRunToPlayer::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemRun");
}
void FireGolemRunToPlayer::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		srand(time(NULL));
		int nextAttack = rand() % 3;
		if(nextAttack == 0)
			entity->GetFSM()->changeState(FireGolemSlam::Instance());
		if(nextAttack == 1)
			entity->GetFSM()->changeState(FireGolemAttack1::Instance());
		if(nextAttack == 2)
			entity->GetFSM()->changeState(FireGolemAttack2::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(FireGolemPatrol::Instance());
	}
}
void FireGolemRunToPlayer::Exit(FireGolemEntity* entity)
{

}
bool FireGolemRunToPlayer::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(FireGolemHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemHurt* FireGolemHurt::Instance()
{
	static FireGolemHurt instance;

	return &instance;
}
void FireGolemHurt::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemHurt");
	entity->HandleDamaged(10);
}
void FireGolemHurt::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}

}
void FireGolemHurt::Exit(FireGolemEntity* entity)
{

}
bool FireGolemHurt::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemDie* FireGolemDie::Instance()
{
	static FireGolemDie instance;

	return &instance;
}
void FireGolemDie::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemDie");
	entity->myIsActive = false;
}
void FireGolemDie::Execute(FireGolemEntity* entity)
{
	if(!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
}
void FireGolemDie::Exit(FireGolemEntity* entity)
{

}
bool FireGolemDie::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemSlam* FireGolemSlam::Instance()
{
	static FireGolemSlam instance;

	return &instance;
}
void FireGolemSlam::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemSlam");
	entity->ResetAttackTimer();
	entity->shakeAttack1 = false;
}
void FireGolemSlam::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 3 && !entity->shakeAttack1)
	{
		CollisionMan->CheckSwordHeroCollisiion(entity);
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoSlamAttack);
		entity->shakeAttack1 = true;
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
}
void FireGolemSlam::Exit(FireGolemEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool FireGolemSlam::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemReturnHome* FireGolemReturnHome::Instance()
{
	static FireGolemReturnHome instance;

	return &instance;
}
void FireGolemReturnHome::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemRun");
}
void FireGolemReturnHome::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
}
void FireGolemReturnHome::Exit(FireGolemEntity* entity)
{

}
bool FireGolemReturnHome::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemPatrol* FireGolemPatrol::Instance()
{
	static FireGolemPatrol instance;

	return &instance;
}
void FireGolemPatrol::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemRun");
}
void FireGolemPatrol::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(FireGolemRunToPlayer::Instance());
	}
}
void FireGolemPatrol::Exit(FireGolemEntity* entity)
{

}
bool FireGolemPatrol::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(FireGolemHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemWaiting* FireGolemWaiting::Instance()
{
	static FireGolemWaiting instance;

	return &instance;
}
void FireGolemWaiting::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemIdle");
	entity->ResetAttackTimer();
}
void FireGolemWaiting::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->FirstTimeSeeingPlayer())
	{
		entity->firstTimeSeeingPlayer = false;
		entity->GetFSM()->changeState(FireGolemSlam::Instance());
	}
}
void FireGolemWaiting::Exit(FireGolemEntity* entity)
{

}
bool FireGolemWaiting::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}