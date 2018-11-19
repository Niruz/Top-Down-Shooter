#pragma once
#include "State.h"

class HeroEntity;
//------------------------------------------------------------------------
//
//  Idle state for the hero
//  
//------------------------------------------------------------------------
class HeroIdle : public State<HeroEntity>
{
private:

	HeroIdle() {}

	//copy ctor and assignment should be private
	HeroIdle(const HeroIdle&);
	HeroIdle& operator=(const HeroIdle&);

public:

	//this is a singleton
	static HeroIdle* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttack : public State<HeroEntity>
{
private:

	HeroAttack() {}

	//copy ctor and assignment should be private
	HeroAttack(const HeroAttack&);
	HeroAttack& operator=(const HeroAttack&);

public:

	//this is a singleton
	static HeroAttack* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);
};
//------------------------------------------------------------------------
//
//  Crouch state for the hero
//  
//------------------------------------------------------------------------
class HeroCrouch : public State<HeroEntity>
{
private:

	HeroCrouch() {}

	//copy ctor and assignment should be private
	HeroCrouch(const HeroCrouch&);
	HeroCrouch& operator=(const HeroCrouch&);

public:

	//this is a singleton
	static HeroCrouch* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);
};
//------------------------------------------------------------------------
//
//  Running state for the hero
//  
//------------------------------------------------------------------------
class HeroRunning : public State<HeroEntity>
{
private:

	HeroRunning() {}

	//copy ctor and assignment should be private
	HeroRunning(const HeroRunning&);
	HeroRunning& operator=(const HeroRunning&);

public:

	//this is a singleton
	static HeroRunning* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);
};//------------------------------------------------------------------------
//
//  Falling state for the hero
//  
//------------------------------------------------------------------------
class HeroFalling : public State<HeroEntity>
{
private:

	HeroFalling() {}

	//copy ctor and assignment should be private
	HeroFalling(const HeroFalling&);
	HeroFalling& operator=(const HeroFalling&);

public:

	//this is a singleton
	static HeroFalling* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);
};
//
//  Jumping state for the hero
//  
//------------------------------------------------------------------------
class HeroJumping : public State<HeroEntity>
{
private:

	HeroJumping() {}

	//copy ctor and assignment should be private
	HeroJumping(const HeroJumping&);
	HeroJumping& operator=(const HeroJumping&);

public:

	//this is a singleton
	static HeroJumping* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

};