#pragma once
#include "State.h"

class BigSkeletonEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BigSkeletonIdle : public State<BigSkeletonEntity>
{
private:

	BigSkeletonIdle() {}

	//copy ctor and assignment should be private
	BigSkeletonIdle(const BigSkeletonIdle&);
	BigSkeletonIdle& operator=(const BigSkeletonIdle&);

public:

	//this is a singleton
	static BigSkeletonIdle* Instance();

	virtual void Enter(BigSkeletonEntity* entity);

	virtual void Execute(BigSkeletonEntity* entity);

	virtual void Exit(BigSkeletonEntity* entity);

	virtual bool OnMessage(BigSkeletonEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BigSkeletonAttack : public State<BigSkeletonEntity>
{
private:

	BigSkeletonAttack() {}

	//copy ctor and assignment should be private
	BigSkeletonAttack(const BigSkeletonAttack&);
	BigSkeletonAttack& operator=(const BigSkeletonAttack&);

public:

	//this is a singleton
	static BigSkeletonAttack* Instance();

	virtual void Enter(BigSkeletonEntity* entity);

	virtual void Execute(BigSkeletonEntity* entity);

	virtual void Exit(BigSkeletonEntity* entity);

	virtual bool OnMessage(BigSkeletonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BigSkeletonHurt : public State<BigSkeletonEntity>
{
private:

	BigSkeletonHurt() {}

	//copy ctor and assignment should be private
	BigSkeletonHurt(const BigSkeletonHurt&);
	BigSkeletonHurt& operator=(const BigSkeletonHurt&);

public:

	//this is a singleton
	static BigSkeletonHurt* Instance();

	virtual void Enter(BigSkeletonEntity* entity);

	virtual void Execute(BigSkeletonEntity* entity);

	virtual void Exit(BigSkeletonEntity* entity);

	virtual bool OnMessage(BigSkeletonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BigSkeletonRunToPlayer : public State<BigSkeletonEntity>
{
private:

	BigSkeletonRunToPlayer() {}

	//copy ctor and assignment should be private
	BigSkeletonRunToPlayer(const BigSkeletonRunToPlayer&);
	BigSkeletonRunToPlayer& operator=(const BigSkeletonRunToPlayer&);

public:

	//this is a singleton
	static BigSkeletonRunToPlayer* Instance();

	virtual void Enter(BigSkeletonEntity* entity);

	virtual void Execute(BigSkeletonEntity* entity);

	virtual void Exit(BigSkeletonEntity* entity);

	virtual bool OnMessage(BigSkeletonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BigSkeletonPatrol : public State<BigSkeletonEntity>
{
private:

	BigSkeletonPatrol() {}

	//copy ctor and assignment should be private
	BigSkeletonPatrol(const BigSkeletonPatrol&);
	BigSkeletonPatrol& operator=(const BigSkeletonPatrol&);

public:

	//this is a singleton
	static BigSkeletonPatrol* Instance();

	virtual void Enter(BigSkeletonEntity* entity);

	virtual void Execute(BigSkeletonEntity* entity);

	virtual void Exit(BigSkeletonEntity* entity);

	virtual bool OnMessage(BigSkeletonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BigSkeletonDie : public State<BigSkeletonEntity>
{
private:

	BigSkeletonDie() {}

	//copy ctor and assignment should be private
	BigSkeletonDie(const BigSkeletonDie&);
	BigSkeletonDie& operator=(const BigSkeletonDie&);

public:

	//this is a singleton
	static BigSkeletonDie* Instance();

	virtual void Enter(BigSkeletonEntity* entity);

	virtual void Execute(BigSkeletonEntity* entity);

	virtual void Exit(BigSkeletonEntity* entity);

	virtual bool OnMessage(BigSkeletonEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
class BigSkeletonRessurect : public State<BigSkeletonEntity>
{
private:

	BigSkeletonRessurect() {}

	//copy ctor and assignment should be private
	BigSkeletonRessurect(const BigSkeletonRessurect&);
	BigSkeletonRessurect& operator=(const BigSkeletonRessurect&);

public:

	//this is a singleton
	static BigSkeletonRessurect* Instance();

	virtual void Enter(BigSkeletonEntity* entity);

	virtual void Execute(BigSkeletonEntity* entity);

	virtual void Exit(BigSkeletonEntity* entity);

	virtual bool OnMessage(BigSkeletonEntity* entity, const Message& msg);

};