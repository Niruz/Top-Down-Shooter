#pragma once
#include "Level.h"

class HeroEntity;
class Sprite;
class Label;
class TileMap;
class BridgeLevel : public Level
{
public:

	BridgeLevel(const std::string& name)
		: Level(name)
	{

	}
	virtual ~BridgeLevel();

	void Initialize() override;
	void Tick(const unsigned int ups, const unsigned int fps) override;
	void Update() override;
	void Render() override;
	void DeInitialize() override;

	void ProcessKeyBoard(int key, float deltaTime, int action) override;
	void ProcessMouse(double xpos, double ypos, bool movement) override;

	void AddEntity(Entity* entity) override;
	void SpawnEntity(const std::string& type, const glm::vec3&  inpos, const glm::vec3& indir, int heading = 1) override;
	void RemoveEntity(Entity* entity) override;
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
	Layer* myEffectsLayer;

	//	Sprite* mySprite;
	Label* myFPSLabel;
	Label* myBossAnnouncer;
	Label* myEvilVanquished;
	Group* bossAnnouncerGroup;
	TileMap* myMap;

	Camera* myCamera;
	Group* myCursor;

	Group* tileGroup;
	Group* treeGroup;
	Group * bushGroup;
	Group * statueGroup;
	Group* onewayGroup;
	Group* enemyGroup;
	Group* effectsGroup;
	Group * playerGroup;
	Sprite* myMountain;
	Sprite* myGraveyard;
	Sprite* myHPBar;
	Group* myGuiGroup;

	//Entities... Temporary for easier debugging
	HeroEntity* myPlayer;
	std::vector<Entity*> myEntitites;
	//	std::vector<SkeletonEntity*> mySkeletons;

	std::vector<Group*> myPlayerTileGroups;

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
	bool myBossDead;

	float startScreenTime2;
	float delayCutscene2;
	bool cutSceneStarted2;

	bool levelFinished = false;
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