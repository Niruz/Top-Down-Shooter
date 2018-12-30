#include "SimpleTimer.h"
#include "GraveyardLevel.h"
#include "ShaderManager.h"
#include "Layer.h"
#include "Label.h"
#include "Sprite.h"
#include "BatchRenderer.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Group.h"
#include "TileMap.h"
#include "HeroEntity.h"
#include <iostream>
#include "glfw3.h"
#include "SkeletonEntity.h"
#include "GhostEntity.h"
#include "HellCatEntity.h"
#include "Entity.h"
#include "EyeMonsterEntity.h"
#include "DemonEntity.h"
#include "AnimatedSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "EntityManager.h"
#include "Entity.h"
#include "FireGolemEntity.h"
#include "GhoulEntity.h"
#include "UndeadWarriorEntity.h"
#include "ReaperEntity.h"
#include "ImpEntity.h"
#include "NecromancerEntity.h"
#include "CollisionManager.h"
#include "BaseProjectileEntity.h"
#include "NecromancerProjectile.h"
#include "ImpProjectile.h"
#include "AdventurerProjectile.h"
#include "AdventurerProjectileArrow.h"
#include "CollisionManager.h"
#include "Effect.h"
#include "HitEffectSprite.h"
#include "DynamicLayer.h"
#include "PotionPickup.h"
#include "PotionSprite.h"
#include "PickupDestroyedSprite.h"
#include "BloodEffectSprite.h"
#include "EnemyHitEffectSprite.h"
#include "SwordHitEffectSprite.h"
#include "AdventurerSlideEffectSprite.h"
#include "AdventurerDropKickEffectSprite.h"
void GraveyardLevel::Initialize()
{
	lastX = 640.0f;
	lastY = 360.0f;
	myHeight = 720.0f;
	myWidth = 1280.0f;
	myMouseMovement = false;

	glm::mat4 ortho = glm::ortho(-320.0f - 64, 320.0f + 64, -180.0f - 36, 180.0f + 36, -100.0f, 100.0f);
	myCamera = new Camera(666, "Camera1");
	myCamera->setScreenPosition(glm::vec2(lastX, lastY));
	myCamera->setProjectionMatrix(ortho);
	myCamera->setWidth(myWidth);
	myCamera->setHeight(myHeight);
	EntityMan->registerEntity(myCamera);

	myShader = ShaderMan->getShader(SIMPLE_GRAVEYARD_SHADER);

	myTileLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f - 64, 320.0f + 64, -180.0f - 36, 180.0f + 36, -100.0f, 100.0f));

	//Moon
	myMoonBackground = new Sprite(glm::vec4(0, 0, -99.0f, 1), glm::vec2(768.0f, 432.0f), TextureMan->GetTexture("moonbackground"));
	myTileLayer->Add(myMoonBackground);
	//Mountain
	myMountainBackground = new Sprite(glm::vec4(0, -108, -98.0f, 1), glm::vec2(768.0f, 432.0f), TextureMan->GetTexture("mountains"));
	myMountainBackground->setUVSpecialized(glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(2, 1), glm::vec2(2, 0));
	myTileLayer->Add(myMountainBackground);
	//Background
	myGraveyardBackground = new Sprite(glm::vec4(0, -108, -97.0f, 1), glm::vec2(768.0f, 216.0f), TextureMan->GetTexture("graveyard"));
	myTileLayer->Add(myGraveyardBackground);


	myPlayer = new HeroEntity(0, "Player");
	myNumberOfEntities = 26;
	myEntitites.push_back(myPlayer);
	for (Entity* entity : myEntitites)
	{
		EntityMan->registerEntity(entity);
	}

	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(260, 160, 0.8)));
	myFPSLabel = new Label("", glm::vec4(-55, -10, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(myFPSLabel);

	myTileLayer->Add(fpsGroup);









//	myMap = new TileMap("Levels/dungeon.level", glm::vec2(-320, 3488), glm::vec2(160, -288), glm::vec2(0, 119), glm::vec2(0, 14));
	//myMap = new TileMap("Levels/cemetary.tmx", "Tilesets/cemetarytileset.tsx");
	//myMap = new TileMap("Levels/cemetary.tmx", "CemetaryTileset");
	myMap = new TileMap("CemetaryTileLayer", "CemetaryTileset");
	myMap->printMap();

	std::vector<Tile*> myPath3;
	myMap->GetPath(1, 1, 18, 10, myPath3);

	myMap->printPath(myPath3);
	myPlayer->mPosition.x = myMap->GetPlayerStartTile()->myWorldPosition.x;
	myPlayer->mPosition.y = myMap->GetPlayerStartTile()->myWorldPosition.y;
	myPlayer->myAABB->myOrigin = glm::vec2(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->SetPlayerTile2(myPlayer->myAABB);
	std::vector<Tile*> map = myMap->GetMap();

	propGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.2)), -10.2);
	tileGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -9.2)), -9.2);
	bigblockGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -9.0)), -9.0);

	myRenderGroups.push_back(propGroup);
	myRenderGroups.push_back(tileGroup);
	myRenderGroups.push_back(bigblockGroup);


	for(int i = 0 ; i < map.size(); i++)
	{
		if(map[i]->myTileType != "-1")
		{
			tileGroup->Add(new Sprite(glm::vec4(map[i]->myWorldPosition.x, map[i]->myWorldPosition.y, 0.0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("cemetarytileset"),std::stoi(map[i]->myTileType)));
		//	tileGroup->Add(new Sprite(glm::vec4(map[i]->myWorldPosition.x, map[i]->myWorldPosition.y, 0.0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floatingsolid")));
		}
	}


	/*float startX = -32.0f * 10.0f;
	float startY = 32.0f * 6;
	srand(54);

	int floortype = 1;
	int rooftype = 1;
	for (int i = 0; i < map.size(); i++)
	{
		if (i % 122 == 0)
		{
			startY -= 32.0f;
			startX = -32.0f*10.0f;
		}

		if (i == 1799)
			int shitterooo = 5;

		if (map[i]->myIsBlockingFlag)
		{
			if (!(map[i]->myTileType == "o"))
			{
				if (map[i]->myTileType == "X")
				{
					tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(32.0f, 34.0f), TextureMan->GetTexture("dungeonfloor" + std::to_string(floortype))));
					floortype++;
					if (floortype > 4)
						floortype = 1;
					int grassType = (rand() % 6);
					if (grassType == 1)
						tileGroup->Add(new Sprite(glm::vec4(startX, startY + 31.0f, 0.0, 1), glm::vec2(32.0f, 34.0f), TextureMan->GetTexture("dungeongrass" + std::to_string(grassType))));
					else if (grassType == 2)
						tileGroup->Add(new Sprite(glm::vec4(startX, startY + 31.0f, 0.0, 1), glm::vec2(32.0f, 34.0f), TextureMan->GetTexture("dungeongrass" + std::to_string(grassType))));
					else if (grassType == 3)
						tileGroup->Add(new Sprite(glm::vec4(startX, startY + 31.0f, 0.0, 1), glm::vec2(32.0f, 34.0f), TextureMan->GetTexture("dungeongrass" + std::to_string(grassType))));
				}
				if (map[i]->myTileType == "x")
				{
					tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(32.0f, 34.0f), TextureMan->GetTexture("dungeonroof" + std::to_string(rooftype))));
					rooftype++;
					if (rooftype > 4)
						rooftype = 1;
				}
				if (map[i]->myTileType == "I")
				{
					bigblockGroup->Add(new Sprite(glm::vec4(startX, startY + 63, 0.0, 1), glm::vec2(105.0f, 160.0f), TextureMan->GetTexture("dungeonbigtile")));
					floortype++;
					if (floortype > 4)
						floortype = 1;
				}
			}
		}
		else
		{
			if (map[i]->myTileType == "S")
			{
				int cageType = (rand() % 4);
				cageType++; // 0-2 = 1-3 :)
				if (cageType == 1 || cageType == 2)
					propGroup->Add(new Sprite(glm::vec4(startX, startY + 7, 0.0, 1), glm::vec2(34.0f, 82.0f), TextureMan->GetTexture("dungeoncage" + std::to_string(cageType))));
				else
					propGroup->Add(new Sprite(glm::vec4(startX, startY - 16, 0.0, 1), glm::vec2(34.0f, 128.0f), TextureMan->GetTexture("dungeoncage" + std::to_string(3))));
			}
			if (map[i]->myTileType == "B")
			{
				int coffinType = (rand() % 3);
				coffinType++;
				if (coffinType == 1)
					propGroup->Add(new Sprite(glm::vec4(startX, startY - 1, 0.0, 1), glm::vec2(66.0f, 32.0f), TextureMan->GetTexture("dungeoncoffin" + std::to_string(coffinType))));
				else if (coffinType == 2)
					propGroup->Add(new Sprite(glm::vec4(startX, startY - 11, 0.0, 1), glm::vec2(66.0f, 22.0f), TextureMan->GetTexture("dungeoncoffin" + std::to_string(coffinType))));
				else
					propGroup->Add(new Sprite(glm::vec4(startX, startY - 5, 0.0, 1), glm::vec2(82.0f, 28.0f), TextureMan->GetTexture("dungeoncoffin" + std::to_string(coffinType))));
			}
		}
		startX += 32.0f;
	}*/
	myTileLayer->Add(propGroup);
	myTileLayer->Add(tileGroup);
	myTileLayer->Add(bigblockGroup);
	myTileLayer->Add(myPlayer->mySprite);

	lastPlayerX = myPlayer->mPosition.x;
	myScreenDirection = 0.0f;

	myLayers.push_back(myTileLayer);
	myPlayer->myTileMap = myMap;
}
GraveyardLevel::~GraveyardLevel()
{
	delete myMap;
	EntityMan->DeleteAllEntities();
}
void GraveyardLevel::UpdatePlayer()
{
	EntityMan->Update();
	CollisionMan->Update();
	MessageMan->dispatchDelayedMessages();

	myPlayer->UpdateTransformationMatrix(*myCamera);
	glm::vec2 mouseScreenWorld = myCamera->mouseScreenToWorld(glm::vec2(lastX, lastY));
	glm::mat4 tran = glm::mat4(1.0f);
	tran = glm::translate(tran, glm::vec3(mouseScreenWorld.x, mouseScreenWorld.y, 0.0f));

	for (Group* group : myRenderGroups)
	{
		glm::mat4 camTranslation = myCamera->mTranslationMatrix;
		group->UpdateXYAxis(glm::vec2(myCamera->mPosition.x, myCamera->mPosition.y));
	}

	myScreenDirection = 0.0f;
	if ((myPlayer->mPosition.x > 75.5f) && (myPlayer->mPosition.x < 3150.0f))
	{
		float newPlayerX = myPlayer->mPosition.x;
		if (lastPlayerX > newPlayerX)
			myScreenDirection = -1.0f;
		else if (lastPlayerX < newPlayerX)
			myScreenDirection = 1.0f;
		else
			myScreenDirection = 0.0f;

		lastPlayerX = newPlayerX;
	}
	myMountainBackground->increaseUVAlongX(myScreenDirection *0.001f);
	myGraveyardBackground->increaseUVAlongX(myScreenDirection *0.002f);
}
void GraveyardLevel::Tick(const unsigned int ups, const unsigned int fps)
{
	myFPSLabel->myText = std::to_string(fps) + " fps";
	std::cout << ups << " ups, " << fps << " fps" << std::endl;
}
void GraveyardLevel::Update()
{
	UpdatePlayer();
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->SetPlayerTile2(myPlayer->myAABB);
	//myCamera.setPosition(-myPlayer->mPosition);
	//if (myPlayer->mPosition.x > 75.5f && myPlayer->mPosition.x < 3155.0f && (!myBossBattle))
	if (myPlayer->mPosition.x > 75.5f && myPlayer->mPosition.x < 3155.0f)
		int hoho = 6;
		//myCamera->setPosition(glm::vec3(-myPlayer->mPosition.x, 32.0f, -myPlayer->mPosition.z));
		myCamera->setPosition(glm::vec3(-myPlayer->mPosition.x, 384, -myPlayer->mPosition.z));

	myCamera->Update();
}
void GraveyardLevel::Render()
{
	for (Layer* layer : myLayers)
		layer->Render();
}
void GraveyardLevel::DeInitialize()
{

}
void GraveyardLevel::ProcessKeyBoard(int key, float deltaTime, int action)
{
	myPlayer->processKeyBoard(key, deltaTime, action);
}
void GraveyardLevel::ProcessMouse(double xpos, double ypos, bool movement)
{
	myMouseMovement = movement;

	lastX = xpos;
	lastY = ypos;

	myCamera->setScreenPosition(glm::vec2(lastX, lastY));
}
void GraveyardLevel::AddEntity(Entity* entity)
{
	myEntitites.push_back(entity);
}

void GraveyardLevel::SpawnEntity(const std::string& type, const glm::vec3&  inpos, const glm::vec3& indir, int heading)
{

}
void GraveyardLevel::RemoveEntity(Entity* entity)
{
	if (dynamic_cast<BaseProjectileEntity*>(entity))
	{
		if ((dynamic_cast<BaseProjectileEntity*>(entity)->isHeroProjectile))
			CollisionMan->RemoveHeroProjectile((BaseProjectileEntity*)entity);
		else
			CollisionMan->RemoveProjectile((BaseProjectileEntity*)entity);
		EntityMan->removeEntity(entity);
	}
	else
	{
		CollisionMan->RemoveEntity((BaseEnemy*)entity);
		EntityMan->removeEntity(entity);
	}
}