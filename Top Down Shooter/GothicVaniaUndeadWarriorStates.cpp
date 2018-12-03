#include "SimpleTimer.h"
#include "GothicVaniaUndeadWarriorStates.h"
#include "UndeadWarriorEntity.h"
#include "UndeadWarriorSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
//------------------------------------------------------------------------methods for GhostAttack
UndeadWarriorIdle* UndeadWarriorIdle::Instance()
{
	static UndeadWarriorIdle instance;

	return &instance;
}
void UndeadWarriorIdle::Enter(UndeadWarriorEntity* entity)
{
	entity->SetAnimation("UndeadWarriorIdle");
	entity->ResetAttackTimer();
}
void UndeadWarriorIdle::Execute(UndeadWarriorEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(UndeadWarriorRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(UndeadWarriorAttack::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(UndeadWarriorPatrol::Instance());
	}

}
void UndeadWarriorIdle::Exit(UndeadWarriorEntity* entity)
{

}
bool UndeadWarriorIdle::OnMessage(UndeadWarriorEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(UndeadWarriorHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
UndeadWarriorAttack* UndeadWarriorAttack::Instance()
{
	static UndeadWarriorAttack instance;

	return &instance;
}
void UndeadWarriorAttack::Enter(UndeadWarriorEntity* entity)
{
	entity->SetAnimation("UndeadWarriorAttack");
	entity->ResetAttackTimer();
}
void UndeadWarriorAttack::Execute(UndeadWarriorEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5)
	{

	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(UndeadWarriorIdle::Instance());
	}
}
void UndeadWarriorAttack::Exit(UndeadWarriorEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTime() + EngineUtilities::RandomFloat(0.3, 2);
}
bool UndeadWarriorAttack::OnMessage(UndeadWarriorEntity* entity, const Message& msg)
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
UndeadWarriorHurt* UndeadWarriorHurt::Instance()
{
	static UndeadWarriorHurt instance;

	return &instance;
}
void UndeadWarriorHurt::Enter(UndeadWarriorEntity* entity)
{
	entity->SetAnimation("UndeadWarriorHurt");
	entity->HandleDamaged(10);
}
void UndeadWarriorHurt::Execute(UndeadWarriorEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(UndeadWarriorIdle::Instance());
	}

}
void UndeadWarriorHurt::Exit(UndeadWarriorEntity* entity)
{

}
bool UndeadWarriorHurt::OnMessage(UndeadWarriorEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
UndeadWarriorRunToPlayer* UndeadWarriorRunToPlayer::Instance()
{
	static UndeadWarriorRunToPlayer instance;

	return &instance;
}
void UndeadWarriorRunToPlayer::Enter(UndeadWarriorEntity* entity)
{
	entity->SetAnimation("UndeadWarriorRun");
}
void UndeadWarriorRunToPlayer::Execute(UndeadWarriorEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(UndeadWarriorAttack::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(UndeadWarriorIdle::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(UndeadWarriorPatrol::Instance());
	}
}
void UndeadWarriorRunToPlayer::Exit(UndeadWarriorEntity* entity)
{

}
bool UndeadWarriorRunToPlayer::OnMessage(UndeadWarriorEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(UndeadWarriorHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
UndeadWarriorPatrol* UndeadWarriorPatrol::Instance()
{
	static UndeadWarriorPatrol instance;

	return &instance;
}
void UndeadWarriorPatrol::Enter(UndeadWarriorEntity* entity)
{
	entity->SetAnimation("UndeadWarriorRun");
}
void UndeadWarriorPatrol::Execute(UndeadWarriorEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(UndeadWarriorRunToPlayer::Instance());
	}
}
void UndeadWarriorPatrol::Exit(UndeadWarriorEntity* entity)
{

}
bool UndeadWarriorPatrol::OnMessage(UndeadWarriorEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(UndeadWarriorHurt::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
UndeadWarriorDie* UndeadWarriorDie::Instance()
{
	static UndeadWarriorDie instance;

	return &instance;
}
void UndeadWarriorDie::Enter(UndeadWarriorEntity* entity)
{
	entity->SetAnimation("UndeadWarriorDie");
}
void UndeadWarriorDie::Execute(UndeadWarriorEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
}
void UndeadWarriorDie::Exit(UndeadWarriorEntity* entity)
{

}
bool UndeadWarriorDie::OnMessage(UndeadWarriorEntity* entity, const Message& msg)
{
	return false;
}