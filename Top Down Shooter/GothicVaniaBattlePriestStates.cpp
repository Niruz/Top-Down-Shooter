#include "SimpleTimer.h"
#include "GothicVaniaBattlePriestStates.h"
#include "BattlePriestEntity.h"
#include "BattlePriestSprite.h"
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
BattlePriestIdle* BattlePriestIdle::Instance()
{
	static BattlePriestIdle instance;

	return &instance;
}
void BattlePriestIdle::Enter(BattlePriestEntity* entity)
{
	entity->SetAnimation("BattlePriestIdle");
	entity->ResetAttackTimer();
}
void BattlePriestIdle::Execute(BattlePriestEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(BattlePriestRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(BattlePriestAttack::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(BattlePriestPatrol::Instance());
	}

}
void BattlePriestIdle::Exit(BattlePriestEntity* entity)
{

}
bool BattlePriestIdle::OnMessage(BattlePriestEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(BattlePriestHurt::Instance());
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
BattlePriestAttack* BattlePriestAttack::Instance()
{
	static BattlePriestAttack instance;

	return &instance;
}
void BattlePriestAttack::Enter(BattlePriestEntity* entity)
{
	entity->SetAnimation("BattlePriestAttack");
	entity->ResetAttackTimer();
	entity->myAlreadyAttacked = false;
	entity->myAlreadyAttacked2 = false;
	entity->SetFacing();
}
void BattlePriestAttack::Execute(BattlePriestEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 10 && !entity->myAlreadyAttacked2)
	{
		float xOffset = -75.0f;
		if (entity->myAnimatedSprite->myHeading == Heading::RIGHTFACING)
			xOffset *= -1.0f;
		GameWorld->GetActiveLevel()->SpawnEntity("Lightning Effect", glm::vec3(entity->mPosition.x + xOffset, entity->mPosition.y + 90.0f, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), entity->myAnimatedSprite->myHeading);
		entity->myAlreadyAttacked2 = true;
	}
		
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 11 && !entity->myAlreadyAttacked)
	{
		if (CollisionMan->CheckSwordHeroCollisiion(entity))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 0, Msg_SmashedDown, entity->myShakeInfoSlamAttack);
			entity->myAlreadyAttacked = true;
			//MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoSlamAttack);
			
		//	GameWorld->GetActiveLevel()->SpawnEntity("Lightning Effect", glm::vec3(entity->mPosition.x + xOffset, entity->mPosition.y + 90.0f, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), entity->myAnimatedSprite->myHeading);
		}
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoSlamAttack);
		SoundMan->GetSoundEngine()->play2D("Audio/lightning.wav", GL_FALSE);
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(BattlePriestIdle::Instance());
	}
}
void BattlePriestAttack::Exit(BattlePriestEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool BattlePriestAttack::OnMessage(BattlePriestEntity* entity, const Message& msg)
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
BattlePriestHurt* BattlePriestHurt::Instance()
{
	static BattlePriestHurt instance;

	return &instance;
}
void BattlePriestHurt::Enter(BattlePriestEntity* entity)
{
	entity->SetAnimation("BattlePriestHurt");
	entity->HandleDamaged(10);
}
void BattlePriestHurt::Execute(BattlePriestEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(BattlePriestIdle::Instance());
	}

}
void BattlePriestHurt::Exit(BattlePriestEntity* entity)
{

}
bool BattlePriestHurt::OnMessage(BattlePriestEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
BattlePriestRunToPlayer* BattlePriestRunToPlayer::Instance()
{
	static BattlePriestRunToPlayer instance;

	return &instance;
}
void BattlePriestRunToPlayer::Enter(BattlePriestEntity* entity)
{
	entity->SetAnimation("BattlePriestRun");
}
void BattlePriestRunToPlayer::Execute(BattlePriestEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(BattlePriestAttack::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		entity->GetFSM()->changeState(BattlePriestIdle::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(BattlePriestPatrol::Instance());
	}
}
void BattlePriestRunToPlayer::Exit(BattlePriestEntity* entity)
{

}
bool BattlePriestRunToPlayer::OnMessage(BattlePriestEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(BattlePriestHurt::Instance());
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
BattlePriestPatrol* BattlePriestPatrol::Instance()
{
	static BattlePriestPatrol instance;

	return &instance;
}
void BattlePriestPatrol::Enter(BattlePriestEntity* entity)
{
	entity->SetAnimation("BattlePriestRun");
}
void BattlePriestPatrol::Execute(BattlePriestEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(BattlePriestRunToPlayer::Instance());
	}
}
void BattlePriestPatrol::Exit(BattlePriestEntity* entity)
{

}
bool BattlePriestPatrol::OnMessage(BattlePriestEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(BattlePriestHurt::Instance());
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
BattlePriestDie* BattlePriestDie::Instance()
{
	static BattlePriestDie instance;

	return &instance;
}
void BattlePriestDie::Enter(BattlePriestEntity* entity)
{
	entity->SetAnimation("BattlePriestDeath");


	entity->myIsActive = false;
	GameWorld->GetActiveLevel()->SpawnEntity("Enemy Hit Death", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), entity->myAnimatedSprite->myHeading);
	GameWorld->GetActiveLevel()->SpawnEntity("HP Potion", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
}
void BattlePriestDie::Execute(BattlePriestEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
}
void BattlePriestDie::Exit(BattlePriestEntity* entity)
{

}
bool BattlePriestDie::OnMessage(BattlePriestEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_Revive:

		/*entity->myHealth = 100.0f;
		entity->myIsActive = true;
		entity->GetFSM()->changeState(BattlePriestRessurect::Instance());*/
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
BattlePriestRessurect* BattlePriestRessurect::Instance()
{
	static BattlePriestRessurect instance;

	return &instance;
}
void BattlePriestRessurect::Enter(BattlePriestEntity* entity)
{
	entity->SetAnimation("BattlePriestRessurect");
}
void BattlePriestRessurect::Execute(BattlePriestEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		entity->GetFSM()->changeState(BattlePriestIdle::Instance());
}
void BattlePriestRessurect::Exit(BattlePriestEntity* entity)
{

}
bool BattlePriestRessurect::OnMessage(BattlePriestEntity* entity, const Message& msg)
{
	return false;
}