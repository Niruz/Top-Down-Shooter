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
	Sprite* myHPBar;
	Group* myGuiGroup;

	//Entities
	HeroEntity* myPlayer;
	SkeletonEntity* mySkeleton;
	GhostEntity* myGhost;
	GhostEntity* myGhost2;
	GhostEntity* myGhost3;
	HellCatEntity* myHellCat;
	DemonEntity* myDemon;
	DemonEntity* myDemon2;
	DemonEntity* myDemon3;
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

	bool myBossBattle;
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


