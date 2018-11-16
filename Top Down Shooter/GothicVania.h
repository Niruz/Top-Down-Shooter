#pragma once
#include "Game.h"
#include "Camera.h"
class Shader;
class Layer;
class Label;
class Sprite;
class TileMap;
class HeroEntity;
class Group;

class GothicVania : public Game
{
public:

	GothicVania()
	{

	}
	~GothicVania()
	{
		delete myMap;
		delete myTileLayer;
	}

	void Initialize() override;
	void Tick() override;
	void Update() override;
	void Render() override;

	void UpdatePlayer();

	void ProcessKeyBoard(int key, float deltaTime, int action) override;
	void ProcessMouse(double xpos, double ypos, bool movement) override;
private:

	Shader * myShader;
	Layer* myTileLayer;
	Layer* myBackgroundLayer;
	Layer* myGraveyardLayer;
	Layer* myMountainsLayer;
	//	Sprite* mySprite;
	Label* myFPSLabel;
	TileMap* myMap;
	HeroEntity* myPlayer;
	Camera myCamera;
	Group* myCursor;
	Group* tileGroup;
	Sprite* myMountain;
	Sprite* myGraveyard;

	float lastX;
	float lastY;
	float myWidth;
	float myHeight;
	bool myMouseMovement;



private:
	//Debug stuff
	Layer * myDebugLayer;
	Group* myPlayerTile;
};


