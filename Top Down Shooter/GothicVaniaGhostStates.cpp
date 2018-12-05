#include "SimpleTimer.h"
#include "GothicVaniaGhostStates.h"
#include "GhostEntity.h"
#include "GhostSprite.h"

//------------------------------------------------------------------------methods for GhostPatrol
GhostPatrol* GhostPatrol::Instance()
{
	static GhostPatrol instance;

	return &instance;
}
void GhostPatrol::Enter(GhostEntity* entity)
{
	entity->SetAnimation("GhostPatrol");
	entity->ResetAttackTimer();
	entity->myPlasmaSprite->myPosition.x = -1337.0f;
}
void GhostPatrol::Execute(GhostEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->myPlasmaSprite->Update();
	entity->HandleMovement();

	if(entity->myAtTarget)
	{
		entity->GetFSM()->changeState(GhostAttack::Instance());
	}
	if ((Clock->GetCurrentTimeInSeconds() - entity->myAttackTimer) >= 3.0f)
	{
		
	}
}
void GhostPatrol::Exit(GhostEntity* entity)
{

}
bool GhostPatrol::OnMessage(GhostEntity* entity, const Message& msg)
{
	return false;
}

//------------------------------------------------------------------------methods for GhostAttack
GhostAttack* GhostAttack::Instance()
{
	static GhostAttack instance;

	return &instance;
}
void GhostAttack::Enter(GhostEntity* entity)
{
	entity->SetAnimation("GhostAttack");
	entity->ResetAttackTimer(); 
	entity->myPlasmaSprite->myPosition.x = entity->mPosition.x + 6.0f;
}
void GhostAttack::Execute(GhostEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->myPlasmaSprite->Update();
	//entity->HandleMovement();
	if ((Clock->GetCurrentTimeInSeconds() - entity->myAttackTimer) >= 2.0f)
	{
		entity->GetFSM()->changeState(GhostPatrol::Instance());
		entity->myAtTarget = false;
	}
}
void GhostAttack::Exit(GhostEntity* entity)
{

}
bool GhostAttack::OnMessage(GhostEntity* entity, const Message& msg)
{
	return false;
}