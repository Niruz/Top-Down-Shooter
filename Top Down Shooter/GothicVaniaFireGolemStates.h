#pragma once
#include "State.h"

class FireGolemEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class FireGolemIdle : public State<FireGolemEntity>
{
private:

	FireGolemIdle() {}

	//copy ctor and assignment should be private
	FireGolemIdle(const FireGolemIdle&);
	FireGolemIdle& operator=(const FireGolemIdle&);

public:

	//this is a singleton
	static FireGolemIdle* Instance();

	virtual void Enter(FireGolemEntity* entity);

	virtual void Execute(FireGolemEntity* entity);

	virtual void Exit(FireGolemEntity* entity);

	virtual bool OnMessage(FireGolemEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class FireGolemAttack1 : public State<FireGolemEntity>
{
private:

	FireGolemAttack1() {}

	//copy ctor and assignment should be private
	FireGolemAttack1(const FireGolemAttack1&);
	FireGolemAttack1& operator=(const FireGolemAttack1&);

public:

	//this is a singleton
	static FireGolemAttack1* Instance();

	virtual void Enter(FireGolemEntity* entity);

	virtual void Execute(FireGolemEntity* entity);

	virtual void Exit(FireGolemEntity* entity);

	virtual bool OnMessage(FireGolemEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class FireGolemAttack2 : public State<FireGolemEntity>
{
private:

	FireGolemAttack2() {}

	//copy ctor and assignment should be private
	FireGolemAttack2(const FireGolemAttack2&);
	FireGolemAttack2& operator=(const FireGolemAttack2&);

public:

	//this is a singleton
	static FireGolemAttack2* Instance();

	virtual void Enter(FireGolemEntity* entity);

	virtual void Execute(FireGolemEntity* entity);

	virtual void Exit(FireGolemEntity* entity);

	virtual bool OnMessage(FireGolemEntity* entity, const Message& msg);

};