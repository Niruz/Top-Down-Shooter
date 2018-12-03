#pragma once
#include "State.h"

class GhoulEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class GhoulIdle : public State<GhoulEntity>
{
private:

	GhoulIdle() {}

	//copy ctor and assignment should be private
	GhoulIdle(const GhoulIdle&);
	GhoulIdle& operator=(const GhoulIdle&);

public:

	//this is a singleton
	static GhoulIdle* Instance();

	virtual void Enter(GhoulEntity* entity);

	virtual void Execute(GhoulEntity* entity);

	virtual void Exit(GhoulEntity* entity);

	virtual bool OnMessage(GhoulEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class GhoulAttack : public State<GhoulEntity>
{
private:

	GhoulAttack() {}

	//copy ctor and assignment should be private
	GhoulAttack(const GhoulAttack&);
	GhoulAttack& operator=(const GhoulAttack&);

public:

	//this is a singleton
	static GhoulAttack* Instance();

	virtual void Enter(GhoulEntity* entity);

	virtual void Execute(GhoulEntity* entity);

	virtual void Exit(GhoulEntity* entity);

	virtual bool OnMessage(GhoulEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class GhoulHurt : public State<GhoulEntity>
{
private:

	GhoulHurt() {}

	//copy ctor and assignment should be private
	GhoulHurt(const GhoulHurt&);
	GhoulHurt& operator=(const GhoulHurt&);

public:

	//this is a singleton
	static GhoulHurt* Instance();

	virtual void Enter(GhoulEntity* entity);

	virtual void Execute(GhoulEntity* entity);

	virtual void Exit(GhoulEntity* entity);

	virtual bool OnMessage(GhoulEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class GhoulRunToPlayer : public State<GhoulEntity>
{
private:

	GhoulRunToPlayer() {}

	//copy ctor and assignment should be private
	GhoulRunToPlayer(const GhoulRunToPlayer&);
	GhoulRunToPlayer& operator=(const GhoulRunToPlayer&);

public:

	//this is a singleton
	static GhoulRunToPlayer* Instance();

	virtual void Enter(GhoulEntity* entity);

	virtual void Execute(GhoulEntity* entity);

	virtual void Exit(GhoulEntity* entity);

	virtual bool OnMessage(GhoulEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class GhoulPatrol : public State<GhoulEntity>
{
private:

	GhoulPatrol() {}

	//copy ctor and assignment should be private
	GhoulPatrol(const GhoulPatrol&);
	GhoulPatrol& operator=(const GhoulPatrol&);

public:

	//this is a singleton
	static GhoulPatrol* Instance();

	virtual void Enter(GhoulEntity* entity);

	virtual void Execute(GhoulEntity* entity);

	virtual void Exit(GhoulEntity* entity);

	virtual bool OnMessage(GhoulEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class GhoulDie : public State<GhoulEntity>
{
private:

	GhoulDie() {}

	//copy ctor and assignment should be private
	GhoulDie(const GhoulDie&);
	GhoulDie& operator=(const GhoulDie&);

public:

	//this is a singleton
	static GhoulDie* Instance();

	virtual void Enter(GhoulEntity* entity);

	virtual void Execute(GhoulEntity* entity);

	virtual void Exit(GhoulEntity* entity);

	virtual bool OnMessage(GhoulEntity* entity, const Message& msg);

};