#include "SimpleTimer.h"
#include "GothicVaniaAbominationStates.h"
#include "AbominationEntity.h"
#include "AbominationSprite.h"
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
AbominationIdle* AbominationIdle::Instance()
{
	static AbominationIdle instance;

	return &instance;
}
void AbominationIdle::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationIdle");
	entity->ResetAttackTimer();
}
void AbominationIdle::Execute(AbominationEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (!entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange())
	{
		if (Clock->GetCurrentTimeInSeconds() > entity->myJumpCooldown)
			entity->GetFSM()->changeState(AbominationJump::Instance());
		else
			entity->GetFSM()->changeState(AbominationRunToPlayer::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->IsAttackCoolDownReady())
	{
		srand(time(NULL));
		int nextAttack = rand() % 3;
		if (nextAttack == 0)
			entity->GetFSM()->changeState(AbominationAttack::Instance());
		if (nextAttack == 1)
			entity->GetFSM()->changeState(AbominationAttack::Instance());
		if (nextAttack == 2)
		{
			if (Clock->GetCurrentTimeInSeconds() > entity->mySpawnProjectileCooldown)
				entity->GetFSM()->changeState(AbominationSpawnProjectile::Instance());
			else
				entity->GetFSM()->changeState(AbominationAttack::Instance());
		}
			
		//entity->GetFSM()->changeState(AbominationJump::Instance());
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(AbominationPatrol::Instance());
	}

}
void AbominationIdle::Exit(AbominationEntity* entity)
{

}
bool AbominationIdle::OnMessage(AbominationEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(AbominationHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	//	GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
AbominationAttack* AbominationAttack::Instance()
{
	static AbominationAttack instance;

	return &instance;
}
void AbominationAttack::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationAttack");
	entity->ResetAttackTimer();
	entity->myAlreadyAttacked = false;
	entity->SetFacing();
	entity->myAlreadyPlayedSound = false;
	SoundMan->GetSoundEngine()->play2D("Audio/monster-1.wav", GL_FALSE);
}
void AbominationAttack::Execute(AbominationEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 10 && !entity->myAlreadyAttacked)
	{
		if (CollisionMan->CheckSwordHeroCollisiion(entity))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 0, Msg_SmashedDown, entity->myShakeInfoSlamAttack);
			entity->myAlreadyAttacked = true;
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoSlamAttack);
		}
		if (!entity->myAlreadyPlayedSound)
		{
			entity->myAlreadyPlayedSound = true;
			SoundMan->GetSoundEngine()->play2D("Audio/big golem hit.wav", GL_FALSE);
		}
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(AbominationIdle::Instance());
	}
}
void AbominationAttack::Exit(AbominationEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool AbominationAttack::OnMessage(AbominationEntity* entity, const Message& msg)
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
AbominationHurt* AbominationHurt::Instance()
{
	static AbominationHurt instance;

	return &instance;
}
void AbominationHurt::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationHurt");
	entity->HandleDamaged(10);
	SoundMan->GetSoundEngine()->play2D("Audio/monster-4.wav", GL_FALSE);
}
void AbominationHurt::Execute(AbominationEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(AbominationIdle::Instance());
	}

}
void AbominationHurt::Exit(AbominationEntity* entity)
{

}
bool AbominationHurt::OnMessage(AbominationEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
AbominationRunToPlayer* AbominationRunToPlayer::Instance()
{
	static AbominationRunToPlayer instance;

	return &instance;
}
void AbominationRunToPlayer::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationRun");
}
void AbominationRunToPlayer::Execute(AbominationEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();
	if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && entity->IsAttackCoolDownReady())
	{
		if (Clock->GetCurrentTimeInSeconds() > entity->myJumpCooldown)
			entity->GetFSM()->changeState(AbominationJump::Instance());
		else
			entity->GetFSM()->changeState(AbominationAttack::Instance());
		//entity->GetFSM()->changeState(AbominationJump::Instance());
	}
	else if (entity->IsPlayerWithinAttackDistance() && entity->IsPlayerWithinPatrolRange() && entity->AmIWithinMyPatrolDistance() && !entity->IsAttackCoolDownReady())
	{
		//entity->GetFSM()->changeState(AbominationJump::Instance());
		//entity->GetFSM()->changeState(AbominationIdle::Instance());
		srand(time(NULL));
		int nextAttack = rand() % 3;
		if (nextAttack == 0)
			entity->GetFSM()->changeState(AbominationAttack::Instance());
		if (nextAttack == 1)
			entity->GetFSM()->changeState(AbominationAttack::Instance());
		if (nextAttack == 2)
		{
			if (Clock->GetCurrentTimeInSeconds() > entity->mySpawnProjectileCooldown)
				entity->GetFSM()->changeState(AbominationSpawnProjectile::Instance());
			else
				entity->GetFSM()->changeState(AbominationAttack::Instance());
		}
	}
	else if (!entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(AbominationPatrol::Instance());
	}
}
void AbominationRunToPlayer::Exit(AbominationEntity* entity)
{

}
bool AbominationRunToPlayer::OnMessage(AbominationEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(AbominationHurt::Instance());
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
AbominationPatrol* AbominationPatrol::Instance()
{
	static AbominationPatrol instance;

	return &instance;
}
void AbominationPatrol::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationRun");
}
void AbominationPatrol::Execute(AbominationEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(AbominationRunToPlayer::Instance());
	}
}
void AbominationPatrol::Exit(AbominationEntity* entity)
{

}
bool AbominationPatrol::OnMessage(AbominationEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(AbominationHurt::Instance());
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
AbominationDie* AbominationDie::Instance()
{
	static AbominationDie instance;

	return &instance;
}
void AbominationDie::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationDie");

	SoundMan->GetSoundEngine()->stopAllSoundsOfSoundSource(SoundMan->GetSoundEngine()->getSoundSource("Audio/monsteyr-1.wav"));
	SoundMan->GetSoundEngine()->stopAllSoundsOfSoundSource(SoundMan->GetSoundEngine()->getSoundSource("Audio/monsteyr-4.wav"));
	SoundMan->GetSoundEngine()->stopAllSoundsOfSoundSource(SoundMan->GetSoundEngine()->getSoundSource("Audio/monsteyr-6.wav"));
	SoundMan->GetSoundEngine()->stopAllSoundsOfSoundSource(SoundMan->GetSoundEngine()->getSoundSource("Audio/monsteyr-8.wav"));

	SoundMan->GetSoundEngine()->play2D("Audio/monsteyr-6.wav", GL_FALSE);
	entity->myIsActive = false;
	GameWorld->GetActiveLevel()->SpawnEntity("Enemy Hit Death", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), entity->myAnimatedSprite->myHeading);
}
void AbominationDie::Execute(AbominationEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
}
void AbominationDie::Exit(AbominationEntity* entity)
{

}
bool AbominationDie::OnMessage(AbominationEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_Revive:

		/*entity->myHealth = 100.0f;
		entity->myIsActive = true;
		entity->GetFSM()->changeState(AbominationRessurect::Instance());*/
		return true;

	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
AbominationSpawnProjectile* AbominationSpawnProjectile::Instance()
{
	static AbominationSpawnProjectile instance;

	return &instance;
}
void AbominationSpawnProjectile::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationSpawnProjectile");
}
void AbominationSpawnProjectile::Execute(AbominationEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		entity->GetFSM()->changeState(AbominationIdle::Instance());
}
void AbominationSpawnProjectile::Exit(AbominationEntity* entity)
{
	entity->mySpawnProjectileCooldown = Clock->GetCurrentTimeInSeconds() + 13.0f;
}
bool AbominationSpawnProjectile::OnMessage(AbominationEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
AbominationJump* AbominationJump::Instance()
{
	static AbominationJump instance;

	return &instance;
}
void AbominationJump::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationJump");
	entity->myStartedJump = false;
	entity->StartJump();
	SoundMan->GetSoundEngine()->play2D("Audio/monster-8.wav", GL_FALSE);
}
void AbominationJump::Execute(AbominationEntity* entity)
{
	if(!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex > 2 && !entity->myStartedJump)
	{
		entity->myStartedJump = true;
	}
	if (entity->myStartedJump)
		entity->HandleJump();
	

}
void AbominationJump::Exit(AbominationEntity* entity)
{
	
}
bool AbominationJump::OnMessage(AbominationEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
AbominationFalling* AbominationFalling::Instance()
{
	static AbominationFalling instance;

	return &instance;
}
void AbominationFalling::Enter(AbominationEntity* entity)
{
	//entity->SetAnimation("AbominationJump");
}
void AbominationFalling::Execute(AbominationEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	entity->HandleFalling();

}
void AbominationFalling::Exit(AbominationEntity* entity)
{
	entity->myJumpCooldown = Clock->GetCurrentTimeInSeconds() + 13.0f;
	MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myJumpShake);
	SoundMan->GetSoundEngine()->play2D("Audio/big golem hit.wav", GL_FALSE);

	//GameWorld->GetActiveLevel()->SpawnEntity("Earth Projectile", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
	GameWorld->GetActiveLevel()->SpawnEntity("Earth Projectile", glm::vec3(3400.0f, 260.0f, entity->mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
	GameWorld->GetActiveLevel()->SpawnEntity("Earth Projectile", glm::vec3(3600.0f, 200.0f, entity->mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
	GameWorld->GetActiveLevel()->SpawnEntity("Earth Projectile", glm::vec3(3550.0f, 230.0f, entity->mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
	GameWorld->GetActiveLevel()->SpawnEntity("Earth Projectile", glm::vec3(3700.0f, 190.0f, entity->mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
	GameWorld->GetActiveLevel()->SpawnEntity("Earth Projectile", glm::vec3(3820.0f, 170.0f, entity->mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
	GameWorld->GetActiveLevel()->SpawnEntity("Earth Projectile", glm::vec3(3450.0f, 240.0f, entity->mPosition.z), glm::vec3(1.0f, 0.0f, 0.0f));
}
bool AbominationFalling::OnMessage(AbominationEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
AbominationWaitForPlayer* AbominationWaitForPlayer::Instance()
{
	static AbominationWaitForPlayer instance;

	return &instance;
}
void AbominationWaitForPlayer::Enter(AbominationEntity* entity)
{
	entity->SetAnimation("AbominationIdle");
	entity->ResetAttackTimer();
}
void AbominationWaitForPlayer::Execute(AbominationEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->SetFacing();
	if (entity->IsPlayerWithinAttackDistance2() && entity->IsPlayerWithinPatrolRange())
	{
		entity->GetFSM()->changeState(AbominationIdle::Instance());
	}
}
void AbominationWaitForPlayer::Exit(AbominationEntity* entity)
{

}
bool AbominationWaitForPlayer::OnMessage(AbominationEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(AbominationHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		//	GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}