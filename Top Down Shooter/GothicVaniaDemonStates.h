#pragma once
#include "State.h"

class DemonEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class DemonIdle : public State<DemonEntity>
{
private:

	DemonIdle() {}

	//copy ctor and assignment should be private
	DemonIdle(const DemonIdle&);
	DemonIdle& operator=(const DemonIdle&);

public:

	//this is a singleton
	static DemonIdle* Instance();

	virtual void Enter(DemonEntity* entity);

	virtual void Execute(DemonEntity* entity);

	virtual void Exit(DemonEntity* entity);

	virtual bool OnMessage(DemonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class DemonAttack : public State<DemonEntity>
{
private:

	DemonAttack() {}

	//copy ctor and assignment should be private
	DemonAttack(const DemonAttack&);
	DemonAttack& operator=(const DemonAttack&);

public:

	//this is a singleton
	static DemonAttack* Instance();

	virtual void Enter(DemonEntity* entity);

	virtual void Execute(DemonEntity* entity);

	virtual void Exit(DemonEntity* entity);

	virtual bool OnMessage(DemonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class DemonWindup : public State<DemonEntity>
{
private:

	DemonWindup() {}

	//copy ctor and assignment should be private
	DemonWindup(const DemonWindup&);
	DemonWindup& operator=(const DemonWindup&);

public:

	//this is a singleton
	static DemonWindup* Instance();

	virtual void Enter(DemonEntity* entity);

	virtual void Execute(DemonEntity* entity);

	virtual void Exit(DemonEntity* entity);

	virtual bool OnMessage(DemonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class DemonWindDown : public State<DemonEntity>
{
private:

	DemonWindDown() {}

	//copy ctor and assignment should be private
	DemonWindDown(const DemonWindDown&);
	DemonWindDown& operator=(const DemonWindDown&);

public:

	//this is a singleton
	static DemonWindDown* Instance();

	virtual void Enter(DemonEntity* entity);

	virtual void Execute(DemonEntity* entity);

	virtual void Exit(DemonEntity* entity);

	virtual bool OnMessage(DemonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class DemonAwaitingOrders : public State<DemonEntity>
{
private:

	DemonAwaitingOrders() {}

	//copy ctor and assignment should be private
	DemonAwaitingOrders(const DemonAwaitingOrders&);
	DemonAwaitingOrders& operator=(const DemonAwaitingOrders&);

public:

	//this is a singleton
	static DemonAwaitingOrders* Instance();

	virtual void Enter(DemonEntity* entity);

	virtual void Execute(DemonEntity* entity);

	virtual void Exit(DemonEntity* entity);

	virtual bool OnMessage(DemonEntity* entity, const Message& msg);

};