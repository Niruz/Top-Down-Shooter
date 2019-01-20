#include "SimpleTimer.h"
#include "GothicVaniaBigSkeletonStates.h"
#include "BigSkeletonEntity.h"
#include "BigSkeletonSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
#include "CollisionManager.h"
#include "NecromancerEntity.h"
#include "World.h"
#include "CemetaryLevel.h"
#include "BaseProjectileEntity.h"
#include "SoundManager.h"
//------------------------------------------------------------------------methods for GhostAttack
BigSkeletonIdle* BigSkeletonIdle::Instance()
{
	static BigSkeletonIdle instance;

	return &instance;
}
void BigSkeletonIdle::Enter(BigSkeletonEntity* entity)
{
	entity->SetAnimation("SkeletonIdle");
	entity->ResetAttackTimer();
}
void BigSkeletonIdle::Execute(BigSkeletonEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(BigSkeletonRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(BigSkeletonAttack::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(BigSkeletonPatrol::Instance());
	}

}
void BigSkeletonIdle::Exit(BigSkeletonEntity* entity)
{

}
bool BigSkeletonIdle::OnMessage(BigSkeletonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(BigSkeletonHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		//GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
BigSkeletonAttack* BigSkeletonAttack::Instance()
{
	static BigSkeletonAttack instance;

	return &instance;
}
void BigSkeletonAttack::Enter(BigSkeletonEntity* entity)
{
	entity->SetAnimation("SkeletonAttack");
	entity->ResetAttackTimer();
	entity->myAlreadyAttacked = false;
	entity->SetFacing();
}
void BigSkeletonAttack::Execute(BigSkeletonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 8 && !entity->myAlreadyAttacked)
	{
		if(CollisionMan->CheckSwordHeroCollisiion(entity))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 0, Msg_SmashedDown, entity->myShakeInfoSlamAttack);
			entity->myAlreadyAttacked = true;
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoSlamAttack);
			SoundMan->GetSoundEngine()->play2D("Audio/swordhit.wav", GL_FALSE);
		}
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(BigSkeletonIdle::Instance());
	}
}
void BigSkeletonAttack::Exit(BigSkeletonEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool BigSkeletonAttack::OnMessage(BigSkeletonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		//GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
BigSkeletonHurt* BigSkeletonHurt::Instance()
{
	static BigSkeletonHurt instance;

	return &instance;
}
void BigSkeletonHurt::Enter(BigSkeletonEntity* entity)
{
	entity->SetAnimation("SkeletonHurt");
	entity->HandleDamaged(10);
}
void BigSkeletonHurt::Execute(BigSkeletonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(BigSkeletonIdle::Instance());
	}

}
void BigSkeletonHurt::Exit(BigSkeletonEntity* entity)
{

}
bool BigSkeletonHurt::OnMessage(BigSkeletonEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
BigSkeletonRunToPlayer* BigSkeletonRunToPlayer::Instance()
{
	static BigSkeletonRunToPlayer instance;

	return &instance;
}
void BigSkeletonRunToPlayer::Enter(BigSkeletonEntity* entity)
{
	entity->SetAnimation("SkeletonRun");
}
void BigSkeletonRunToPlayer::Execute(BigSkeletonEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(BigSkeletonAttack::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(BigSkeletonIdle::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(BigSkeletonPatrol::Instance());
	}
}
void BigSkeletonRunToPlayer::Exit(BigSkeletonEntity* entity)
{

}
bool BigSkeletonRunToPlayer::OnMessage(BigSkeletonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(BigSkeletonHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		//GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
BigSkeletonPatrol* BigSkeletonPatrol::Instance()
{
	static BigSkeletonPatrol instance;

	return &instance;
}
void BigSkeletonPatrol::Enter(BigSkeletonEntity* entity)
{
	entity->SetAnimation("SkeletonRun");
}
void BigSkeletonPatrol::Execute(BigSkeletonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(BigSkeletonRunToPlayer::Instance());
	}
}
void BigSkeletonPatrol::Exit(BigSkeletonEntity* entity)
{

}
bool BigSkeletonPatrol::OnMessage(BigSkeletonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(BigSkeletonHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		//GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
BigSkeletonDie* BigSkeletonDie::Instance()
{
	static BigSkeletonDie instance;

	return &instance;
}
void BigSkeletonDie::Enter(BigSkeletonEntity* entity)
{
	entity->SetAnimation("SkeletonDie");


	entity->myIsActive = false;
	GameWorld->GetActiveLevel()->SpawnEntity("Enemy Hit Death", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), entity->myAnimatedSprite->myHeading);
	GameWorld->GetActiveLevel()->SpawnEntity("HP Potion", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
}
void BigSkeletonDie::Execute(BigSkeletonEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
}
void BigSkeletonDie::Exit(BigSkeletonEntity* entity)
{

}
bool BigSkeletonDie::OnMessage(BigSkeletonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_Revive:

		/*entity->myHealth = 100.0f;
		entity->myIsActive = true;
		entity->GetFSM()->changeState(BigSkeletonRessurect::Instance());*/
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
BigSkeletonRessurect* BigSkeletonRessurect::Instance()
{
	static BigSkeletonRessurect instance;

	return &instance;
}
void BigSkeletonRessurect::Enter(BigSkeletonEntity* entity)
{
	entity->SetAnimation("SkeletonRessurect");
}
void BigSkeletonRessurect::Execute(BigSkeletonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		entity->GetFSM()->changeState(BigSkeletonIdle::Instance());
}
void BigSkeletonRessurect::Exit(BigSkeletonEntity* entity)
{

}
bool BigSkeletonRessurect::OnMessage(BigSkeletonEntity* entity, const Message& msg)
{
	return false;
}