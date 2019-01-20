#pragma once
#include "State.h"

class AbominationEntity;
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class AbominationIdle : public State<AbominationEntity>
{
private:

	AbominationIdle() {}

	//copy ctor and assignment should be private
	AbominationIdle(const AbominationIdle&);
	AbominationIdle& operator=(const AbominationIdle&);

public:

	//this is a singleton
	static AbominationIdle* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class AbominationAttack : public State<AbominationEntity>
{
private:

	AbominationAttack() {}

	//copy ctor and assignment should be private
	AbominationAttack(const AbominationAttack&);
	AbominationAttack& operator=(const AbominationAttack&);

public:

	//this is a singleton
	static AbominationAttack* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class AbominationHurt : public State<AbominationEntity>
{
private:

	AbominationHurt() {}

	//copy ctor and assignment should be private
	AbominationHurt(const AbominationHurt&);
	AbominationHurt& operator=(const AbominationHurt&);

public:

	//this is a singleton
	static AbominationHurt* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class AbominationRunToPlayer : public State<AbominationEntity>
{
private:

	AbominationRunToPlayer() {}

	//copy ctor and assignment should be private
	AbominationRunToPlayer(const AbominationRunToPlayer&);
	AbominationRunToPlayer& operator=(const AbominationRunToPlayer&);

public:

	//this is a singleton
	static AbominationRunToPlayer* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class AbominationPatrol : public State<AbominationEntity>
{
private:

	AbominationPatrol() {}

	//copy ctor and assignment should be private
	AbominationPatrol(const AbominationPatrol&);
	AbominationPatrol& operator=(const AbominationPatrol&);

public:

	//this is a singleton
	static AbominationPatrol* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
//
//  Patrol state for the Ghost
//  
//------------------------------------------------------------------------
class AbominationDie : public State<AbominationEntity>
{
private:

	AbominationDie() {}

	//copy ctor and assignment should be private
	AbominationDie(const AbominationDie&);
	AbominationDie& operator=(const AbominationDie&);

public:

	//this is a singleton
	static AbominationDie* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};
//------------------------------------------------------------------------
class AbominationSpawnProjectile : public State<AbominationEntity>
{
private:

	AbominationSpawnProjectile() {}

	//copy ctor and assignment should be private
	AbominationSpawnProjectile(const AbominationSpawnProjectile&);
	AbominationSpawnProjectile& operator=(const AbominationSpawnProjectile&);

public:

	//this is a singleton
	static AbominationSpawnProjectile* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
class AbominationJump : public State<AbominationEntity>
{
private:

	AbominationJump() {}

	//copy ctor and assignment should be private
	AbominationJump(const AbominationJump&);
	AbominationJump& operator=(const AbominationJump&);

public:

	//this is a singleton
	static AbominationJump* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};

//------------------------------------------------------------------------
class AbominationFalling : public State<AbominationEntity>
{
private:

	AbominationFalling() {}

	//copy ctor and assignment should be private
	AbominationFalling(const AbominationFalling&);
	AbominationFalling& operator=(const AbominationFalling&);

public:

	//this is a singleton
	static AbominationFalling* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};


//------------------------------------------------------------------------
class AbominationWaitForPlayer : public State<AbominationEntity>
{
private:

	AbominationWaitForPlayer() {}

	//copy ctor and assignment should be private
	AbominationWaitForPlayer(const AbominationWaitForPlayer&);
	AbominationWaitForPlayer& operator=(const AbominationWaitForPlayer&);

public:

	//this is a singleton
	static AbominationWaitForPlayer* Instance();

	virtual void Enter(AbominationEntity* entity);

	virtual void Execute(AbominationEntity* entity);

	virtual void Exit(AbominationEntity* entity);

	virtual bool OnMessage(AbominationEntity* entity, const Message& msg);

};