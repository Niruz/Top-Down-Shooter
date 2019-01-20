#pragma once
#include "Level.h"

class HeroEntity;
class Sprite;
class Label;
class TileMap;
class EffectsGroup;
class CellarLevel : public Level
{
public:

	CellarLevel(const std::string& name)
		: Level(name)
	{

	}
	virtual ~CellarLevel();

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

public:

	Shader * myShader;
	Layer* myTileLayer;
	Label* myFPSLabel;
	TileMap* myMap;

	Camera* myCamera;

	Group * tileGroup;
	Group * propGroup;
	Group * propGroupFront;
	Group * playerGroup;
	Group * myEnemyGroup;
	EffectsGroup * effectsGroup;
	EffectsGroup * effectsGroupBack;

	Sprite* myMoonBackground;
	Sprite* myGraveyardBackground;

	HeroEntity* myPlayer;
	std::vector<Entity*> myEntitites;

	float lastX;
	float lastY;
	float myWidth;
	float myHeight;
	bool myMouseMovement;
	float lastPlayerX;
	float myScreenDirection;

	bool myBossBattle = false;

	float myMapWidth;
	float myMapHeight;
	//Move these
	float myCameraMinBoundX;
	float myCameraMaxBoundX;

	bool levelFinished = false;

private:

};