#pragma once
#include "Game.h"
#include "Camera.h"
#include <vector>
class Shader;
class Layer;
class Label;
class Sprite;
class TileMap;
class HeroEntity;
class SkeletonEntity;
class GhostEntity;
class HellCatEntity;
class Group;
class BaseEnemy;
class Entity;
class EyeMonsterEntity;
class DemonEntity;
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
	
	//Debug
	void UpdatePlayerTiles();

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
	
	Camera myCamera;
	Group* myCursor;
	Group* tileGroup;
	Sprite* myMountain;
	Sprite* myGraveyard;

	//Entities
	HeroEntity* myPlayer;
	SkeletonEntity* mySkeleton;
	GhostEntity* myGhost;
	HellCatEntity* myHellCat;
	DemonEntity* myDemon;
	EyeMonsterEntity* myEyeMonster;
	std::vector<Entity*> myEntitites;
//	std::vector<SkeletonEntity*> mySkeletons;

	float lastX;
	float lastY;
	float myWidth;
	float myHeight;
	bool myMouseMovement;
	float lastPlayerX;
	float myScreenDirection;


private:
	//Debug stuff
	Layer * myDebugLayer;
	Group* myPlayerTile;
	Group* myPlayerTileTopLeft;
	Group* myPlayerTileTopRight;
	Group* myPlayerTileBottomLeft;
	Group* myPlayerTileBottomRight;
	Group* myPlayerTileMidRight;
	Group* myPlayerTileMidLeft;
};


