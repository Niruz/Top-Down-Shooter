#pragma once

#include "Entity.h"
#include "StateMachine.h"

class Vampire : public Entity
{
public:

	Vampire(int id)
		:Entity(id)
	{

	};
	~Vampire(){}

	virtual void update();
	virtual bool handleMessage(const Message& msg);

private:

	StateMachine<Vampire>*  mStateMachine;
};