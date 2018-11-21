#pragma once
#include "State.h"

class GhostEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class GhostPatrol : public State<GhostEntity>
{
private:

	GhostPatrol() {}

	//copy ctor and assignment should be private
	GhostPatrol(const GhostPatrol&);
	GhostPatrol& operator=(const GhostPatrol&);

public:

	//this is a singleton
	static GhostPatrol* Instance();

	virtual void Enter(GhostEntity* entity);

	virtual void Execute(GhostEntity* entity);

	virtual void Exit(GhostEntity* entity);

	virtual bool OnMessage(GhostEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class GhostAttack : public State<GhostEntity>
{
private:

	GhostAttack() {}

	//copy ctor and assignment should be private
	GhostAttack(const GhostPatrol&);
	GhostAttack& operator=(const GhostPatrol&);

public:

	//this is a singleton
	static GhostAttack* Instance();

	virtual void Enter(GhostEntity* entity);

	virtual void Execute(GhostEntity* entity);

	virtual void Exit(GhostEntity* entity);

	virtual bool OnMessage(GhostEntity* entity, const Message& msg);

};