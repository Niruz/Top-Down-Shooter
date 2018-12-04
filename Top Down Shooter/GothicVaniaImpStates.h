#pragma once
#include "State.h"

class ImpEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ImpIdle : public State<ImpEntity>
{
private:

	ImpIdle() {}

	//copy ctor and assignment should be private
	ImpIdle(const ImpIdle&);
	ImpIdle& operator=(const ImpIdle&);

public:

	//this is a singleton
	static ImpIdle* Instance();

	virtual void Enter(ImpEntity* entity);

	virtual void Execute(ImpEntity* entity);

	virtual void Exit(ImpEntity* entity);

	virtual bool OnMessage(ImpEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ImpAttack : public State<ImpEntity>
{
private:

	ImpAttack() {}

	//copy ctor and assignment should be private
	ImpAttack(const ImpAttack&);
	ImpAttack& operator=(const ImpAttack&);

public:

	//this is a singleton
	static ImpAttack* Instance();

	virtual void Enter(ImpEntity* entity);

	virtual void Execute(ImpEntity* entity);

	virtual void Exit(ImpEntity* entity);

	virtual bool OnMessage(ImpEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ImpHurt : public State<ImpEntity>
{
private:

	ImpHurt() {}

	//copy ctor and assignment should be private
	ImpHurt(const ImpHurt&);
	ImpHurt& operator=(const ImpHurt&);

public:

	//this is a singleton
	static ImpHurt* Instance();

	virtual void Enter(ImpEntity* entity);

	virtual void Execute(ImpEntity* entity);

	virtual void Exit(ImpEntity* entity);

	virtual bool OnMessage(ImpEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ImpRunToPlayer : public State<ImpEntity>
{
private:

	ImpRunToPlayer() {}

	//copy ctor and assignment should be private
	ImpRunToPlayer(const ImpRunToPlayer&);
	ImpRunToPlayer& operator=(const ImpRunToPlayer&);

public:

	//this is a singleton
	static ImpRunToPlayer* Instance();

	virtual void Enter(ImpEntity* entity);

	virtual void Execute(ImpEntity* entity);

	virtual void Exit(ImpEntity* entity);

	virtual bool OnMessage(ImpEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ImpPatrol : public State<ImpEntity>
{
private:

	ImpPatrol() {}

	//copy ctor and assignment should be private
	ImpPatrol(const ImpPatrol&);
	ImpPatrol& operator=(const ImpPatrol&);

public:

	//this is a singleton
	static ImpPatrol* Instance();

	virtual void Enter(ImpEntity* entity);

	virtual void Execute(ImpEntity* entity);

	virtual void Exit(ImpEntity* entity);

	virtual bool OnMessage(ImpEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ImpDie : public State<ImpEntity>
{
private:

	ImpDie() {}

	//copy ctor and assignment should be private
	ImpDie(const ImpDie&);
	ImpDie& operator=(const ImpDie&);

public:

	//this is a singleton
	static ImpDie* Instance();

	virtual void Enter(ImpEntity* entity);

	virtual void Execute(ImpEntity* entity);

	virtual void Exit(ImpEntity* entity);

	virtual bool OnMessage(ImpEntity* entity, const Message& msg);

};