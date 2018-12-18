#pragma once
#include "State.h"

class GothicVania;
//------------------------------------------------------------------------
//
//  Idle state for the hero
//  
//------------------------------------------------------------------------
class GothicVaniaIntroState : public State<GothicVania>
{
private:

	GothicVaniaIntroState() {}

	//copy ctor and assignment should be private
	GothicVaniaIntroState(const GothicVaniaIntroState&);
	GothicVaniaIntroState& operator=(const GothicVaniaIntroState&);

public:

	//this is a singleton
	static GothicVaniaIntroState* Instance();

	virtual void Enter(GothicVania* entity);

	virtual void Execute(GothicVania* entity);

	virtual void Exit(GothicVania* entity);

	virtual bool OnMessage(GothicVania* entity, const Message& msg);

	virtual bool HandleInput(GothicVania* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Idle state for the hero
//  
//------------------------------------------------------------------------
class GothicVaniaMenuState : public State<GothicVania>
{
private:

	GothicVaniaMenuState() {}

	//copy ctor and assignment should be private
	GothicVaniaMenuState(const GothicVaniaMenuState&);
	GothicVaniaMenuState& operator=(const GothicVaniaMenuState&);

public:

	//this is a singleton
	static GothicVaniaMenuState* Instance();

	virtual void Enter(GothicVania* entity);

	virtual void Execute(GothicVania* entity);

	virtual void Exit(GothicVania* entity);

	virtual bool OnMessage(GothicVania* entity, const Message& msg);

	virtual bool HandleInput(GothicVania* entity, int key, int action);
};
//------------------------------------------------------------------------
//
//  Idle state for the hero
//  
//------------------------------------------------------------------------
class GothicVaniaPlayState : public State<GothicVania>
{
private:

	GothicVaniaPlayState() {}

	//copy ctor and assignment should be private
	GothicVaniaPlayState(const GothicVaniaPlayState&);
	GothicVaniaPlayState& operator=(const GothicVaniaPlayState&);

public:

	//this is a singleton
	static GothicVaniaPlayState* Instance();

	virtual void Enter(GothicVania* entity);

	virtual void Execute(GothicVania* entity);

	virtual void Exit(GothicVania* entity);

	virtual bool OnMessage(GothicVania* entity, const Message& msg);

	virtual bool HandleInput(GothicVania* entity, int key, int action);

};