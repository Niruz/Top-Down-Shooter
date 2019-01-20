#pragma once
#include "State.h"

class ShriekerEntity;

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ShriekerIdle : public State<ShriekerEntity>
{
private:

	ShriekerIdle() {}

	//copy ctor and assignment should be private
	ShriekerIdle(const ShriekerIdle&);
	ShriekerIdle& operator=(const ShriekerIdle&);

public:

	//this is a singleton
	static ShriekerIdle* Instance();

	virtual void Enter(ShriekerEntity* entity);

	virtual void Execute(ShriekerEntity* entity);

	virtual void Exit(ShriekerEntity* entity);

	virtual bool OnMessage(ShriekerEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ShriekerAppear : public State<ShriekerEntity>
{
private:

	ShriekerAppear() {}

	//copy ctor and assignment should be private
	ShriekerAppear(const ShriekerAppear&);
	ShriekerAppear& operator=(const ShriekerAppear&);

public:

	//this is a singleton
	static ShriekerAppear* Instance();

	virtual void Enter(ShriekerEntity* entity);

	virtual void Execute(ShriekerEntity* entity);

	virtual void Exit(ShriekerEntity* entity);

	virtual bool OnMessage(ShriekerEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ShriekerAttack : public State<ShriekerEntity>
{
private:

	ShriekerAttack() {}

	//copy ctor and assignment should be private
	ShriekerAttack(const ShriekerAttack&);
	ShriekerAttack& operator=(const ShriekerAttack&);

public:

	//this is a singleton
	static ShriekerAttack* Instance();

	virtual void Enter(ShriekerEntity* entity);

	virtual void Execute(ShriekerEntity* entity);

	virtual void Exit(ShriekerEntity* entity);

	virtual bool OnMessage(ShriekerEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ShriekerDisappear : public State<ShriekerEntity>
{
private:

	ShriekerDisappear() {}

	//copy ctor and assignment should be private
	ShriekerDisappear(const ShriekerDisappear&);
	ShriekerDisappear& operator=(const ShriekerDisappear&);

public:

	//this is a singleton
	static ShriekerDisappear* Instance();

	virtual void Enter(ShriekerEntity* entity);

	virtual void Execute(ShriekerEntity* entity);

	virtual void Exit(ShriekerEntity* entity);

	virtual bool OnMessage(ShriekerEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ShriekerHurt : public State<ShriekerEntity>
{
private:

	ShriekerHurt() {}

	//copy ctor and assignment should be private
	ShriekerHurt(const ShriekerHurt&);
	ShriekerHurt& operator=(const ShriekerHurt&);

public:

	//this is a singleton
	static ShriekerHurt* Instance();

	virtual void Enter(ShriekerEntity* entity);

	virtual void Execute(ShriekerEntity* entity);

	virtual void Exit(ShriekerEntity* entity);

	virtual bool OnMessage(ShriekerEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class ShriekerDie : public State<ShriekerEntity>
{
private:

	ShriekerDie() {}

	//copy ctor and assignment should be private
	ShriekerDie(const ShriekerDie&);
	ShriekerDie& operator=(const ShriekerDie&);

public:

	//this is a singleton
	static ShriekerDie* Instance();

	virtual void Enter(ShriekerEntity* entity);

	virtual void Execute(ShriekerEntity* entity);

	virtual void Exit(ShriekerEntity* entity);

	virtual bool OnMessage(ShriekerEntity* entity, const Message& msg);

};

