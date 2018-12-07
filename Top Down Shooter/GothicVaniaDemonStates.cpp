#include "SimpleTimer.h"
#include "GothicVaniaDemonStates.h"
#include "DemonEntity.h"
#include "TextureManager.h"
#include "AnimatedSprite.h"
#include "Messages.h"
//------------------------------------------------------------------------methods for GhostPatrol
DemonIdle* DemonIdle::Instance()
{
	static DemonIdle instance;

	return &instance;
}
void DemonIdle::Enter(DemonEntity* entity)
{
	
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demonidle");
	entity->SetAnimation("DemonIdle");
	entity->myAnimatedSprite->mySize = glm::vec2(160, 144);
	if(entity->myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x + 16.0f;
		entity->myAnimatedSprite->myPosition.y = entity->mPosition.y - 11.0f;
	}
	else
	{
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
		entity->myAnimatedSprite->myPosition.y = entity->mPosition.y - 11.0f;
	}

	entity->ResetAttackTimer();
}
void DemonIdle::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();

	if(entity->firstAttack)
	{
		entity->firstAttack = false;
		entity->GetFSM()->changeState(DemonWindup::Instance());
	}
	if ((Clock->GetCurrentTimeInSeconds() - entity->myAttackTimer) >= 4.0f)
	{
		entity->GetFSM()->changeState(DemonWindup::Instance());
	}
}
void DemonIdle::Exit(DemonEntity* entity)
{

}
bool DemonIdle::OnMessage(DemonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonAttack* DemonAttack::Instance()
{
	static DemonAttack instance;

	return &instance;
}
void DemonAttack::Enter(DemonEntity* entity)
{
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demon");
	entity->SetAnimation("DemonAttack");
//	entity->myAnimatedSprite->mySize = glm::vec2(240, 192);
//	entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
//	entity->myAnimatedSprite->myPosition.y = entity->mPosition.y + 11.0f;
	entity->ResetAttackTimer();
}
void DemonAttack::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if ((Clock->GetCurrentTimeInSeconds() - entity->myAttackTimer) >= 5.0f)
	{
		entity->GetFSM()->changeState(DemonWindDown::Instance());
	}
}
void DemonAttack::Exit(DemonEntity* entity)
{

}
bool DemonAttack::OnMessage(DemonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonWindup* DemonWindup::Instance()
{
	static DemonWindup instance;

	return &instance;
}
void DemonWindup::Enter(DemonEntity* entity)
{
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demon");
	entity->SetAnimation("DemonWindUp");
	entity->myAnimatedSprite->mySize = glm::vec2(240, 192);
	if (entity->myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
		entity->myAnimatedSprite->myPosition.y = entity->mPosition.y + 11.0f;
	}
	else
	{
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x + 16.0f;
		entity->myAnimatedSprite->myPosition.y = entity->mPosition.y + 11.0f;
	}
	entity->ResetAttackTimer();
}
void DemonWindup::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(DemonAttack::Instance());
	}
}
void DemonWindup::Exit(DemonEntity* entity)
{

}
bool DemonWindup::OnMessage(DemonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonWindDown* DemonWindDown::Instance()
{
	static DemonWindDown instance;

	return &instance;
}
void DemonWindDown::Enter(DemonEntity* entity)
{
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demon");
	entity->SetAnimation("DemonWindDown");
/*	entity->myAnimatedSprite->mySize = glm::vec2(240, 192);
	entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
	entity->myAnimatedSprite->myPosition.y = entity->mPosition.y + 11.0f;*/
//	entity->ResetAttackTimer();
}
void DemonWindDown::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(DemonIdle::Instance());
	}
}
void DemonWindDown::Exit(DemonEntity* entity)
{

}
bool DemonWindDown::OnMessage(DemonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_TakeDamage:

		entity->HandleDamaged(10);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonAwaitingOrders* DemonAwaitingOrders::Instance()
{
	static DemonAwaitingOrders instance;

	return &instance;
}
void DemonAwaitingOrders::Enter(DemonEntity* entity)
{
	entity->myIsActive = true;
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demonidle");
	entity->SetAnimation("DemonIdle");
	//entity->storedY = entity->myAnimatedSprite->myPosition.y;
	entity->myAnimatedSprite->myPosition.y += 2000.0f;
}
void DemonAwaitingOrders::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->HandleMovement();
}
void DemonAwaitingOrders::Exit(DemonEntity* entity)
{

}
bool DemonAwaitingOrders::OnMessage(DemonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_GoFuckShitUp:

		//entity->mPosition.y = entity->storedY;
		entity->myAnimatedSprite->myPosition.y -= 2000.0f;
		entity->GetFSM()->changeState(DemonSwoopDown::Instance());
		return true;

	}

	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonSwoopDown* DemonSwoopDown::Instance()
{
	static DemonSwoopDown instance;

	return &instance;
}
void DemonSwoopDown::Enter(DemonEntity* entity)
{
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("demonidle");
	entity->SetAnimation("DemonIdle");
	if (entity->myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x + 16.0f;
		entity->myAnimatedSprite->myPosition.y = entity->mPosition.y - 11.0f;
	}
	else
	{
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
		entity->myAnimatedSprite->myPosition.y = entity->mPosition.y - 11.0f;
	}
}
void DemonSwoopDown::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	//entity->HandleMovement();
	entity->HandleSwoopDown();
	if(entity->touchedDown)
		entity->GetFSM()->changeState(DemonIdle::Instance());
}
void DemonSwoopDown::Exit(DemonEntity* entity)
{

}
bool DemonSwoopDown::OnMessage(DemonEntity* entity, const Message& msg)
{
	switch (msg.mMsg)
	{
	case Msg_GoFuckShitUp:

		//entity->mPosition.y = entity->storedY;
		entity->myAnimatedSprite->myPosition.y -= 2000.0f;
		entity->GetFSM()->changeState(DemonIdle::Instance());
		return true;

	}

	return false;
}
//------------------------------------------------------------------------methods for GhostPatrol
DemonDie* DemonDie::Instance()
{
	static DemonDie instance;

	return &instance;
}
void DemonDie::Enter(DemonEntity* entity)
{
	entity->myIsActive = false;
	entity->myAnimatedSprite->myTexture = TextureMan->GetTexture("enemyDeath");
	entity->myAnimatedSprite->mySize = glm::vec2(88, 102);
	entity->SetAnimation("DemonDie");
	if (entity->myAnimatedSprite->myHeading == Heading::RIGHTFACING)
	{
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x + 16.0f;
		entity->myAnimatedSprite->myPosition.y = entity->mPosition.y - 11.0f;
	}
	else
	{
		entity->myAnimatedSprite->myPosition.x = entity->mPosition.x - 16.0f;
		entity->myAnimatedSprite->myPosition.y = entity->mPosition.y - 11.0f;
	}
}
void DemonDie::Execute(DemonEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->mPosition.y = -2000.0f;
		entity->myAnimatedSprite->myPosition.y = -2000.0f;
		entity->myPlayerAABB->myPosition.y = -2000.0f;
	}
	//entity->HandleMovement();
/*	entity->HandleSwoopDown();
	if (entity->touchedDown)
		entity->GetFSM()->changeState(DemonIdle::Instance());*/
}
void DemonDie::Exit(DemonEntity* entity)
{

}
bool DemonDie::OnMessage(DemonEntity* entity, const Message& msg)
{
	return false;
}