#pragma once
#include "Entity.h"
#include "StateMachine.h"

class Miner : public Entity
{

	Miner(int id)
		:Entity(id)
	{

	};
	~Miner() {}

	virtual void update();
	virtual bool handleMessage(const Message& msg);
	//an instance of the state machine class
	StateMachine<Miner>*  mStateMachine;
};