#pragma once
#include "State.h"

class ReaperEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ReaperIdle : public State<ReaperEntity>
{
private:

	ReaperIdle() {}

	//copy ctor and assignment should be private
	ReaperIdle(const ReaperIdle&);
	ReaperIdle& operator=(const ReaperIdle&);

public:

	//this is a singleton
	static ReaperIdle* Instance();

	virtual void Enter(ReaperEntity* entity);

	virtual void Execute(ReaperEntity* entity);

	virtual void Exit(ReaperEntity* entity);

	virtual bool OnMessage(ReaperEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ReaperAttack : public State<ReaperEntity>
{
private:

	ReaperAttack() {}

	//copy ctor and assignment should be private
	ReaperAttack(const ReaperAttack&);
	ReaperAttack& operator=(const ReaperAttack&);

public:

	//this is a singleton
	static ReaperAttack* Instance();

	virtual void Enter(ReaperEntity* entity);

	virtual void Execute(ReaperEntity* entity);

	virtual void Exit(ReaperEntity* entity);

	virtual bool OnMessage(ReaperEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ReaperHurt : public State<ReaperEntity>
{
private:

	ReaperHurt() {}

	//copy ctor and assignment should be private
	ReaperHurt(const ReaperHurt&);
	ReaperHurt& operator=(const ReaperHurt&);

public:

	//this is a singleton
	static ReaperHurt* Instance();

	virtual void Enter(ReaperEntity* entity);

	virtual void Execute(ReaperEntity* entity);

	virtual void Exit(ReaperEntity* entity);

	virtual bool OnMessage(ReaperEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ReaperRunToPlayer : public State<ReaperEntity>
{
private:

	ReaperRunToPlayer() {}

	//copy ctor and assignment should be private
	ReaperRunToPlayer(const ReaperRunToPlayer&);
	ReaperRunToPlayer& operator=(const ReaperRunToPlayer&);

public:

	//this is a singleton
	static ReaperRunToPlayer* Instance();

	virtual void Enter(ReaperEntity* entity);

	virtual void Execute(ReaperEntity* entity);

	virtual void Exit(ReaperEntity* entity);

	virtual bool OnMessage(ReaperEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ReaperPatrol : public State<ReaperEntity>
{
private:

	ReaperPatrol() {}

	//copy ctor and assignment should be private
	ReaperPatrol(const ReaperPatrol&);
	ReaperPatrol& operator=(const ReaperPatrol&);

public:

	//this is a singleton
	static ReaperPatrol* Instance();

	virtual void Enter(ReaperEntity* entity);

	virtual void Execute(ReaperEntity* entity);

	virtual void Exit(ReaperEntity* entity);

	virtual bool OnMessage(ReaperEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ReaperDie : public State<ReaperEntity>
{
private:

	ReaperDie() {}

	//copy ctor and assignment should be private
	ReaperDie(const ReaperDie&);
	ReaperDie& operator=(const ReaperDie&);

public:

	//this is a singleton
	static ReaperDie* Instance();

	virtual void Enter(ReaperEntity* entity);

	virtual void Execute(ReaperEntity* entity);

	virtual void Exit(ReaperEntity* entity);

	virtual bool OnMessage(ReaperEntity* entity, const Message& msg);

};