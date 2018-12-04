#include "SimpleTimer.h"
#include "GothicVaniaNecromancerStates.h"
#include "NecromancerEntity.h"
#include "NecromancerSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
//------------------------------------------------------------------------methods for GhostAttack
NecromancerIdle* NecromancerIdle::Instance()
{
	static NecromancerIdle instance;

	return &instance;
}
void NecromancerIdle::Enter(NecromancerEntity* entity)
{
	entity->SetAnimation("NecromancerIdle");
	entity->ResetAttackTimer();
}
void NecromancerIdle::Execute(NecromancerEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(NecromancerRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(NecromancerAttack::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(NecromancerPatrol::Instance());
	}

}
void NecromancerIdle::Exit(NecromancerEntity* entity)
{

}
bool NecromancerIdle::OnMessage(NecromancerEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(NecromancerHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
NecromancerAttack* NecromancerAttack::Instance()
{
	static NecromancerAttack instance;

	return &instance;
}
void NecromancerAttack::Enter(NecromancerEntity* entity)
{
	entity->SetAnimation("NecromancerAttack");
	entity->ResetAttackTimer();
	entity->SetFacing();
}
void NecromancerAttack::Execute(NecromancerEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5)
	{

	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(NecromancerIdle::Instance());
	}
}
void NecromancerAttack::Exit(NecromancerEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTime() + EngineUtilities::RandomFloat(0.3, 2);
}
bool NecromancerAttack::OnMessage(NecromancerEntity* entity, const Message& msg)
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
NecromancerHurt* NecromancerHurt::Instance()
{
	static NecromancerHurt instance;

	return &instance;
}
void NecromancerHurt::Enter(NecromancerEntity* entity)
{
	entity->SetAnimation("NecromancerHurt");
	entity->HandleDamaged(10);
}
void NecromancerHurt::Execute(NecromancerEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(NecromancerIdle::Instance());
	}

}
void NecromancerHurt::Exit(NecromancerEntity* entity)
{

}
bool NecromancerHurt::OnMessage(NecromancerEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
NecromancerRunToPlayer* NecromancerRunToPlayer::Instance()
{
	static NecromancerRunToPlayer instance;

	return &instance;
}
void NecromancerRunToPlayer::Enter(NecromancerEntity* entity)
{
	entity->SetAnimation("NecromancerRun");
}
void NecromancerRunToPlayer::Execute(NecromancerEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(NecromancerAttack::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(NecromancerIdle::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(NecromancerPatrol::Instance());
	}
}
void NecromancerRunToPlayer::Exit(NecromancerEntity* entity)
{

}
bool NecromancerRunToPlayer::OnMessage(NecromancerEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(NecromancerHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
NecromancerPatrol* NecromancerPatrol::Instance()
{
	static NecromancerPatrol instance;

	return &instance;
}
void NecromancerPatrol::Enter(NecromancerEntity* entity)
{
	entity->SetAnimation("NecromancerRun");
}
void NecromancerPatrol::Execute(NecromancerEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(NecromancerRunToPlayer::Instance());
	}
}
void NecromancerPatrol::Exit(NecromancerEntity* entity)
{

}
bool NecromancerPatrol::OnMessage(NecromancerEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(NecromancerHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
NecromancerDie* NecromancerDie::Instance()
{
	static NecromancerDie instance;

	return &instance;
}
void NecromancerDie::Enter(NecromancerEntity* entity)
{
	entity->SetAnimation("NecromancerDie");
}
void NecromancerDie::Execute(NecromancerEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
}
void NecromancerDie::Exit(NecromancerEntity* entity)
{

}
bool NecromancerDie::OnMessage(NecromancerEntity* entity, const Message& msg)
{
	return false;
}