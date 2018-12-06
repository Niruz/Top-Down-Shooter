#pragma once
#include "State.h"

class NecromancerEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class NecromancerIdle : public State<NecromancerEntity>
{
private:

	NecromancerIdle() {}

	//copy ctor and assignment should be private
	NecromancerIdle(const NecromancerIdle&);
	NecromancerIdle& operator=(const NecromancerIdle&);

public:

	//this is a singleton
	static NecromancerIdle* Instance();

	virtual void Enter(NecromancerEntity* entity);

	virtual void Execute(NecromancerEntity* entity);

	virtual void Exit(NecromancerEntity* entity);

	virtual bool OnMessage(NecromancerEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class NecromancerAttack : public State<NecromancerEntity>
{
private:

	NecromancerAttack() {}

	//copy ctor and assignment should be private
	NecromancerAttack(const NecromancerAttack&);
	NecromancerAttack& operator=(const NecromancerAttack&);

public:

	//this is a singleton
	static NecromancerAttack* Instance();

	virtual void Enter(NecromancerEntity* entity);

	virtual void Execute(NecromancerEntity* entity);

	virtual void Exit(NecromancerEntity* entity);

	virtual bool OnMessage(NecromancerEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class NecromancerHurt : public State<NecromancerEntity>
{
private:

	NecromancerHurt() {}

	//copy ctor and assignment should be private
	NecromancerHurt(const NecromancerHurt&);
	NecromancerHurt& operator=(const NecromancerHurt&);

public:

	//this is a singleton
	static NecromancerHurt* Instance();

	virtual void Enter(NecromancerEntity* entity);

	virtual void Execute(NecromancerEntity* entity);

	virtual void Exit(NecromancerEntity* entity);

	virtual bool OnMessage(NecromancerEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class NecromancerRunToPlayer : public State<NecromancerEntity>
{
private:

	NecromancerRunToPlayer() {}

	//copy ctor and assignment should be private
	NecromancerRunToPlayer(const NecromancerRunToPlayer&);
	NecromancerRunToPlayer& operator=(const NecromancerRunToPlayer&);

public:

	//this is a singleton
	static NecromancerRunToPlayer* Instance();

	virtual void Enter(NecromancerEntity* entity);

	virtual void Execute(NecromancerEntity* entity);

	virtual void Exit(NecromancerEntity* entity);

	virtual bool OnMessage(NecromancerEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class NecromancerPatrol : public State<NecromancerEntity>
{
private:

	NecromancerPatrol() {}

	//copy ctor and assignment should be private
	NecromancerPatrol(const NecromancerPatrol&);
	NecromancerPatrol& operator=(const NecromancerPatrol&);

public:

	//this is a singleton
	static NecromancerPatrol* Instance();

	virtual void Enter(NecromancerEntity* entity);

	virtual void Execute(NecromancerEntity* entity);

	virtual void Exit(NecromancerEntity* entity);

	virtual bool OnMessage(NecromancerEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class NecromancerDie : public State<NecromancerEntity>
{
private:

	NecromancerDie() {}

	//copy ctor and assignment should be private
	NecromancerDie(const NecromancerDie&);
	NecromancerDie& operator=(const NecromancerDie&);

public:

	//this is a singleton
	static NecromancerDie* Instance();

	virtual void Enter(NecromancerEntity* entity);

	virtual void Execute(NecromancerEntity* entity);

	virtual void Exit(NecromancerEntity* entity);

	virtual bool OnMessage(NecromancerEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class NecromancerRessurect : public State<NecromancerEntity>
{
private:

	NecromancerRessurect() {}

	//copy ctor and assignment should be private
	NecromancerRessurect(const NecromancerRessurect&);
	NecromancerRessurect& operator=(const NecromancerRessurect&);

public:

	//this is a singleton
	static NecromancerRessurect* Instance();

	virtual void Enter(NecromancerEntity* entity);

	virtual void Execute(NecromancerEntity* entity);

	virtual void Exit(NecromancerEntity* entity);

	virtual bool OnMessage(NecromancerEntity* entity, const Message& msg);

};