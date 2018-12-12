#include "SimpleTimer.h"
#include "GothicVaniaHeroStates.h"
#include "HeroEntity.h"
#include "HeroSprite.h"
#include "AdventurerSprite.h"
#include "GLFW\glfw3.h"
#include "CollisionManager.h"
#include "Messages.h"
#include "MessageDispatcher.h"


//------------------------------------------------------------------------methods for HeroAttack
HeroAttackSwordAir1* HeroAttackSwordAir1::Instance()
{
	static HeroAttackSwordAir1 instance;

	return &instance;
}


void HeroAttackSwordAir1::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerAttack1AirSword");
	entity->myShouldEnterNextSwordAttack = false;
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
	entity->myCurrentSwordAttackCooldownTimer = Clock->GetCurrentTimeInSeconds();
}


void HeroAttackSwordAir1::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		//if(entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->basicAttack)
	{
		if (CollisionMan->CheckSwordEnemyCollision(entity->mySwordAABB))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
			entity->basicAttack = true;
		}
		if (entity->myShouldEnterNextSwordAttack)
			entity->GetFSM()->changeState(HeroAttackSwordAir2::Instance());
		else
			entity->GetFSM()->changeState(HeroFalling::Instance());
	}
}


void HeroAttackSwordAir1::Exit(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
}


bool HeroAttackSwordAir1::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttackSwordAir1::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex >= 3)
			entity->myShouldEnterNextSwordAttack = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroAttackSwordAir2* HeroAttackSwordAir2::Instance()
{
	static HeroAttackSwordAir2 instance;

	return &instance;
}


void HeroAttackSwordAir2::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerAttack2AirSword");
	entity->myShouldEnterNextSwordAttack = false;
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
	entity->myAirSlamReceived = false;
	entity->myCurrentSwordAttackCooldownTimer = Clock->GetCurrentTimeInSeconds();
}


void HeroAttackSwordAir2::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		//if(entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->basicAttack)
	{
		if (CollisionMan->CheckSwordEnemyCollision(entity->mySwordAABB))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
			entity->basicAttack = true;
		}
		if (entity->myShouldEnterNextSwordAttack)
			entity->GetFSM()->changeState(HeroAttackSwordAir3::Instance());
		else
			entity->GetFSM()->changeState(HeroFalling::Instance());
	}
}


void HeroAttackSwordAir2::Exit(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
}


bool HeroAttackSwordAir2::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttackSwordAir2::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex >= 2)
			entity->myShouldEnterNextSwordAttack = true;
	}
	if (key == GLFW_KEY_V && action == GLFW_REPEAT)
	{
		entity->myAirSlamReceived = true;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroAttackSwordAir3* HeroAttackSwordAir3::Instance()
{
	static HeroAttackSwordAir3 instance;

	return &instance;
}


void HeroAttackSwordAir3::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerAirSlamBegin");
	entity->myShouldEnterNextSwordAttack = false;
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
	entity->myCurrentSwordAttackCooldownTimer = Clock->GetCurrentTimeInSeconds();
}


void HeroAttackSwordAir3::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		//if(entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->basicAttack)
	{
		if (CollisionMan->CheckSwordEnemyCollision(entity->mySwordAABB))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
			entity->basicAttack = true;
		}
		if (entity->myAirSlamReceived)
			entity->GetFSM()->changeState(HeroAttackSwordAir4::Instance());
		else
			entity->GetFSM()->changeState(HeroFalling::Instance());
	}
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->basicAttack)
	{
		if (entity->myAirSlamReceived)
			entity->GetFSM()->changeState(HeroAttackSwordAir4::Instance());
	}
	if(entity->myAirSlamReceived && entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex >= 3)
		entity->HandleAirSlam(-6.0f);
	/*else if (entity->myAirSlamReceived)
		entity->GetFSM()->changeState(HeroAttackSwordAir4::Instance());
	if (entity->IsOnSpikes())
		entity->GetFSM()->changeState(HeroDamaged::Instance());*/
	/*else
	{
		entity->HandleAirSlam(0.0f);
	}*/
}


void HeroAttackSwordAir3::Exit(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
	entity->myAirSlamReceived = false;
}


bool HeroAttackSwordAir3::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttackSwordAir3::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex >= 2)
			entity->myShouldEnterNextSwordAttack = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}*/
	/*if (key == GLFW_KEY_V && action == GLFW_RELEASE)
	{
		entity->myAirSlamReceived = false;
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->myAirSlamReceived = true;
	}*/
	if (key == GLFW_KEY_V && action == GLFW_RELEASE)
	{
		entity->myAirSlamReceived = false;
	}
	if (key == GLFW_KEY_V && action == GLFW_REPEAT)
	{
		entity->myAirSlamReceived = true;
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroAttackSwordAir4* HeroAttackSwordAir4::Instance()
{
	static HeroAttackSwordAir4 instance;

	return &instance;
}


void HeroAttackSwordAir4::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerAirSlamLoop");
	entity->myShouldEnterNextSwordAttack = false;
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
}


void HeroAttackSwordAir4::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->IsOnSpikes())
		entity->GetFSM()->changeState(HeroDamaged::Instance());
	else
	{
		entity->HandleAirSlam(-6.0f);
	}
}


void HeroAttackSwordAir4::Exit(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
}


bool HeroAttackSwordAir4::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttackSwordAir4::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex >= 2)
	entity->myShouldEnterNextSwordAttack = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
	entity->myShouldEnterNextSwordAttack = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
	entity->myShouldEnterNextSwordAttack = false;
	}*/
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroAttackSwordAir5* HeroAttackSwordAir5::Instance()
{
	static HeroAttackSwordAir5 instance;

	return &instance;
}


void HeroAttackSwordAir5::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerAirSlamEnd");
	entity->myShouldEnterNextSwordAttack = false;
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
}


void HeroAttackSwordAir5::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if(entity->myAnimatedSprite->IsDone())
		entity->GetFSM()->changeState(HeroIdle::Instance());
}


void HeroAttackSwordAir5::Exit(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
}


bool HeroAttackSwordAir5::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttackSwordAir5::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex >= 2)
	entity->myShouldEnterNextSwordAttack = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
	entity->myShouldEnterNextSwordAttack = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
	entity->myShouldEnterNextSwordAttack = false;
	}*/
	return true;
}
//------------------------------------------------------------------------methods for HeroIdle
HeroIdle* HeroIdle::Instance()
{
	static HeroIdle instance;

	return &instance;
}


void HeroIdle::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerIdleSword");
}


void HeroIdle::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->CheckIfFalling();
}


void HeroIdle::Exit(HeroEntity* entity)
{

}


bool HeroIdle::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroIdle::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myNegYDirection = -1.0f;
	}*/
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCrouch::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttackSword1::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroSliding::Instance());
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroFireBowGround::Instance());
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCastSpell::Instance());
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroSheatheSword::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroAttackSword1* HeroAttackSword1::Instance()
{
	static HeroAttackSword1 instance;

	return &instance;
}


void HeroAttackSword1::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerAttack1Sword");
	entity->myShouldEnterNextSwordAttack = false;
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
	entity->myCurrentSwordAttackCooldownTimer = Clock->GetCurrentTimeInSeconds();
}


void HeroAttackSword1::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if(entity->myAnimatedSprite->IsDone())
	//if(entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->basicAttack)
	{
		if(CollisionMan->CheckSwordEnemyCollision(entity->mySwordAABB))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
			entity->basicAttack = true;
		}
		if(entity->myShouldEnterNextSwordAttack)
			entity->GetFSM()->changeState(HeroAttackSword2::Instance());
		else
			entity->GetFSM()->changeState(HeroIdle::Instance());
	}
}


void HeroAttackSword1::Exit(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
}


bool HeroAttackSword1::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttackSword1::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		if(entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex >=4)
			entity->myShouldEnterNextSwordAttack = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroAttackSword2* HeroAttackSword2::Instance()
{
	static HeroAttackSword2 instance;

	return &instance;
}


void HeroAttackSword2::Enter(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
	entity->SetAnimation("AdventurerAttack2Sword");
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
	entity->myCurrentSwordAttackCooldownTimer = Clock->GetCurrentTimeInSeconds();
}


void HeroAttackSword2::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		//if(entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->basicAttack)
	{
		if (CollisionMan->CheckSwordEnemyCollision(entity->mySwordAABB))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
			entity->basicAttack = true;
		}
		if (entity->myShouldEnterNextSwordAttack)
			entity->GetFSM()->changeState(HeroAttackSword3::Instance());
		else
			entity->GetFSM()->changeState(HeroIdle::Instance());
	}
}


void HeroAttackSword2::Exit(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
}


bool HeroAttackSword2::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttackSword2::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex >= 5)
			entity->myShouldEnterNextSwordAttack = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS && !entity->myShouldEnterNextSwordAttack)
	{
		entity->myShouldEnterNextSwordAttack = false;
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroAttackSword3* HeroAttackSword3::Instance()
{
	static HeroAttackSword3 instance;

	return &instance;
}


void HeroAttackSword3::Enter(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
	entity->SetAnimation("AdventurerAttack3Sword");
	entity->myAnimatedSprite->Reset();
	entity->basicAttack = false;
	entity->myCurrentSwordAttackCooldownTimer = Clock->GetCurrentTimeInSeconds();
}


void HeroAttackSword3::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
		//if(entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 4 && !entity->basicAttack)
	{
		if (CollisionMan->CheckSwordEnemyCollision(entity->mySwordAABB))
		{
			MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
			entity->basicAttack = true;
		}
	/*	if (entity->myShouldEnterNextSwordAttack)
			entity->GetFSM()->changeState(HeroAttackSword1::Instance());
		else*/
			entity->GetFSM()->changeState(HeroIdle::Instance());
	}
}


void HeroAttackSword3::Exit(HeroEntity* entity)
{
	entity->myShouldEnterNextSwordAttack = false;
}


bool HeroAttackSword3::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroAttackSword3::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		//entity->myShouldEnterNextSwordAttack = true;
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroCrouch* HeroCrouch::Instance()
{
	static HeroCrouch instance;

	return &instance;
}


void HeroCrouch::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerCrouch");
	entity->myAnimatedSprite->Reset();
}


void HeroCrouch::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
}


void HeroCrouch::Exit(HeroEntity* entity)
{

}


bool HeroCrouch::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroCrouch::HandleInput(HeroEntity* entity, int key, int action)
{
/*	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroRunning::Instance());
		entity->myNegYDirection = -1.0f;
	}*/
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_C && action == GLFW_RELEASE)
	{
		entity->GetFSM()->changeState(HeroIdle::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttackSword1::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroRunning
HeroRunning* HeroRunning::Instance()
{
	static HeroRunning instance;

	return &instance;
}


void HeroRunning::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerRunSword");
	entity->myAnimatedSprite->Reset();
}


void HeroRunning::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();

	entity->HandleMovement();
	entity->CheckIfFalling();
}


void HeroRunning::Exit(HeroEntity* entity)
{

}


bool HeroRunning::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroRunning::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		entity->myNegYDirection = -1.0f;
	}*/
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	if (key == GLFW_KEY_D && action == GLFW_REPEAT)
	{
		int shit = 5;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCrouch::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttackSword1::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroSliding::Instance());
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroFireBowGround::Instance());
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCastSpell::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroRunning
HeroSliding* HeroSliding::Instance()
{
	static HeroSliding instance;

	return &instance;
}


void HeroSliding::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerSlide");
	entity->myAnimatedSprite->Reset();
	if (entity->myAnimatedSprite->myHeading == Heading::RIGHTFACING)
		entity->StartSliding(1);
	else
		entity->StartSliding(-1);
}


void HeroSliding::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();

	entity->HandleSliding();
	entity->CheckIfFalling();

	if (Clock->GetCurrentTimeInSeconds() >= entity->myStartSlidingTime + 0.3f)
	{
		entity->GetFSM()->changeState(HeroIdle::Instance());
	}
		
}


void HeroSliding::Exit(HeroEntity* entity)
{

}


bool HeroSliding::OnMessage(HeroEntity* entity, const Message& msg)
{

	/*switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}*/
	return true;
}
bool HeroSliding::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
	entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
	entity->myNegYDirection = -1.0f;
	}*/
	/*if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCrouch::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttackSword1::Instance());
	}*/
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
HeroFalling* HeroFalling::Instance()
{
	static HeroFalling instance;

	return &instance;
}


void HeroFalling::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerFall");
	entity->myAnimatedSprite->Reset();
}


void HeroFalling::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->IsOnSpikes())
		entity->GetFSM()->changeState(HeroDamaged::Instance());
	entity->myNegYDirection = -1.0f;
	//entity->HandleMovement();
	entity->HandleGravity();
}


void HeroFalling::Exit(HeroEntity* entity)
{

}


bool HeroFalling::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroFalling::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttackSwordAir1::Instance());
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroFireBowAir::Instance());
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroDropKick::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
HeroJumping* HeroJumping::Instance()
{
	static HeroJumping instance;

	return &instance;
}


void HeroJumping::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerJump");
	entity->myAnimatedSprite->Reset();
	entity->StartJump();
	entity->myYVelocity = 9.0f;
}


void HeroJumping::Execute(HeroEntity* entity)
{
	if(!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
	//entity->HandleMovement();
	entity->HandleJump();
}


void HeroJumping::Exit(HeroEntity* entity)
{

}


bool HeroJumping::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroJumping::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		if (entity->myYVelocity < 3.5f)
			entity->myYVelocity = 3.5f;
		entity->GetFSM()->changeState(HeroFalling::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttackSwordAir1::Instance());
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroFireBowAir::Instance());
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroDropKick::Instance());
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
HeroDamaged* HeroDamaged::Instance()
{
	static HeroDamaged instance;

	return &instance;
}


void HeroDamaged::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerHurt");
	entity->myAnimatedSprite->Reset();
	entity->myStartDeadTimer = Clock->GetCurrentTimeInSeconds();
	entity->HandleDamaged(10);
}


void HeroDamaged::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if(Clock->GetCurrentTimeInSeconds() > entity->myStartDeadTimer + 0.4f)
	{
		entity->Respawn();
		
		entity->GetFSM()->changeState(HeroRunning::Instance());
	}
//	entity->HandleDamaged();
}


void HeroDamaged::Exit(HeroEntity* entity)
{
	entity->HandleDamaged(10);
}


bool HeroDamaged::OnMessage(HeroEntity* entity, const Message& msg)
{
	return false;
}
bool HeroDamaged::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroFireBowGround* HeroFireBowGround::Instance()
{
	static HeroFireBowGround instance;

	return &instance;
}

void HeroFireBowGround::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerBowGround");
	entity->myAnimatedSprite->Reset();
	entity->myFiredProjectile = false;
}

void HeroFireBowGround::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 8 )
	{
		entity->SpawnArrow();
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		
		entity->GetFSM()->changeState(HeroIdle::Instance());
	}
}

void HeroFireBowGround::Exit(HeroEntity* entity)
{
	
}

bool HeroFireBowGround::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroFireBowGround::HandleInput(HeroEntity* entity, int key, int action)
{
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroFireBowAir* HeroFireBowAir::Instance()
{
	static HeroFireBowAir instance;

	return &instance;
}

void HeroFireBowAir::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerBowInAir");
	entity->myAnimatedSprite->Reset();
	entity->myFiredProjectile = false;
}

void HeroFireBowAir::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 6)
	{
		entity->SpawnArrow();
	}
	if (entity->myAnimatedSprite->IsDone())
	{

		entity->GetFSM()->changeState(HeroIdle::Instance());
	}
}

void HeroFireBowAir::Exit(HeroEntity* entity)
{

}

bool HeroFireBowAir::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroFireBowAir::HandleInput(HeroEntity* entity, int key, int action)
{
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
HeroDie* HeroDie::Instance()
{
	static HeroDie instance;

	return &instance;
}

void HeroDie::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerDie");
	entity->myAnimatedSprite->Reset();
}

void HeroDie::Execute(HeroEntity* entity)
{
	if(!entity->myAnimatedSprite->IsDone())
		entity->myAnimatedSprite->Update();
}

void HeroDie::Exit(HeroEntity* entity)
{

}

bool HeroDie::OnMessage(HeroEntity* entity, const Message& msg)
{
	return false;
}
bool HeroDie::HandleInput(HeroEntity* entity, int key, int action)
{
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
HeroDropKick* HeroDropKick::Instance()
{
	static HeroDropKick instance;

	return &instance;
}

void HeroDropKick::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerDropKick");
	entity->myAnimatedSprite->Reset();
	if (entity->myAnimatedSprite->myHeading == Heading::RIGHTFACING)
		entity->StartSliding(1);
	else
		entity->StartSliding(-1);
}

void HeroDropKick::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->IsOnSpikes())
		entity->GetFSM()->changeState(HeroDamaged::Instance());
	else
	{
		entity->myNegYDirection = -1.0f;
		entity->HandleDropKick();
	}

}

void HeroDropKick::Exit(HeroEntity* entity)
{

}

bool HeroDropKick::OnMessage(HeroEntity* entity, const Message& msg)
{
	return false;
}
bool HeroDropKick::HandleInput(HeroEntity* entity, int key, int action)
{
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroCastSpell* HeroCastSpell::Instance()
{
	static HeroCastSpell instance;

	return &instance;
}

void HeroCastSpell::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerCastSpell");
	entity->myAnimatedSprite->Reset();
	entity->myFiredProjectile = false;
}

void HeroCastSpell::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->myCurrentAnimation->myCurrentIndex == 3)
	{
		entity->SpawnProjectile();
	}
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(HeroIdle::Instance());
	}
}

void HeroCastSpell::Exit(HeroEntity* entity)
{

}

bool HeroCastSpell::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroCastSpell::HandleInput(HeroEntity* entity, int key, int action)
{
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroSheatheSword* HeroSheatheSword::Instance()
{
	static HeroSheatheSword instance;

	return &instance;
}

void HeroSheatheSword::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerSheatheSword");
	entity->myAnimatedSprite->Reset();
}

void HeroSheatheSword::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(HeroMeleeIdle::Instance());
	}

}

void HeroSheatheSword::Exit(HeroEntity* entity)
{

}

bool HeroSheatheSword::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroSheatheSword::HandleInput(HeroEntity* entity, int key, int action)
{
	return true;
}
//------------------------------------------------------------------------methods for HeroIdle
HeroMeleeIdle* HeroMeleeIdle::Instance()
{
	static HeroMeleeIdle instance;

	return &instance;
}


void HeroMeleeIdle::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerIdleSheathe");
}


void HeroMeleeIdle::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	entity->CheckIfFalling();
}


void HeroMeleeIdle::Exit(HeroEntity* entity)
{

}


bool HeroMeleeIdle::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroMeleeIdle::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
	entity->GetFSM()->changeState(HeroRunning::Instance());
	entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
	entity->GetFSM()->changeState(HeroRunning::Instance());
	entity->myNegYDirection = -1.0f;
	}*/
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroMeleeRun::Instance());
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroMeleeRun::Instance());
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroMeleeDrawSword::Instance());
	}
/*	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCrouch::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttackSword1::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}*/
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroMeleeSliding::Instance());
	}
/*	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroFireBowGround::Instance());
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCastSpell::Instance());
	}*/
	return true;
}
//------------------------------------------------------------------------methods for HeroRunning
HeroMeleeRun* HeroMeleeRun::Instance()
{
	static HeroMeleeRun instance;

	return &instance;
}


void HeroMeleeRun::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerRun");
	entity->myAnimatedSprite->Reset();
}


void HeroMeleeRun::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();

	entity->HandleMovement();
	entity->CheckIfFalling();
}


void HeroMeleeRun::Exit(HeroEntity* entity)
{

}


bool HeroMeleeRun::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroMeleeRun::HandleInput(HeroEntity* entity, int key, int action)
{
	/*if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
	entity->myPosYDirection = 1.0f;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
	entity->myNegYDirection = -1.0f;
	}*/
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		entity->myPosXDirection = 1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::RIGHTFACING);
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		entity->myNegXDirection = -1.5f;
		entity->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	}
/*	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCrouch::Instance());
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroAttackSword1::Instance());
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}*/
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroMeleeSliding::Instance());
	}/*
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroFireBowGround::Instance());
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroCastSpell::Instance());
	}*/
	return true;
}
//------------------------------------------------------------------------methods for HeroAttack
HeroMeleeDrawSword* HeroMeleeDrawSword::Instance()
{
	static HeroMeleeDrawSword instance;

	return &instance;
}

void HeroMeleeDrawSword::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerDrawSword");
	entity->myAnimatedSprite->Reset();
}

void HeroMeleeDrawSword::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();
	if (entity->myAnimatedSprite->IsDone())
	{
		entity->GetFSM()->changeState(HeroIdle::Instance());
	}

}

void HeroMeleeDrawSword::Exit(HeroEntity* entity)
{

}

bool HeroMeleeDrawSword::OnMessage(HeroEntity* entity, const Message& msg)
{

	switch (msg.mMsg)
	{
	case Msg_TakeDamage:
		MessageMan->dispatchMessage(0, entity->GetID(), 666, Msg_ShakeCamera, entity->myShakeInfoBasicAttack);
		entity->HandleDamaged(10);
		return true;

	}
	return false;
}
bool HeroMeleeDrawSword::HandleInput(HeroEntity* entity, int key, int action)
{
	return true;
}
HeroMeleeSliding* HeroMeleeSliding::Instance()
{
	static HeroMeleeSliding instance;

	return &instance;
}


void HeroMeleeSliding::Enter(HeroEntity* entity)
{
	entity->SetAnimation("AdventurerSlide");
	entity->myAnimatedSprite->Reset();
	if (entity->myAnimatedSprite->myHeading == Heading::RIGHTFACING)
		entity->StartSliding(1);
	else
		entity->StartSliding(-1);
}


void HeroMeleeSliding::Execute(HeroEntity* entity)
{
	entity->myAnimatedSprite->Update();

	entity->HandleSliding();
	entity->CheckIfFalling();

	if (Clock->GetCurrentTimeInSeconds() >= entity->myStartSlidingTime + 0.3f)
	{
		entity->GetFSM()->changeState(HeroMeleeIdle::Instance());
	}

}

void HeroMeleeSliding::Exit(HeroEntity* entity)
{

}

bool HeroMeleeSliding::OnMessage(HeroEntity* entity, const Message& msg)
{
	return true;
}
bool HeroMeleeSliding::HandleInput(HeroEntity* entity, int key, int action)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		entity->GetFSM()->changeState(HeroJumping::Instance());
	}
	return true;
}