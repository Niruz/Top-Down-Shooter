#pragma once
#include "Level.h"

class Shader;
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
class FireGolemEntity;
class GhoulEntity;
class UndeadWarriorEntity;
class ReaperEntity;
class ImpEntity;
class NecromancerEntity;
class CemetaryLevel : public Level
{
public:

	CemetaryLevel()
	{

	}
	virtual ~CemetaryLevel()
	{
		delete myMap;
		//delete myTileLayer;
	}
	void Initialize() override;
	void Tick(const unsigned int ups, const unsigned int fps) override;
	void Update() override;
	void Render() override;
	void DeInitialize() override;

	void ProcessKeyBoard(int key, float deltaTime, int action) override;
	void ProcessMouse(double xpos, double ypos, bool movement) override;


	void UpdatePlayer();
	void UpdatePlayerTiles();

public:
	Shader * myShader;
	//Tilelayer = grass layer
	Layer* myTileLayer;
	Layer* myBackgroundLayer;
	Layer* myGraveyardLayer;
	Layer* myMountainsLayer;
	Layer* myTreeLayer;
	Layer* myBushLayer;
	Layer* myStatueLayer;
	Layer* myOneWayPlatformLayer;
	Layer* myEnemyLayer;
	Layer* myPlayerLayer;

	//	Sprite* mySprite;
	Label* myFPSLabel;
	Label* myBossAnnouncer;
	Group* bossAnnouncerGroup;
	TileMap* myMap;

	Camera* myCamera;
	Group* myCursor;
	std::vector<Group*> myRenderGroups;
	Group* tileGroup;
	Sprite* myMountain;
	Sprite* myGraveyard;
	Sprite* myHPBar;
	Group* myGuiGroup;

	//Entities... Temporary for easier debugging
	HeroEntity* myPlayer;
	SkeletonEntity* mySkeleton;
	SkeletonEntity* mySkeleton2;
	SkeletonEntity* mySkeleton3;
	SkeletonEntity* mySkeleton4;
	GhostEntity* myGhost;
	GhostEntity* myGhost2;
	GhostEntity* myGhost3;
	HellCatEntity* myHellCat;
	HellCatEntity* myHellCat2;
	HellCatEntity* myHellCat3;
	HellCatEntity* myHellCat4;
	DemonEntity* myDemon;
	DemonEntity* myDemon2;
	DemonEntity* myDemon3;
	EyeMonsterEntity* myEyeMonster;
	EyeMonsterEntity* myEyeMonster2;
	EyeMonsterEntity* myEyeMonster3;
	EyeMonsterEntity* myEyeMonster4;
	EyeMonsterEntity* myEyeMonster5;
	EyeMonsterEntity* myEyeMonster6;
	EyeMonsterEntity* myEyeMonster7;

	//newer stuff
	FireGolemEntity* myFireGolem1;
	GhoulEntity* myGhoul1;
	UndeadWarriorEntity* myUDWar1;
	ReaperEntity* myReaperEntity;
	ImpEntity* myImpEntity;
	NecromancerEntity* myNecromancerEntity;
	std::vector<Entity*> myEntitites;
	//	std::vector<SkeletonEntity*> mySkeletons;

	float lastX;
	float lastY;
	float myWidth;
	float myHeight;
	bool myMouseMovement;
	float lastPlayerX;
	float myScreenDirection;
	float startScreenTime;
	float delayCutscene;
	float alphaStart;
	bool myBossBattle;
	bool cutSceneStarted;
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