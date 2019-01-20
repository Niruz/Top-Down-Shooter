#pragma once
#include "State.h"

class BattlePriestEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BattlePriestIdle : public State<BattlePriestEntity>
{
private:

	BattlePriestIdle() {}

	//copy ctor and assignment should be private
	BattlePriestIdle(const BattlePriestIdle&);
	BattlePriestIdle& operator=(const BattlePriestIdle&);

public:

	//this is a singleton
	static BattlePriestIdle* Instance();

	virtual void Enter(BattlePriestEntity* entity);

	virtual void Execute(BattlePriestEntity* entity);

	virtual void Exit(BattlePriestEntity* entity);

	virtual bool OnMessage(BattlePriestEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BattlePriestAttack : public State<BattlePriestEntity>
{
private:

	BattlePriestAttack() {}

	//copy ctor and assignment should be private
	BattlePriestAttack(const BattlePriestAttack&);
	BattlePriestAttack& operator=(const BattlePriestAttack&);

public:

	//this is a singleton
	static BattlePriestAttack* Instance();

	virtual void Enter(BattlePriestEntity* entity);

	virtual void Execute(BattlePriestEntity* entity);

	virtual void Exit(BattlePriestEntity* entity);

	virtual bool OnMessage(BattlePriestEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BattlePriestHurt : public State<BattlePriestEntity>
{
private:

	BattlePriestHurt() {}

	//copy ctor and assignment should be private
	BattlePriestHurt(const BattlePriestHurt&);
	BattlePriestHurt& operator=(const BattlePriestHurt&);

public:

	//this is a singleton
	static BattlePriestHurt* Instance();

	virtual void Enter(BattlePriestEntity* entity);

	virtual void Execute(BattlePriestEntity* entity);

	virtual void Exit(BattlePriestEntity* entity);

	virtual bool OnMessage(BattlePriestEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BattlePriestRunToPlayer : public State<BattlePriestEntity>
{
private:

	BattlePriestRunToPlayer() {}

	//copy ctor and assignment should be private
	BattlePriestRunToPlayer(const BattlePriestRunToPlayer&);
	BattlePriestRunToPlayer& operator=(const BattlePriestRunToPlayer&);

public:

	//this is a singleton
	static BattlePriestRunToPlayer* Instance();

	virtual void Enter(BattlePriestEntity* entity);

	virtual void Execute(BattlePriestEntity* entity);

	virtual void Exit(BattlePriestEntity* entity);

	virtual bool OnMessage(BattlePriestEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BattlePriestPatrol : public State<BattlePriestEntity>
{
private:

	BattlePriestPatrol() {}

	//copy ctor and assignment should be private
	BattlePriestPatrol(const BattlePriestPatrol&);
	BattlePriestPatrol& operator=(const BattlePriestPatrol&);

public:

	//this is a singleton
	static BattlePriestPatrol* Instance();

	virtual void Enter(BattlePriestEntity* entity);

	virtual void Execute(BattlePriestEntity* entity);

	virtual void Exit(BattlePriestEntity* entity);

	virtual bool OnMessage(BattlePriestEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class BattlePriestDie : public State<BattlePriestEntity>
{
private:

	BattlePriestDie() {}

	//copy ctor and assignment should be private
	BattlePriestDie(const BattlePriestDie&);
	BattlePriestDie& operator=(const BattlePriestDie&);

public:

	//this is a singleton
	static BattlePriestDie* Instance();

	virtual void Enter(BattlePriestEntity* entity);

	virtual void Execute(BattlePriestEntity* entity);

	virtual void Exit(BattlePriestEntity* entity);

	virtual bool OnMessage(BattlePriestEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
class BattlePriestRessurect : public State<BattlePriestEntity>
{
private:

	BattlePriestRessurect() {}

	//copy ctor and assignment should be private
	BattlePriestRessurect(const BattlePriestRessurect&);
	BattlePriestRessurect& operator=(const BattlePriestRessurect&);

public:

	//this is a singleton
	static BattlePriestRessurect* Instance();

	virtual void Enter(BattlePriestEntity* entity);

	virtual void Execute(BattlePriestEntity* entity);

	virtual void Exit(BattlePriestEntity* entity);

	virtual bool OnMessage(BattlePriestEntity* entity, const Message& msg);

};