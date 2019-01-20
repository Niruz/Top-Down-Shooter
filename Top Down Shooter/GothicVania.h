#pragma once
#include "Game.h"
#include "Camera.h"
#include <vector>
#include "CemetaryLevel.h"

#include "StateMachine.h"

class SplashScreen;
class MenuScreen;
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
		delete myStateMachine;
		delete mySplashScreen;
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
	void RenderMenuScreen();
	void UpdateMenuScreen();

private:

	
public:

	int activeLevel;
	std::vector<Level*> myLevels;
	bool myRenderingSplashScreen;
	bool myRenderingMenuScreen;
	SplashScreen* mySplashScreen;
	MenuScreen* myMenuScreen;
};


