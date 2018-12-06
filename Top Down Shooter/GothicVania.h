#pragma once
#include "Game.h"
#include "Camera.h"
#include <vector>
#include "CemetaryLevel.h"

#include "StateMachine.h"
class GothicVania : public Game
{
public:

	StateMachine<GothicVania>*  myStateMachine;
	StateMachine<GothicVania>*  GetFSM()const { return myStateMachine; }
	GothicVania()
	{

	}
	~GothicVania()
	{
		for (Level* level : myLevels)
			delete level;
	}

	void Initialize() override;
	void Tick() override;
	void Update() override;
	void Render() override;

	void ProcessKeyBoard(int key, float deltaTime, int action) override;
	void ProcessMouse(double xpos, double ypos, bool movement) override;

	void RenderLevel();
	void UpdateLevel();
	void RenderGameScreen();
	void UpdateGameScreen();

private:

	
public:

	int activeLevel;
	std::vector<Level*> myLevels;

	Layer* myGameScreenLayer;
	Label* myBossAnnouncer;
	Group* bossAnnouncerGroup;
	float myAlphaGameLayer;
	float myAlphaDirection;
	bool myGameScreenDone;
};


