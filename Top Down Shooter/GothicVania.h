#pragma once
#include "Game.h"
#include "Camera.h"
#include <vector>
#include "CemetaryLevel.h"

class GothicVania : public Game
{
public:

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
private:

	
private:

	int activeLevel;
	std::vector<Level*> myLevels;
};


