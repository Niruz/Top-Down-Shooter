#pragma once
#include "Level.h"

class HeroEntity;
class Sprite;
class Label;
class TileMap;
class DungeonLevel : public Level
{
public:

	DungeonLevel(const std::string& name)
		: Level(name)
	{

	}
	virtual ~DungeonLevel();

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
	Group * bigblockGroup;
	Group * propGroup;
	Group * playerGroup;

	Sprite* myDungeonBackground;
	Sprite* myPillarBackground;

	HeroEntity* myPlayer;
	std::vector<Entity*> myEntitites;

	float lastX;
	float lastY;
	float myWidth;
	float myHeight;
	bool myMouseMovement;
	float lastPlayerX;
	float myScreenDirection;

	bool levelFinished = false;
private:

};