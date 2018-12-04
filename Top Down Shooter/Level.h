#pragma once

#include "Camera.h"
#include "Layer.h"


class Level
{
public:
	Level() {};
	virtual ~Level() 
	{
		for (Layer* layer : myLayers)
			delete layer;
	};

	virtual void Initialize() = 0;
	virtual void Tick(const unsigned int ups, const unsigned int fps) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void DeInitialize() = 0;

	virtual void ProcessKeyBoard(int key, float deltaTime, int action) = 0;
	virtual void ProcessMouse(double xpos, double ypos, bool movement) = 0;

	Camera* myCamera;
	std::vector<Layer*> myLayers;

};
