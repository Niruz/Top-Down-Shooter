#pragma once

#include "State.h"
#include "Miner.h"
#include "Vampire.h"
class EnterMineAndDigForNugget : public State<Miner>
{
private:

	EnterMineAndDigForNugget() {}

	//copy ctor and assignment should be private
	EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
	EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);

public:

	//this is a singleton
	static EnterMineAndDigForNugget* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner);

	virtual bool OnMessage(Miner* agent, const Message& msg);

};

class EnterMineAndDigForVampire : public State<Vampire>
{
private:

	EnterMineAndDigForVampire() {}

	//copy ctor and assignment should be private
	EnterMineAndDigForVampire(const EnterMineAndDigForVampire&);
	EnterMineAndDigForVampire& operator=(const EnterMineAndDigForVampire&);

public:

	//this is a singleton
	static EnterMineAndDigForVampire* Instance();

	virtual void Enter(Vampire* miner);

	virtual void Execute(Vampire* miner);

	virtual void Exit(Vampire* miner);

	virtual bool OnMessage(Vampire* agent, const Message& msg);

};