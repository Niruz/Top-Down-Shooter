#include "SimpleTimer.h"
#include "GothicVaniaGhoulStates.h"
#include "GhoulEntity.h"
#include "GhoulSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
//------------------------------------------------------------------------methods for GhostAttack
GhoulIdle* GhoulIdle::Instance()
{
	static GhoulIdle instance;

	return &instance;
}
void GhoulIdle::Enter(GhoulEntity* entity)
{
	entity->SetAnimation("GhoulIdle");
	entity->ResetAttackTimer();
}
void GhoulIdle::Execute(GhoulEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(GhoulRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(GhoulAttack::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(GhoulPatrol::Instance());
	}

}
void GhoulIdle::Exit(GhoulEntity* entity)
{

}
bool GhoulIdle::OnMessage(GhoulEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(GhoulHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
GhoulAttack* GhoulAttack::Instance()
{
	static GhoulAttack instance;

	return &instance;
}
void GhoulAttack::Enter(GhoulEntity* entity)
{
	entity->SetAnimation("GhoulAttack");
	entity->ResetAttackTimer();
}
void GhoulAttack::Execute(GhoulEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5 )
	{

	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(GhoulIdle::Instance());
	}
}
void GhoulAttack::Exit(GhoulEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTime() + EngineUtilities::RandomFloat(0.3, 2);
}
bool GhoulAttack::OnMessage(GhoulEntity* entity, const Message& msg)
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
GhoulHurt* GhoulHurt::Instance()
{
	static GhoulHurt instance;

	return &instance;
}
void GhoulHurt::Enter(GhoulEntity* entity)
{
	entity->SetAnimation("GhoulHurt");
	entity->HandleDamaged(10);
}
void GhoulHurt::Execute(GhoulEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(GhoulIdle::Instance());
	}

}
void GhoulHurt::Exit(GhoulEntity* entity)
{

}
bool GhoulHurt::OnMessage(GhoulEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
GhoulRunToPlayer* GhoulRunToPlayer::Instance()
{
	static GhoulRunToPlayer instance;

	return &instance;
}
void GhoulRunToPlayer::Enter(GhoulEntity* entity)
{
	entity->SetAnimation("GhoulRun");
}
void GhoulRunToPlayer::Execute(GhoulEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(GhoulAttack::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(GhoulIdle::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(GhoulPatrol::Instance());
	}
}
void GhoulRunToPlayer::Exit(GhoulEntity* entity)
{

}
bool GhoulRunToPlayer::OnMessage(GhoulEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(GhoulHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
GhoulPatrol* GhoulPatrol::Instance()
{
	static GhoulPatrol instance;

	return &instance;
}
void GhoulPatrol::Enter(GhoulEntity* entity)
{
	entity->SetAnimation("GhoulRun");
}
void GhoulPatrol::Execute(GhoulEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(GhoulRunToPlayer::Instance());
	}
}
void GhoulPatrol::Exit(GhoulEntity* entity)
{

}
bool GhoulPatrol::OnMessage(GhoulEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(GhoulHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
GhoulDie* GhoulDie::Instance()
{
	static GhoulDie instance;

	return &instance;
}
void GhoulDie::Enter(GhoulEntity* entity)
{
	entity->SetAnimation("GhoulDie");
}
void GhoulDie::Execute(GhoulEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
}
void GhoulDie::Exit(GhoulEntity* entity)
{

}
bool GhoulDie::OnMessage(GhoulEntity* entity, const Message& msg)
{
	return false;
}