#include "SimpleTimer.h"
#include "GothicVaniaUndeadWarriorStates.h"
#include "UndeadWarriorEntity.h"
#include "UndeadWarriorSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
#include "CollisionManager.h"
#include "NecromancerEntity.h"
#include "World.h"
#include "CemetaryLevel.h"
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
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	entity->myAlreadyAttacked = false;
	entity->SetFacing();
}
void UndeadWarriorAttack::Execute(UndeadWarriorEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->myAlreadyAttacked)
	{
		entity->myAlreadyAttacked = CollisionMan->CheckSwordHeroCollisiion(entity);
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(UndeadWarriorIdle::Instance());
	}
}
void UndeadWarriorAttack::Exit(UndeadWarriorEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool UndeadWarriorAttack::OnMessage(UndeadWarriorEntity* entity, const Message& msg)
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
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	if(entity->myMaster != nullptr)
		MessageMan->dispatchMessage(2.0, entity->GetID(), entity->myMaster->GetID(), Msg_RessurectMe, 0);
	entity->myIsActive = false;
	GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Large Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));

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
	switch (msg.mMsg)
	{
	case Msg_Revive:

		entity->myHealth = 100.0f;
		entity->myIsActive = true;
		entity->GetFSM()->changeState(UndeadWarriorRessurect::Instance());
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
UndeadWarriorRessurect* UndeadWarriorRessurect::Instance()
{
	static UndeadWarriorRessurect instance;

	return &instance;
}
void UndeadWarriorRessurect::Enter(UndeadWarriorEntity* entity)
{
	entity->SetAnimation("UndeadWarriorRessurect");
}
void UndeadWarriorRessurect::Execute(UndeadWarriorEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		entity->GetFSM()->changeState(UndeadWarriorIdle::Instance());
}
void UndeadWarriorRessurect::Exit(UndeadWarriorEntity* entity)
{

}
bool UndeadWarriorRessurect::OnMessage(UndeadWarriorEntity* entity, const Message& msg)
{
	return false;
}