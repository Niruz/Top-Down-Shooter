#include "SimpleTimer.h"
#include "GothicVaniaGhoulStates.h"
#include "GhoulEntity.h"
#include "GhoulSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
#include "CollisionManager.h"
#include "World.h"
#include "CemetaryLevel.h"
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
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	entity->myAlreadyAttacked = false;
}
void GhoulAttack::Execute(GhoulEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->myAlreadyAttacked)
	{
		entity->myAlreadyAttacked = CollisionMan->CheckSwordHeroCollisiion(entity);
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(GhoulIdle::Instance());
	}
}
void GhoulAttack::Exit(GhoulEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool GhoulAttack::OnMessage(GhoulEntity* entity, const Message& msg)
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
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	entity->myIsActive = false;
	GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Large Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("HP Potion", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
}
void GhoulDie::Execute(GhoulEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->MarkForDeletion();
	}
}
void GhoulDie::Exit(GhoulEntity* entity)
{

}
bool GhoulDie::OnMessage(GhoulEntity* entity, const Message& msg)
{
	return false;
}