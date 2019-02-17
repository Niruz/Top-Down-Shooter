#include "SimpleTimer.h"
#include "GothicVaniaShriekerStates.h"
#include "ShriekerEntity.h"
#include "ShriekerSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"
#include <ctime>
#include "EngineUtilities.h"
#include "CollisionManager.h"
#include "NecromancerEntity.h"
#include "World.h"
#include "CemetaryLevel.h"
#include "SoundManager.h"
//------------------------------------------------------------------------methods for GhostAttack
ShriekerIdle* ShriekerIdle::Instance()
{
	static ShriekerIdle instance;

	return &instance;
}
void ShriekerIdle::Enter(ShriekerEntity* entity)
{
	entity->SetAnimation("ShriekerIdle");
	entity->ResetAttackTimer();
	
}
void ShriekerIdle::Execute(ShriekerEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->IsPlayerWithinAttackDistance())
	{
		entity->GetFSM()->changeState(ShriekerDisappear::Instance());
	}

}
void ShriekerIdle::Exit(ShriekerEntity* entity)
{

}
bool ShriekerIdle::OnMessage(ShriekerEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ShriekerAppear* ShriekerAppear::Instance()
{
	static ShriekerAppear instance;

	return &instance;
}
void ShriekerAppear::Enter(ShriekerEntity* entity)
{
	entity->SetAnimation("ShriekerAppear");
	entity->ChooseAppearPoint();
	SoundMan->GetSoundEngine()->play2D("Audio/teleport.wav", GL_FALSE);
}
void ShriekerAppear::Execute(ShriekerEntity* entity)
{
	if (!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		entity->GetFSM()->changeState(ShriekerAttack::Instance());

}
void ShriekerAppear::Exit(ShriekerEntity* entity)
{

}
bool ShriekerAppear::OnMessage(ShriekerEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ShriekerAttack* ShriekerAttack::Instance()
{
	static ShriekerAttack instance;

	return &instance;
}
void ShriekerAttack::Enter(ShriekerEntity* entity)
{
	entity->SetAnimation("ShriekerShriek");
	//float myAttackCooldown;
	entity->myAlreadyAttacked = false;
	if (entity->IsPlayerWithinAttackDistance())
	{
		SoundMan->GetSoundEngine()->play2D("Audio/scream4.ogg", GL_FALSE);
	}
	
}
void ShriekerAttack::Execute(ShriekerEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		entity->GetFSM()->changeState(ShriekerDisappear::Instance());
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 3 && !entity->myAlreadyAttacked)
	{
		if (CollisionMan->CheckSwordHeroCollisiion(entity))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 0, Msg_SmashedDown, entity->myShakeInfoSlamAttack);
			entity->myAlreadyAttacked = true;
		}

	}

	

}
void ShriekerAttack::Exit(ShriekerEntity* entity)
{
	entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + EngineUtilities::RandomFloat(0.3, 2);
}
bool ShriekerAttack::OnMessage(ShriekerEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(ShriekerDie::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ShriekerDisappear* ShriekerDisappear::Instance()
{
	static ShriekerDisappear instance;

	return &instance;
}
void ShriekerDisappear::Enter(ShriekerEntity* entity)
{
	entity->SetAnimation("ShriekerVanish");
	entity->myAlreadyAttacked = false;
	SoundMan->GetSoundEngine()->play2D("Audio/teleport.wav", GL_FALSE);
}
void ShriekerDisappear::Execute(ShriekerEntity* entity)
{

	if (entity->myAlreadyAttacked)
	{
		if (Clock->GetCurrentTimeInSeconds() > entity->myAttackCooldown)
			entity->GetFSM()->changeState(ShriekerAppear::Instance());
	}
	else
	{



		if (!entity->myAnimatedSprite->IsDone())
			entity->myAnimatedSprite->Update();
		if (entity->myAnimatedSprite->IsDone())
		{
			//entity->GetFSM()->changeState(ShriekerAppear::Instance());
			entity->myAlreadyAttacked = true;
			entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + 0.5f;
		}

	/*	entity->myAnimatedSprite->Update();
		if (entity->myAnimatedSprite->IsDone())
		{
			entity->myAlreadyAttacked = true;
			entity->myAttackCooldown = Clock->GetCurrentTimeInSeconds() + 2.0f;
		}
		*/
	}
	

}
void ShriekerDisappear::Exit(ShriekerEntity* entity)
{

}
bool ShriekerDisappear::OnMessage(ShriekerEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
ShriekerHurt* ShriekerHurt::Instance()
{
	static ShriekerHurt instance;

	return &instance;
}
void ShriekerHurt::Enter(ShriekerEntity* entity)
{
	entity->SetAnimation("SkeletonRun");
}
void ShriekerHurt::Execute(ShriekerEntity* entity)
{
	entity->myAnimatedSprite->Update();


	entity->HandleMovement();

}
void ShriekerHurt::Exit(ShriekerEntity* entity)
{

}
bool ShriekerHurt::OnMessage(ShriekerEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->GetFSM()->changeState(ShriekerHurt::Instance());
		return true;
	case Msg_TakeDamageBow:

		entity->HandleDamaged(10);
		GameWorld->GetActiveLevel()->SpawnEntity("Medium Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		return true;
	}
	return false;
}

//------------------------------------------------------------------------methods for GhostAttack
ShriekerDie* ShriekerDie::Instance()
{
	static ShriekerDie instance;

	return &instance;
}
void ShriekerDie::Enter(ShriekerEntity* entity)
{
	SoundMan->GetSoundEngine()->stopAllSoundsOfSoundSource(SoundMan->GetSoundEngine()->getSoundSource("Audio/scream4.ogg"));
	entity->SetAnimation("ShriekerVanish");
	SoundMan->GetSoundEngine()->play2D("Audio/teleport.wav", GL_FALSE);
	GameWorld->GetActiveLevel()->SpawnEntity("Large Hit", glm::vec3(entity->mPosition.x, entity->mPosition.y, entity->mPosition.z + 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
}
void ShriekerDie::Execute(ShriekerEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		entity->MarkForDeletion();

}
void ShriekerDie::Exit(ShriekerEntity* entity)
{

}
bool ShriekerDie::OnMessage(ShriekerEntity* entity, const Message& msg)
{
	return false;
}