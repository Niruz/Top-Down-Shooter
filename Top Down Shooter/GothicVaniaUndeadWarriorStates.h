#pragma once
#include "State.h"

class UndeadWarriorEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class UndeadWarriorIdle : public State<UndeadWarriorEntity>
{
private:

	UndeadWarriorIdle() {}

	//copy ctor and assignment should be private
	UndeadWarriorIdle(const UndeadWarriorIdle&);
	UndeadWarriorIdle& operator=(const UndeadWarriorIdle&);

public:

	//this is a singleton
	static UndeadWarriorIdle* Instance();

	virtual void Enter(UndeadWarriorEntity* entity);

	virtual void Execute(UndeadWarriorEntity* entity);

	virtual void Exit(UndeadWarriorEntity* entity);

	virtual bool OnMessage(UndeadWarriorEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class UndeadWarriorAttack : public State<UndeadWarriorEntity>
{
private:

	UndeadWarriorAttack() {}

	//copy ctor and assignment should be private
	UndeadWarriorAttack(const UndeadWarriorAttack&);
	UndeadWarriorAttack& operator=(const UndeadWarriorAttack&);

public:

	//this is a singleton
	static UndeadWarriorAttack* Instance();

	virtual void Enter(UndeadWarriorEntity* entity);

	virtual void Execute(UndeadWarriorEntity* entity);

	virtual void Exit(UndeadWarriorEntity* entity);

	virtual bool OnMessage(UndeadWarriorEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class UndeadWarriorHurt : public State<UndeadWarriorEntity>
{
private:

	UndeadWarriorHurt() {}

	//copy ctor and assignment should be private
	UndeadWarriorHurt(const UndeadWarriorHurt&);
	UndeadWarriorHurt& operator=(const UndeadWarriorHurt&);

public:

	//this is a singleton
	static UndeadWarriorHurt* Instance();

	virtual void Enter(UndeadWarriorEntity* entity);

	virtual void Execute(UndeadWarriorEntity* entity);

	virtual void Exit(UndeadWarriorEntity* entity);

	virtual bool OnMessage(UndeadWarriorEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class UndeadWarriorRunToPlayer : public State<UndeadWarriorEntity>
{
private:

	UndeadWarriorRunToPlayer() {}

	//copy ctor and assignment should be private
	UndeadWarriorRunToPlayer(const UndeadWarriorRunToPlayer&);
	UndeadWarriorRunToPlayer& operator=(const UndeadWarriorRunToPlayer&);

public:

	//this is a singleton
	static UndeadWarriorRunToPlayer* Instance();

	virtual void Enter(UndeadWarriorEntity* entity);

	virtual void Execute(UndeadWarriorEntity* entity);

	virtual void Exit(UndeadWarriorEntity* entity);

	virtual bool OnMessage(UndeadWarriorEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class UndeadWarriorPatrol : public State<UndeadWarriorEntity>
{
private:

	UndeadWarriorPatrol() {}

	//copy ctor and assignment should be private
	UndeadWarriorPatrol(const UndeadWarriorPatrol&);
	UndeadWarriorPatrol& operator=(const UndeadWarriorPatrol&);

public:

	//this is a singleton
	static UndeadWarriorPatrol* Instance();

	virtual void Enter(UndeadWarriorEntity* entity);

	virtual void Execute(UndeadWarriorEntity* entity);

	virtual void Exit(UndeadWarriorEntity* entity);

	virtual bool OnMessage(UndeadWarriorEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class UndeadWarriorDie : public State<UndeadWarriorEntity>
{
private:

	UndeadWarriorDie() {}

	//copy ctor and assignment should be private
	UndeadWarriorDie(const UndeadWarriorDie&);
	UndeadWarriorDie& operator=(const UndeadWarriorDie&);

public:

	//this is a singleton
	static UndeadWarriorDie* Instance();

	virtual void Enter(UndeadWarriorEntity* entity);

	virtual void Execute(UndeadWarriorEntity* entity);

	virtual void Exit(UndeadWarriorEntity* entity);

	virtual bool OnMessage(UndeadWarriorEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
class UndeadWarriorRessurect : public State<UndeadWarriorEntity>
{
private:

	UndeadWarriorRessurect() {}

	//copy ctor and assignment should be private
	UndeadWarriorRessurect(const UndeadWarriorRessurect&);
	UndeadWarriorRessurect& operator=(const UndeadWarriorRessurect&);

public:

	//this is a singleton
	static UndeadWarriorRessurect* Instance();

	virtual void Enter(UndeadWarriorEntity* entity);

	virtual void Execute(UndeadWarriorEntity* entity);

	virtual void Exit(UndeadWarriorEntity* entity);

	virtual bool OnMessage(UndeadWarriorEntity* entity, const Message& msg);

};