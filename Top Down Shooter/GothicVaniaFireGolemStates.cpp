#include "SimpleTimer.h"
#include "GothicVaniaFireGolemStates.h"
#include "FireGolemEntity.h"
#include "FireGolemSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "ShakeInfo.h"

//------------------------------------------------------------------------methods for GhostAttack
FireGolemIdle* FireGolemIdle::Instance()
{
	static FireGolemIdle instance;

	return &instance;
}
void FireGolemIdle::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemIdle");
	entity->ResetAttackTimer();
}
void FireGolemIdle::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	/*if (entity->myTileMap->lastPlayerTile->myWorldPosition.x < entity->endPatrol.x && entity->firstTimeSeeingPlayer)
	{
		entity->firstTimeSeeingPlayer = false;
		entity->GetFSM()->changeState(FireGolemSlam::Instance());
	}
	else
	{
		glm::vec2 playerPos = entity->myTileMap->lastPlayerTile->myWorldPosition;
		glm::vec2 myPos = glm::vec2(entity->mPosition);

		float distance = glm::length(myPos - playerPos);

		if ((distance > 50.0f) && playerPos.x > entity->startPatrol.x && playerPos.x < entity->endPatrol.x)
		{
			entity->GetFSM()->changeState(FireGolemRunToPlayer::Instance());
		}
		else if ((distance < 50.0f) && playerPos.x > entity->startPatrol.x && playerPos.x < entity->endPatrol.x)
		{
			entity->GetFSM()->changeState(FireGolemSlam::Instance());
		}
	}
	*/
	 if ((Clock->GetCurrentTime() - entity->myAttackTimer) >= 1.5f)
	{
		entity->GetFSM()->changeState(FireGolemSlam::Instance());
	}
}
void FireGolemIdle::Exit(FireGolemEntity* entity)
{

}
bool FireGolemIdle::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemAttack1* FireGolemAttack1::Instance()
{
	static FireGolemAttack1 instance;

	return &instance;
}
void FireGolemAttack1::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemAttack1");
	entity->ResetAttackTimer();
	entity->shakeAttack1 = false;
}
void FireGolemAttack1::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5 && !entity->shakeAttack1)
	{
		
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->shakeAttack1 = true;
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
}
void FireGolemAttack1::Exit(FireGolemEntity* entity)
{

}
bool FireGolemAttack1::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemAttack2* FireGolemAttack2::Instance()
{
	static FireGolemAttack2 instance;

	return &instance;
}
void FireGolemAttack2::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemAttack2");
	entity->ResetAttackTimer();
	entity->shakeAttack1 = false;
	entity->shakeAttack2 = false;
}
void FireGolemAttack2::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 5 && !entity->shakeAttack1)
	{

		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->shakeAttack1 = true;
	}
	else if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 9 && !entity->shakeAttack2)
	{

		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->shakeAttack2 = true;
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
}
void FireGolemAttack2::Exit(FireGolemEntity* entity)
{

}
bool FireGolemAttack2::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemRunToPlayer* FireGolemRunToPlayer::Instance()
{
	static FireGolemRunToPlayer instance;

	return &instance;
}
void FireGolemRunToPlayer::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemRun");
}
void FireGolemRunToPlayer::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	glm::vec2 playerPos = entity->myTileMap->lastPlayerTile->myWorldPosition;
	glm::vec2 myPos = glm::vec2(entity->mPosition);

	float distance = glm::length(myPos - playerPos);

	if ((distance > 50.0f) && (playerPos.x > entity->startPatrol.x && playerPos.x < entity->endPatrol.x) 
		                   && (entity->mPosition.x >= entity->startPatrol.x && entity->mPosition.x <= entity->endPatrol.x))
	{
		entity->mPosition.x += 1.3f;
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x;
	}
	else if((distance < 50.0f) && ((playerPos.x > entity->startPatrol.x) && (playerPos.x < entity->endPatrol.x))
		&& ((entity->mPosition.x >= entity->startPatrol.x) && (entity->mPosition.x <= entity->endPatrol.x)))
	{
		entity->GetFSM()->changeState(FireGolemSlam::Instance());
	}
}
void FireGolemRunToPlayer::Exit(FireGolemEntity* entity)
{

}
bool FireGolemRunToPlayer::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemHurt* FireGolemHurt::Instance()
{
	static FireGolemHurt instance;

	return &instance;
}
void FireGolemHurt::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemHurt");
}
void FireGolemHurt::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
}
void FireGolemHurt::Exit(FireGolemEntity* entity)
{

}
bool FireGolemHurt::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemDie* FireGolemDie::Instance()
{
	static FireGolemDie instance;

	return &instance;
}
void FireGolemDie::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemDie");
}
void FireGolemDie::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
}
void FireGolemDie::Exit(FireGolemEntity* entity)
{

}
bool FireGolemDie::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}
//------------------------------------------------------------------------methods for GhostAttack
FireGolemSlam* FireGolemSlam::Instance()
{
	static FireGolemSlam instance;

	return &instance;
}
void FireGolemSlam::Enter(FireGolemEntity* entity)
{
	entity->SetAnimation("FireGolemSlam");
	entity->ResetAttackTimer();
	entity->shakeAttack1 = false;
}
void FireGolemSlam::Execute(FireGolemEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->shakeAttack1)
	{

		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoSlamAttack);
		entity->shakeAttack1 = true;
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(FireGolemIdle::Instance());
	}
}
void FireGolemSlam::Exit(FireGolemEntity* entity)
{

}
bool FireGolemSlam::OnMessage(FireGolemEntity* entity, const Message& msg)
{
	return false;
}