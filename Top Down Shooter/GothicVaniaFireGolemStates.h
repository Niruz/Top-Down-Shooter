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
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class FireGolemRunToPlayer : public State<FireGolemEntity>
{
private:

	FireGolemRunToPlayer() {}

	//copy ctor and assignment should be private
	FireGolemRunToPlayer(const FireGolemRunToPlayer&);
	FireGolemRunToPlayer& operator=(const FireGolemRunToPlayer&);

public:

	//this is a singleton
	static FireGolemRunToPlayer* Instance();

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
class FireGolemHurt : public State<FireGolemEntity>
{
private:

	FireGolemHurt() {}

	//copy ctor and assignment should be private
	FireGolemHurt(const FireGolemHurt&);
	FireGolemHurt& operator=(const FireGolemHurt&);

public:

	//this is a singleton
	static FireGolemHurt* Instance();

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
class FireGolemDie : public State<FireGolemEntity>
{
private:

	FireGolemDie() {}

	//copy ctor and assignment should be private
	FireGolemDie(const FireGolemDie&);
	FireGolemDie& operator=(const FireGolemDie&);

public:

	//this is a singleton
	static FireGolemDie* Instance();

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
class FireGolemSlam : public State<FireGolemEntity>
{
private:

	FireGolemSlam() {}

	//copy ctor and assignment should be private
	FireGolemSlam(const FireGolemSlam&);
	FireGolemSlam& operator=(const FireGolemSlam&);

public:

	//this is a singleton
	static FireGolemSlam* Instance();

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
class FireGolemReturnHome : public State<FireGolemEntity>
{
private:

	FireGolemReturnHome() {}

	//copy ctor and assignment should be private
	FireGolemReturnHome(const FireGolemReturnHome&);
	FireGolemReturnHome& operator=(const FireGolemReturnHome&);

public:

	//this is a singleton
	static FireGolemReturnHome* Instance();

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
class FireGolemPatrol : public State<FireGolemEntity>
{
private:

	FireGolemPatrol() {}

	//copy ctor and assignment should be private
	FireGolemPatrol(const FireGolemPatrol&);
	FireGolemPatrol& operator=(const FireGolemPatrol&);

public:

	//this is a singleton
	static FireGolemPatrol* Instance();

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
class FireGolemWaiting : public State<FireGolemEntity>
{
private:

	FireGolemWaiting() {}

	//copy ctor and assignment should be private
	FireGolemWaiting(const FireGolemWaiting&);
	FireGolemWaiting& operator=(const FireGolemWaiting&);

public:

	//this is a singleton
	static FireGolemWaiting* Instance();

	virtual void Enter(FireGolemEntity* entity);

	virtual void Execute(FireGolemEntity* entity);

	virtual void Exit(FireGolemEntity* entity);

	virtual bool OnMessage(FireGolemEntity* entity, const Message& msg);

};