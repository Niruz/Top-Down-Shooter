#include "SimpleTimer.h"
#include "GothicVaniaImpStates.h"
#include "ImpEntity.h"
#include "ImpSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
#include "World.h"
#include "CemetaryLevel.h"
//------------------------------------------------------------------------methods for GhostAttack
ImpIdle* ImpIdle::Instance()
{
	static ImpIdle instance;

	return &instance;
}
void ImpIdle::Enter(ImpEntity* entity)
{
	entity->SetAnimation("ImpIdle");
	entity->ResetAttackTimer();
}
void ImpIdle::Execute(ImpEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(ImpRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(ImpAttack::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(ImpPatrol::Instance());
	}

}
void ImpIdle::Exit(ImpEntity* entity)
{

}
bool ImpIdle::OnMessage(ImpEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(ImpHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ImpAttack* ImpAttack::Instance()
{
	static ImpAttack instance;

	return &instance;
}
void ImpAttack::Enter(ImpEntity* entity)
{
	entity->SetAnimation("ImpAttack");
	entity->ResetAttackTimer();
	entity->SetFacing();
	entity->myFiredProjectile = false;
}
void ImpAttack::Execute(ImpEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5)
	{
		entity->SpawnProjectile();
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(ImpIdle::Instance());
	}

}
void ImpAttack::Exit(ImpEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool ImpAttack::OnMessage(ImpEntity* entity, const Message& msg)
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
ImpHurt* ImpHurt::Instance()
{
	static ImpHurt instance;

	return &instance;
}
void ImpHurt::Enter(ImpEntity* entity)
{
	entity->SetAnimation("ImpHurt");
	entity->HandleDamaged(10);
}
void ImpHurt::Execute(ImpEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(ImpIdle::Instance());
	}

}
void ImpHurt::Exit(ImpEntity* entity)
{

}
bool ImpHurt::OnMessage(ImpEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ImpRunToPlayer* ImpRunToPlayer::Instance()
{
	static ImpRunToPlayer instance;

	return &instance;
}
void ImpRunToPlayer::Enter(ImpEntity* entity)
{
	entity->SetAnimation("ImpRun");
}
void ImpRunToPlayer::Execute(ImpEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(ImpAttack::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(ImpIdle::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(ImpPatrol::Instance());
	}
}
void ImpRunToPlayer::Exit(ImpEntity* entity)
{

}
bool ImpRunToPlayer::OnMessage(ImpEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(ImpHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ImpPatrol* ImpPatrol::Instance()
{
	static ImpPatrol instance;

	return &instance;
}
void ImpPatrol::Enter(ImpEntity* entity)
{
	entity->SetAnimation("ImpRun");
}
void ImpPatrol::Execute(ImpEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(ImpRunToPlayer::Instance());
	}
}
void ImpPatrol::Exit(ImpEntity* entity)
{

}
bool ImpPatrol::OnMessage(ImpEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(ImpHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ImpDie* ImpDie::Instance()
{
	static ImpDie instance;

	return &instance;
}
void ImpDie::Enter(ImpEntity* entity)
{
	entity->SetAnimation("ImpDie");
	entity->myIsActive = false;
	GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Enemy Hit Death", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), entity->myAnimatedSprite->myHeading);
//	GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Large Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("HP Potion", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
}
void ImpDie::Execute(ImpEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->MarkForDeletion();
	}
}
void ImpDie::Exit(ImpEntity* entity)
{

}
bool ImpDie::OnMessage(ImpEntity* entity, const Message& msg)
{
	return false;
}