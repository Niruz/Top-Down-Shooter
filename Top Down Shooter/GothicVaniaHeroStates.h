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

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSwordAir1 : public State<HeroEntity>
{
private:

	HeroAttackSwordAir1() {}

	//copy ctor and assignment should be private
	HeroAttackSwordAir1(const HeroAttackSwordAir1&);
	HeroAttackSwordAir1& operator=(const HeroAttackSwordAir1&);

public:

	//this is a singleton
	static HeroAttackSwordAir1* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSwordAir2 : public State<HeroEntity>
{
private:

	HeroAttackSwordAir2() {}

	//copy ctor and assignment should be private
	HeroAttackSwordAir2(const HeroAttackSwordAir2&);
	HeroAttackSwordAir2& operator=(const HeroAttackSwordAir2&);

public:

	//this is a singleton
	static HeroAttackSwordAir2* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSwordAir3 : public State<HeroEntity>
{
private:

	HeroAttackSwordAir3() {}

	//copy ctor and assignment should be private
	HeroAttackSwordAir3(const HeroAttackSwordAir3&);
	HeroAttackSwordAir3& operator=(const HeroAttackSwordAir3&);

public:

	//this is a singleton
	static HeroAttackSwordAir3* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSword1 : public State<HeroEntity>
{
private:

	HeroAttackSword1() {}

	//copy ctor and assignment should be private
	HeroAttackSword1(const HeroAttackSword1&);
	HeroAttackSword1& operator=(const HeroAttackSword1&);

public:

	//this is a singleton
	static HeroAttackSword1* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);
	
	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSword2 : public State<HeroEntity>
{
private:

	HeroAttackSword2() {}

	//copy ctor and assignment should be private
	HeroAttackSword2(const HeroAttackSword2&);
	HeroAttackSword2& operator=(const HeroAttackSword2&);

public:

	//this is a singleton
	static HeroAttackSword2* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Attack state for the hero
//  
//------------------------------------------------------------------------
class HeroAttackSword3 : public State<HeroEntity>
{
private:

	HeroAttackSword3() {}

	//copy ctor and assignment should be private
	HeroAttackSword3(const HeroAttackSword3&);
	HeroAttackSword3& operator=(const HeroAttackSword3&);

public:

	//this is a singleton
	static HeroAttackSword3* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
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

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
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

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
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

	virtual bool HandleInput(HeroEntity* entity, int key, int action);
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

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};
//
//  Damaged state for the hero
//  
//------------------------------------------------------------------------
class HeroDamaged : public State<HeroEntity>
{
private:

	HeroDamaged() {}

	//copy ctor and assignment should be private
	HeroDamaged(const HeroJumping&);
	HeroDamaged& operator=(const HeroJumping&);

public:

	//this is a singleton
	static HeroDamaged* Instance();

	virtual void Enter(HeroEntity* entity);

	virtual void Execute(HeroEntity* entity);

	virtual void Exit(HeroEntity* entity);

	virtual bool OnMessage(HeroEntity* entity, const Message& msg);

	virtual bool HandleInput(HeroEntity* entity, int key, int action);

};