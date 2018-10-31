#pragma once
#include "Game.h"
#include "Camera.h"
class Shader;
class Layer;
class Label;
class Sprite;
class TileMap;
class Player;
class Group;

class Shooter : public Game
{
public:

	Shooter()
	{

	}
	~Shooter()
	{
		delete myMap;
		delete myLayer;
	}

	void Initialize() override;
	void Tick() override;
	void Update() override;
	void Render() override;
	
	void UpdatePlayer();

	void ProcessKeyBoard(int direction, float deltaTime) override;
    void ProcessMouse(double xpos, double ypos, bool movement) override;
private:

	Shader * myShader;
	Layer* myLayer;
//	Sprite* mySprite;
	Label* myFPSLabel;
	TileMap* myMap;
	Player* myPlayer;
	Camera myCamera;
	Group* myCursor;
	Group* tileGroup;

	float lastX;
	float lastY;
	float myWidth;
	float myHeight;
	bool myMouseMovement;



private:
	//Debug stuff
	Layer* myDebugLayer;
	Group* myPlayerTile;
};



