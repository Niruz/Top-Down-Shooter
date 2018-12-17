#include "SimpleTimer.h"
#include "GothicVaniaNecromancerStates.h"
#include "NecromancerEntity.h"
#include "NecromancerSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
#include "World.h"
#include "CemetaryLevel.h"
#include "BaseProjectileEntity.h"
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
		if(entity->myHaveRecievedRessurectionRequest)
		{
		/*	srand(time(NULL));
			int nextAttack = rand() % 2;
			if (nextAttack == 0)
				entity->GetFSM()->changeState(NecromancerAttack::Instance());
			if (nextAttack == 1)*/
				entity->GetFSM()->changeState(NecromancerRessurect::Instance());
		}
		else
		{
			entity->GetFSM()->changeState(NecromancerAttack::Instance());
		}
		
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
	case Msg_RessurectMe:
		entity->myMinionsToRessurect.push_back(msg.mSender);
		entity->myHaveRecievedRessurectionRequest = true;
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	entity->myFiredProjectile = false;
}
void NecromancerAttack::Execute(NecromancerEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5)
	{
		entity->SpawnProjectile();
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(NecromancerIdle::Instance());
	}
}
void NecromancerAttack::Exit(NecromancerEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool NecromancerAttack::OnMessage(NecromancerEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;

	case Msg_RessurectMe:
		entity->myMinionsToRessurect.push_back(msg.mSender);
		entity->myHaveRecievedRessurectionRequest = true;
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	switch (msg.mMsg)
	{
	case Msg_RessurectMe:
		entity->myMinionsToRessurect.push_back(msg.mSender);
		entity->myHaveRecievedRessurectionRequest = true;
		return true;
	}
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

	case Msg_RessurectMe:
		entity->myMinionsToRessurect.push_back(msg.mSender);
		entity->myHaveRecievedRessurectionRequest = true;
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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

	case Msg_RessurectMe:
		entity->myMinionsToRessurect.push_back(msg.mSender);
		entity->myHaveRecievedRessurectionRequest = true;
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
	entity->myIsActive = false;
	GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Extra Large Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
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
//------------------------------------------------------------------------methods for GhostAttack
NecromancerRessurect* NecromancerRessurect::Instance()
{
	static NecromancerRessurect instance;

	return &instance;
}
void NecromancerRessurect::Enter(NecromancerEntity* entity)
{
	entity->myHaveRessurected = false;
	entity->SetAnimation("NecromancerSummon");
}
void NecromancerRessurect::Execute(NecromancerEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->myHaveRessurected = false;
		entity->myHaveRecievedRessurectionRequest = false;
		for(int i = 0; i < entity->myMinionsToRessurect.size(); i++)
		{
			MessageMan->dispatchMessage(0.0, entity->GetID(), entity->myMinionsToRessurect[i], Msg_Revive, 0);
		}
		entity->myMinionsToRessurect.clear();
		entity->GetFSM()->changeState(NecromancerIdle::Instance());
	}
}
void NecromancerRessurect::Exit(NecromancerEntity* entity)
{
	
}
bool NecromancerRessurect::OnMessage(NecromancerEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	case Msg_RessurectMe:
		entity->myMinionsToRessurect.push_back(msg.mSender);
		entity->myHaveRecievedRessurectionRequest = true;
		return true;
	case Msg_TakeDamageBow:
		entity->HandleDamaged(10);
		BaseProjectileEntity* projectile = (BaseProjectileEntity*)msg.extraInfo;
		GameWorld->GetLevelFromName("Cemetary")->SpawnEntity("Medium Hit", glm::vec3(projectile->mPosition.x, projectile->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}