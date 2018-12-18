#include "SimpleTimer.h"
#include "GothicVaniaReaperStates.h"
#include "ReaperEntity.h"
#include "ReaperSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
#include "CollisionManager.h"
#include "World.h"
#include "CemetaryLevel.h"
//------------------------------------------------------------------------methods for GhostAttack
ReaperIdle* ReaperIdle::Instance()
{
	static ReaperIdle instance;

	return &instance;
}
void ReaperIdle::Enter(ReaperEntity* entity)
{
	entity->SetAnimation("ReaperIdle");
	entity->ResetAttackTimer();
}
void ReaperIdle::Execute(ReaperEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(ReaperRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(ReaperAttack::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(ReaperPatrol::Instance());
	}

}
void ReaperIdle::Exit(ReaperEntity* entity)
{

}
bool ReaperIdle::OnMessage(ReaperEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(ReaperHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ReaperAttack* ReaperAttack::Instance()
{
	static ReaperAttack instance;

	return &instance;
}
void ReaperAttack::Enter(ReaperEntity* entity)
{
	entity->SetAnimation("ReaperAttack");
	entity->ResetAttackTimer();
	entity->myAlreadyAttacked = false;
}
void ReaperAttack::Execute(ReaperEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->myAlreadyAttacked)
	{
		entity->myAlreadyAttacked = CollisionMan->CheckSwordHeroCollisiion(entity);
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(ReaperIdle::Instance());
	}
}
void ReaperAttack::Exit(ReaperEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool ReaperAttack::OnMessage(ReaperEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}

	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ReaperHurt* ReaperHurt::Instance()
{
	static ReaperHurt instance;

	return &instance;
}
void ReaperHurt::Enter(ReaperEntity* entity)
{
	entity->SetAnimation("ReaperHurt");
	entity->HandleDamaged(10);
}
void ReaperHurt::Execute(ReaperEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(ReaperIdle::Instance());
	}

}
void ReaperHurt::Exit(ReaperEntity* entity)
{

}
bool ReaperHurt::OnMessage(ReaperEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ReaperRunToPlayer* ReaperRunToPlayer::Instance()
{
	static ReaperRunToPlayer instance;

	return &instance;
}
void ReaperRunToPlayer::Enter(ReaperEntity* entity)
{
	entity->SetAnimation("ReaperRun");
}
void ReaperRunToPlayer::Execute(ReaperEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(ReaperAttack::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(ReaperIdle::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(ReaperPatrol::Instance());
	}
}
void ReaperRunToPlayer::Exit(ReaperEntity* entity)
{

}
bool ReaperRunToPlayer::OnMessage(ReaperEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(ReaperHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ReaperPatrol* ReaperPatrol::Instance()
{
	static ReaperPatrol instance;

	return &instance;
}
void ReaperPatrol::Enter(ReaperEntity* entity)
{
	entity->SetAnimation("ReaperRun");
}
void ReaperPatrol::Execute(ReaperEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(ReaperRunToPlayer::Instance());
	}
}
void ReaperPatrol::Exit(ReaperEntity* entity)
{

}
bool ReaperPatrol::OnMessage(ReaperEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(ReaperHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ReaperDie* ReaperDie::Instance()
{
	static ReaperDie instance;

	return &instance;
}
void ReaperDie::Enter(ReaperEntity* entity)
{
	entity->SetAnimation("ReaperDie");
	entity->myIsActive = false;
	GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Large Hit", glm::vec3(entity->mPosition.x , entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
//	MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myDeathShakeInfo);
}
void ReaperDie::Execute(ReaperEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	if(entity->myAnimatedSprite->IsDone())
	{
		entity->MarkForDeletion();
	}
}
void ReaperDie::Exit(ReaperEntity* entity)
{

}
bool ReaperDie::OnMessage(ReaperEntity* entity, const Message& msg)
{
	return false;
}