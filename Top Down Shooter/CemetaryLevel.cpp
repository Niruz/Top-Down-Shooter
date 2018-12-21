#include "SimpleTimer.h"
#include "CemetaryLevel.h"
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
void CemetaryLevel::Initialize()
{
	lastX = 640.0f;
	lastY = 360.0f;
	myHeight = 720.0f;
	myWidth = 1280.0f;
	myMouseMovement = false;

	glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -10.0f, 10.0f);
	myCamera = new Camera(666, "Camera1");
	myCamera->setScreenPosition(glm::vec2(lastX, lastY));
	myCamera->setProjectionMatrix(ortho);
	myCamera->setWidth(myWidth);
	myCamera->setHeight(myHeight);
	EntityMan->registerEntity(myCamera);

	myShader = ShaderMan->getShader(SIMPLE_FORWARD_SHADER);

	



	myTileLayer           = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myTreeLayer           = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myBushLayer           = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myStatueLayer         = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myOneWayPlatformLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myEnemyLayer          = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myPlayerLayer         = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myEffectsLayerFront = new DynamicLayer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myEffectsLayerBack  = new DynamicLayer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myBackgroundLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_BACKGROUND1_SHADER), glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -10.0f, 10.0f));
	myGraveyardLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_BACKGROUND2_SHADER), glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -10.0f, 10.0f));
	myMountainsLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_BACKGROUND3_SHADER), glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -10.0f, 10.0f));

	myTestLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));

	myBackgroundLayer->Add(new Sprite(glm::vec4(0, 0, -9.90f, 1), glm::vec2(1.0f, 1.0f), TextureMan->GetTexture("moonbackground")/*, glm::vec2(0, 15)*/));

	myGraveyard = new Sprite(glm::vec4(0, -0.25f, -9.70f, 1), glm::vec2(1.0f, 0.5f), TextureMan->GetTexture("graveyard")/*, glm::vec2(0, 15)*/);
	myGraveyardLayer->Add(myGraveyard);
	//myGraveyardLayer->Add(new Sprite(glm::vec4(0, -0.25f, -0.7, 1), glm::vec2(1.0f, 0.5f), TextureMan->GetTexture("graveyard")/*, glm::vec2(0, 15)*/));


	myMountain = new Sprite(glm::vec4(0, -0.25, -9.80f, 1), glm::vec2(1.0f, 1.0f), TextureMan->GetTexture("mountains")/*, glm::vec2(0, 15)*/);
	myMountain->setUVSpecialized(glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(2, 1), glm::vec2(2, 0));
	myMountainsLayer->Add(myMountain);
	//myMountainsLayer->Add(new Sprite(glm::vec4(0, -0.25, -0.8, 1), glm::vec2(1.0f, 1.0f), TextureMan->GetTexture("mountains")/*, glm::vec2(0, 15)*/));
	myDebugLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f));

	myPlayer = new HeroEntity(0, "Player");
	/*	mySkeleton = new SkeletonEntity(1, "Skeleton1", glm::vec3(64.0f, -152.0f, 0.1f), glm::vec3(224.0f, -152.0f, 0.1f));
	myGhost = new GhostEntity(2, "Ghost1", glm::vec3(-128.0f, -96.0f, 0.1f), glm::vec3(-128.0f, 32.0f, 0.1f));
	myHellCat = new HellCatEntity(3, "HellCat1", glm::vec3(640.0f, -150.0f, 0.1f), glm::vec3(864.0f, -150.0f, 0.1f));
	myEyeMonster = new EyeMonsterEntity(4, "EyeMonster1", glm::vec3(96.0f, -96.0f, 0.09f), glm::vec3(256.0f, -96.0f, 0.09f));
	myDemon = new DemonEntity(5, "Demon1", glm::vec3(128, -96 - 15, 0.1f), glm::vec3(128.0f, -32.0f, 0.1f));
	myGhost2 = new GhostEntity(6, "Ghost2", glm::vec3(1328.0f, -160.0f, 0.1f), glm::vec3(1328.0f, -32.0f, 0.1f));
	myGhost3 = new GhostEntity(7, "Ghost3", glm::vec3(2624.0f, -128.0f, 0.1f), glm::vec3(2624.0f, -32.0f, 0.1f));*/
	myDemon2 = new DemonEntity(8, "Demon2", glm::vec3(3008.0f, 224 - 15, 0.0f), glm::vec3(3008.0f, -32.0f, 0.0f));
	myDemon3 = new DemonEntity(9, "Demon3", glm::vec3(3264.0f, 224 - 15, 0.01f), glm::vec3(3264.0f, -32.0f, 0.01f));/*
																												  mySkeleton2 = new SkeletonEntity(10, "Skeleton2", glm::vec3(0.0f, -152.0f, 0.1f), glm::vec3(-192.0f, -152.0f, 0.1f));
																												  mySkeleton3 = new SkeletonEntity(11, "Skeleton3", glm::vec3(256.0f, -152.0f, 0.1f), glm::vec3(416.0f, -152.0f, 0.1f));
																												  mySkeleton4 = new SkeletonEntity(12, "Skeleton4", glm::vec3(448.0f, -152.0f, 0.1f), glm::vec3(608.0f, -152.0f, 0.1f));
																												  myEyeMonster2 = new EyeMonsterEntity(13, "EyeMonster2", glm::vec3(960.0f, -150.0f, 0.09f), glm::vec3(1120.0f, -150.0f, 0.9f));
																												  myEyeMonster3 = new EyeMonsterEntity(14, "EyeMonster3", glm::vec3(864.0f, -96.0f, 0.09f), glm::vec3(640.0f, -96.0f, 0.9f));
																												  myHellCat2 = new HellCatEntity(15, "HellCat2", glm::vec3(1456.0f, -150.0f, 0.1f), glm::vec3(1616.0f, -150.0f, 0.1f));
																												  myHellCat3 = new HellCatEntity(16, "HellCat3", glm::vec3(1840.0f, -150.0f, 0.1f), glm::vec3(1680.0f, -150.0f, 0.101f));
																												  myEyeMonster4 = new EyeMonsterEntity(17, "EyeMonster4", glm::vec3(1424.0f, -96.0f, 0.09f), glm::vec3(1872.0f, -96.0f, 0.9f));
																												  myEyeMonster5 = new EyeMonsterEntity(18, "EyeMonster5", glm::vec3(2064.0f, -160.0f, 0.09f), glm::vec3(2448.0f, -160.0f, 0.9f));
																												  myEyeMonster6 = new EyeMonsterEntity(19, "EyeMonster6", glm::vec3(2064.0f, -128.0f, 0.091f), glm::vec3(2480.0f, -128.0f, 0.91));
																												  myEyeMonster7 = new EyeMonsterEntity(20, "EyeMonster7", glm::vec3(2064.0f, -96.0f, 0.092f), glm::vec3(2512.0f, -96.0f, 0.92));*/
	myFireGolem1 = new FireGolemEntity(21, "FireGolem1", glm::vec3(-320.0f, -125.0, 0.02f), glm::vec3(-32.0f, -125.0, 0.02f));
	myGhoul1 = new GhoulEntity(22, "Ghoul1", glm::vec3(640.0f, -160.0f, 0.03f), glm::vec3(864.0f, -150.0f, 0.03f));
	//myUDWar1 = new UndeadWarriorEntity(23, "UndeadWarrior1", glm::vec3(64.0f, -152.0f, 0.04f), glm::vec3(224.0f, -152.0f, 0.04f));
	myUDWar1 = new UndeadWarriorEntity(23, "UndeadWarrior1", glm::vec3(1456.0f, -152.0f, 0.04f), glm::vec3(1616.0f, -152.0f, 0.04f));
	myReaperEntity = new ReaperEntity(24, "Reaper1", glm::vec3(256.0f, -152.0f, 0.05f), glm::vec3(416.0f, -152.0f, 0.05f));
	//myImpEntity = new ImpEntity(25, "Imp1", glm::vec3(960.0f, -150.0f, 0.06f), glm::vec3(1120.0f, -150.0f, 0.06f));
	myImpEntity = new ImpEntity(25, "Imp1", glm::vec3(960.0f+320.0f-64.0f, -96, 0.06f), glm::vec3(1120.0f+320.0f, -96, 0.06f));
	myNecromancerEntity = new NecromancerEntity(26, "Necromancer1", glm::vec3(1456.0f, -120.0f, 0.07f), glm::vec3(1840.0f, -120.0f, 0.07f));
	myNumberOfEntities = 26;

	myUDWar1->SetMaster(myNecromancerEntity);

	myEntitites.push_back(myPlayer);
	/*myEntitites.push_back(mySkeleton);
	myEntitites.push_back(myGhost);
	myEntitites.push_back(myGhost2);
	myEntitites.push_back(myGhost3);
	myEntitites.push_back(myHellCat);
	myEntitites.push_back(myEyeMonster);
	myEntitites.push_back(myDemon);*/
	myEntitites.push_back(myDemon2);
	myEntitites.push_back(myDemon3);/*
									myEntitites.push_back(mySkeleton2);
									myEntitites.push_back(mySkeleton3);
									myEntitites.push_back(mySkeleton4);
									myEntitites.push_back(myEyeMonster2);
									myEntitites.push_back(myEyeMonster3);
									myEntitites.push_back(myHellCat2);
									myEntitites.push_back(myHellCat3);
									myEntitites.push_back(myEyeMonster4);
									myEntitites.push_back(myEyeMonster5);
									myEntitites.push_back(myEyeMonster6);
									myEntitites.push_back(myEyeMonster7);*/
	myEntitites.push_back(myFireGolem1);
	myEntitites.push_back(myGhoul1);
	myEntitites.push_back(myUDWar1);
	myEntitites.push_back(myReaperEntity);
	myEntitites.push_back(myImpEntity);
	myEntitites.push_back(myNecromancerEntity);

	for (Entity* entity : myEntitites)
	{
		EntityMan->registerEntity(entity);
	}

	myDemon2->myAnimatedSprite->SetHeading(Heading::LEFTFACING);

	//Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-580, 340, 0.8)));
	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(260, 160, 0.8)));
	myFPSLabel = new Label("", glm::vec4(-55, -10, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	//myFPSLabel = new Label("", glm::vec4(0, 0, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(myFPSLabel);

	bossAnnouncerGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.8f)));
	myBossAnnouncer = new Label("Fire & Fury", glm::vec4(-195.0f, 2000.0f, 0, 1), "Adventurer48", glm::vec4(1, 1, 1, 1));
	myEvilVanquished = new Label("Evil Vanquished", glm::vec4(-195.0f, 2000.0f, 0, 1), "Adventurer48", glm::vec4(1, 1, 1, 1));
	myEvilVanquished->SetColor(glm::vec4(1, 1, 1, 0));
	myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, 0));
	//bossAnnouncerGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(320.0f, 180.0f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	bossAnnouncerGroup->Add(myBossAnnouncer);
	bossAnnouncerGroup->Add(myEvilVanquished);

	myCursor = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.8)));
	myCursor->Add(new Sprite(glm::vec4(0, 0, 0.3, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("cursor")/*, glm::vec2(0, 15)*/));

	myTileLayer->Add(fpsGroup);
	//myEffectsLayer->Add(fpsGroup);
	//myTileLayer->Add(myCursor);

	myMap = new TileMap("Levels/test3.level", glm::vec2(-320, 3488), glm::vec2(160, -288), glm::vec2(0, 119), glm::vec2(0, 14));

	myMap->printMap();

	std::vector<Tile*> myPath3;
	myMap->GetPath(1, 1, 18, 10, myPath3);

	myMap->printPath(myPath3);
	myPlayer->mPosition.x = myMap->GetPlayerRespawnTile()->myWorldPosition.x;
	myPlayer->mPosition.y = myMap->GetPlayerRespawnTile()->myWorldPosition.y;
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->SetPlayerTile2(myPlayer->myAABB);
	std::vector<Tile*> map = myMap->GetMap();
	
	//Tilegroup = grass group

	treeGroup = new Group(glm::translate(glm::mat4(1.0f),   glm::vec3(0.0f, 0.0f, -9.6)), -9.6);
	bushGroup = new Group(glm::translate(glm::mat4(1.0f),   glm::vec3(0.0f, 0.0f, -9.5)), -9.5);
	statueGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -9.4)), -9.4);
	onewayGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -9.3)), -9.3);
	tileGroup          = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -9.2)), -9.2);
	enemyGroup = new Group(glm::translate(glm::mat4(1.0f),  glm::vec3(0.0f, 0.0f, -5.0)), -5.0);
	effectsGroupBack = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0)), -3.0);
	playerGroup = new Group(glm::translate(glm::mat4(1.0f),  glm::vec3(0.0f, 0.0f,  0.0)), 0.0);
	effectsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f,  5.0f)), 5.0f);
	
	myRenderGroups.push_back(tileGroup);
	myRenderGroups.push_back(treeGroup);
	myRenderGroups.push_back(bushGroup);
	myRenderGroups.push_back(statueGroup);
	myRenderGroups.push_back(onewayGroup);
	myRenderGroups.push_back(enemyGroup);
	myRenderGroups.push_back(effectsGroupBack);
	myRenderGroups.push_back(playerGroup);
	myRenderGroups.push_back(effectsGroup);

	
	myTestLayer->Add(treeGroup);
	myTestLayer->Add(bushGroup);
	myTestLayer->Add(statueGroup);
	myTestLayer->Add(onewayGroup);
	myTestLayer->Add(tileGroup);
	myTestLayer->Add(enemyGroup);
	myTestLayer->Add(effectsGroupBack);
	myTestLayer->Add(myPlayer->mySprite);
	myTestLayer->Add(playerGroup);
	myTestLayer->Add(effectsGroup);
		/*	myTileLayer           = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myTreeLayer           = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myBushLayer           = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myStatueLayer         = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myOneWayPlatformLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myEnemyLayer          = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myPlayerLayer         = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));*/
	float startX = -32.0f * 10.0f;
	float startY = 32.0f * 6;
	srand(54);

	int grassType = 1;
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
			//Should be 32 but 30 looks cool

			if (map[i]->myIsSpikedFloor)
			{
				onewayGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("spikes")));
			}
			else if (map[i]->myIsPillar)
			{
				std::string pillar = (rand() % 2) == 0 ? "pillar1" : "pillar2";
				onewayGroup->Add(new Sprite(glm::vec4(startX, startY + 32.5, 0.0, 1), glm::vec2(32.0f, 96.0f), TextureMan->GetTexture(pillar)));
				
			}
			else if (map[i]->myIsOneWayTile)
			{
				
				if (map[i]->myTileType == "F")
				{
					onewayGroup->Add(new Sprite(glm::vec4(startX, startY + 5, 0.0, 1), glm::vec2(32.0f, 41), TextureMan->GetTexture("floatinggrass")));
					
				}
			}
			else
			{
				if (!(map[i]->myTileType == "o"))
				{
					if(map[i]->myTileType == "X")
						tileGroup->Add(new Sprite(glm::vec4(startX, startY + 5, 0.0, 1), glm::vec2(32.0f, 41), grassType > 0 ? TextureMan->GetTexture("grass") : TextureMan->GetTexture("grass2")));
					else if(map[i]->myTileType == "x")
					{
						tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(32.0f, 32), grassType > 0 ? TextureMan->GetTexture("grass_1") : TextureMan->GetTexture("grass2_1")));
					}
				}
					
				grassType *= -1;
				//	tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.011, 1), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f,0.0f,1.0f,0.5f)));
			}
			
		}
		else
		{
			if (map[i]->myIsSpikedFloor)
			{
				if (map[i]->myTileType == "y")
					onewayGroup->Add(new Sprite(glm::vec4(startX, startY + 31-8, 0.0, 1), glm::vec2(32.0f, 94.0f), TextureMan->GetTexture("spikedpillar")));
				else if (map[i]->myTileType == "Y")
					onewayGroup->Add(new Sprite(glm::vec4(startX, startY-7, 0.0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("spikes")));
				else if (map[i]->myTileType == "z")
				{
					onewayGroup->Add(new Sprite(glm::vec4(startX, startY + 0.5f, -0.01, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floatingsolid2")));
					onewayGroup->Add(new Sprite(glm::vec4(startX, startY - 7, 0.0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("spikes")));
				}
					
			}
			else if (map[i]->myTileType == "f")
			{
				if(map[i]->myTileType == "f")
					onewayGroup->Add(new Sprite(glm::vec4(startX, startY + 0.5f, -0.01, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floatingsolid2")));
			}
			else if (map[i]->myTileType == "e")
			{
				onewayGroup->Add(new Sprite(glm::vec4(startX, startY - 21.0f, 0.0, 1), glm::vec2(32.0f, 64.0f), TextureMan->GetTexture("floatingleftgrass")));
				
			}
			else if (map[i]->myTileType == "E")
			{
				onewayGroup->Add(new Sprite(glm::vec4(startX, startY - 19.0f, 0.0, 1), glm::vec2(32.0f, 64.0f), TextureMan->GetTexture("floatingrightgrass")));
				
			}
			else if (map[i]->myTileType == "1")
			{
				statueGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(27.0f, 39.0f), TextureMan->GetTexture("stone1")));
			
			}
			else if (map[i]->myTileType == "2")
			{
				statueGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(27.0f, 40.0f), TextureMan->GetTexture("stone2")));
			
			}
			else if (map[i]->myTileType == "3")
			{
				statueGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(27.0f, 33.0f), TextureMan->GetTexture("stone3")));
				
			}
			else if (map[i]->myTileType == "4")
			{
				statueGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(19.0f, 38.0f), TextureMan->GetTexture("stone4")));
				
			}
			else if (map[i]->myTileType == "S")
			{
				statueGroup->Add(new Sprite(glm::vec4(startX, startY + 20.0f, 0.0, 1), glm::vec2(63.0f, 75.0f), TextureMan->GetTexture("statue")));
				
			}
			else if (map[i]->myTileType == "b")
			{
				bushGroup->Add(new Sprite(glm::vec4(startX, startY, 0.0, 1), glm::vec2(34.0f, 29.0f), TextureMan->GetTexture("bushsmall")));
				
			}
			else if (map[i]->myTileType == "B")
			{
				bushGroup->Add(new Sprite(glm::vec4(startX, startY + 10, 0.0, 1), glm::vec2(76.0f, 65.0f), TextureMan->GetTexture("bushlarge")));
				
			}
			else if (map[i]->myTileType == "T")
			{
				treeGroup->Add(new Sprite(glm::vec4(startX, startY + 40.0f, 0.0, 1), glm::vec2(166.0f, 117.0f), TextureMan->GetTexture("tree1")));
			}
			else if (map[i]->myTileType == "t")
			{
				treeGroup->Add(new Sprite(glm::vec4(startX, startY + 60.0f, 0.0, 1), glm::vec2(176.0f, 171.0f), TextureMan->GetTexture("tree3")));
			}
		}
		startX += 32.0f;
	}
	myTileLayer->Add(tileGroup);
	myTreeLayer->Add(treeGroup);
	myBushLayer->Add(bushGroup);
	myStatueLayer->Add(statueGroup);
	myOneWayPlatformLayer->Add(onewayGroup);

	//Temp
	myGuiGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-260, 160, 0.8)));
	myHPBar = new Sprite(glm::vec4(0.0f, 0.0f, 0.2f, 1.0f), glm::vec2(85, 25), TextureMan->GetTexture("hpbar"));
	myGuiGroup->Add(myHPBar);
	myPlayerLayer->Add(myGuiGroup);

	//Debug
	myPlayerTile = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.02)));
	myPlayerTile->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floor2")/*, glm::vec2(0, 15)*/));
	myPlayerTileTopLeft = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.2)));
	myPlayerTileTopLeft->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.5f)));
	myPlayerTileTopRight = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.2)));
	myPlayerTileTopRight->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.5f)));
	myPlayerTileBottomLeft = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.2)));
	myPlayerTileBottomLeft->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 1.0f, 1.0f, 0.5f)));
	myPlayerTileBottomRight = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.2)));
	myPlayerTileBottomRight->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), glm::vec4(1.0f, 1.0f, 0.0f, 0.5f)));
	myPlayerTileMidRight = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.2)));
	myPlayerTileMidRight->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), glm::vec4(0.4f, 1.0f, 0.0f, 0.5f)));
	myPlayerTileMidLeft = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.2)));
	myPlayerTileMidLeft->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), glm::vec4(1.0f, 1.0f, 0.4f, 0.5f)));

	myPlayerTileGroups.push_back(myPlayerTile);
	myPlayerTileGroups.push_back(myPlayerTileTopLeft);
	myPlayerTileGroups.push_back(myPlayerTileTopRight);
	myPlayerTileGroups.push_back(myPlayerTileBottomLeft);
	myPlayerTileGroups.push_back(myPlayerTileBottomRight);
	myPlayerTileGroups.push_back(myPlayerTileMidRight);
	myPlayerTileGroups.push_back(myPlayerTileMidLeft);

	/*tileGroup->Add(myPlayerTile);
	tileGroup->Add(myPlayerTileTopLeft);
	tileGroup->Add(myPlayerTileTopRight);
	tileGroup->Add(myPlayerTileBottomLeft);
	tileGroup->Add(myPlayerTileTopLeft);
	tileGroup->Add(myPlayerTileBottomRight);
	tileGroup->Add(myPlayerTileMidLeft);
	tileGroup->Add(myPlayerTileMidRight);*/
	/*	tileGroup->Add(myGhost->mySprite);
	tileGroup->Add(myGhost2->mySprite);
	tileGroup->Add(myGhost3->mySprite);
	tileGroup->Add(myHellCat->mySprite);
	tileGroup->Add(myEyeMonster->mySprite);
	tileGroup->Add(myDemon->mySprite);*/
	enemyGroup->Add(myDemon2->mySprite);
	enemyGroup->Add(myDemon3->mySprite);/*
									   tileGroup->Add(mySkeleton->mySprite);
									   tileGroup->Add(mySkeleton2->mySprite);
									   tileGroup->Add(mySkeleton3->mySprite);
									   tileGroup->Add(mySkeleton4->mySprite);
									   tileGroup->Add(myEyeMonster2->mySprite);
									   tileGroup->Add(myEyeMonster3->mySprite);
									   tileGroup->Add(myHellCat2->mySprite);
									   tileGroup->Add(myHellCat3->mySprite);
									   tileGroup->Add(myEyeMonster4->mySprite);
									   tileGroup->Add(myEyeMonster5->mySprite);
									   tileGroup->Add(myEyeMonster6->mySprite);
									   tileGroup->Add(myEyeMonster7->mySprite);*/
	enemyGroup->Add(myFireGolem1->mySprite);
	enemyGroup->Add(myGhoul1->mySprite);
	enemyGroup->Add(myUDWar1->mySprite);
	enemyGroup->Add(myReaperEntity->mySprite);
	enemyGroup->Add(myImpEntity->mySprite);
	enemyGroup->Add(myNecromancerEntity->mySprite);

	myEnemyLayer->Add(enemyGroup);

	//myTileLayer->Add(tileGroup);
	myPlayerLayer->Add(myPlayer->mySprite);
	myEffectsLayerFront->Add(effectsGroup);
	myEffectsLayerBack->Add(effectsGroupBack);
	//screen
	myPlayerLayer->Add(bossAnnouncerGroup);
	myPlayer->myTileMap = myMap;
	myDebugLayer->Add(myPlayerTile);
	lastPlayerX = myPlayer->mPosition.x;
	myScreenDirection = 0.0f;
	myBossBattle = false;
	cutSceneStarted = false;
	myBossDead = false;
	cutSceneStarted2 = false;
	myFireGolem1->myTileMap = myMap;
	myGhoul1->myTileMap = myMap;
	myUDWar1->myTileMap = myMap;
	myReaperEntity->myTileMap = myMap;
	myImpEntity->myTileMap = myMap;
	myNecromancerEntity->myTileMap = myMap;


	myTestLayer->Add(fpsGroup);
	//playerGroup->Add(myPlayer->mySprite);
	
	myTestLayer->Add(bossAnnouncerGroup);

	myLayers.push_back(myBackgroundLayer);
	myLayers.push_back(myMountainsLayer);
	myLayers.push_back(myGraveyardLayer);
	myLayers.push_back(myTestLayer);
	/*myLayers.push_back(myTreeLayer);
	myLayers.push_back(myBushLayer);
	myLayers.push_back(myStatueLayer);
	myLayers.push_back(myOneWayPlatformLayer);
	myLayers.push_back(myTileLayer);
	myLayers.push_back(myEnemyLayer);
	myLayers.push_back(myEffectsLayerBack);
	myLayers.push_back(myPlayerLayer);
	myLayers.push_back(myEffectsLayerFront);*/
	
	/*

	myTileLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myTreeLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myBushLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myStatueLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myOneWayPlatformLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myEnemyLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	myPlayerLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));
	*/
	//myPlayerLayer->Add(myPlayer);
	/*
	myTileLayer
		myTreeLayer
		myBushLayer
		myStatueLayer
		myOneWayPlatformLayer
		myEnemyLayer
		myPlayerLayer
		myBackgroundLayer = ne
		myGraveyardLayer = new
		myMountainsLayer = new*/
	myEffectsLayerZValueBack = 0.0;
	myEffectsLayerZValueFront = 0.0;

}
CemetaryLevel::~CemetaryLevel()
{
	delete myMap;
	EntityMan->DeleteAllEntities();
	//delete myTileLayer;
	//myRenderGroups.clear();
	for (Group* group : myPlayerTileGroups)
		delete group;
}
void CemetaryLevel::UpdatePlayer()
{
	//for (int i = 0; i < myEntitites.size(); i++)
	//	myEntitites[i]->Update();
	EntityMan->Update();
	CollisionMan->Update();
	MessageMan->dispatchDelayedMessages();
	UpdatePlayerTiles();
	/*	for (int i = 0; i < myMap->GetMap().size(); i++)
	{
	if (myMap->GetMap()[i]->isPlayerOnTile)
	{
	glm::mat4 transMat = glm::mat4(1.0);
	glm::vec3 pos = glm::vec3(myMap->GetMap()[i]->myWorldPosition, 0.02f);
	myPlayerTileTopLeft->SetTransformationMatrix(glm::translate(transMat, pos));
	}
	}*/
	//myPlayer->setDirection(myCamera.getPlayerDirection(myPlayer->mPosition));
	myPlayer->UpdateTransformationMatrix(*myCamera);
	glm::vec2 mouseScreenWorld = myCamera->mouseScreenToWorld(glm::vec2(lastX, lastY));
	glm::mat4 tran = glm::mat4(1.0f);
	tran = glm::translate(tran, glm::vec3(mouseScreenWorld.x, mouseScreenWorld.y, 0.0f));
	myCursor->SetTransformationMatrix(tran);

	for(Group* group : myRenderGroups)
	{
		glm::mat4 camTranslation = myCamera->mTranslationMatrix;
		group->UpdateXYAxis(glm::vec2(myCamera->mPosition.x, myCamera->mPosition.y));
	}
	//tileGroup->SetTransformationMatrix(myCamera->mTranslationMatrix);

	myScreenDirection = 0.0f;
	if ((myPlayer->mPosition.x > 75.5f) && (myPlayer->mPosition.x < 3150.0f) && (!myBossBattle))
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

	if (myPlayer->mPosition.x >= 3155.0f && !myBossBattle)
	{
		myBossBattle = true;
		myMap->GetTile2(96, 1)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 2)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 3)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 4)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 5)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 6)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 7)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 8)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 9)->myIsBlockingFlag = true;
		myMap->GetTile2(96, 10)->myIsBlockingFlag = true;
		//1337 is the game itself
		MessageMan->dispatchMessage(0, 1337, myDemon2->GetID(), Msg_GoFuckShitUp, 0);
		MessageMan->dispatchMessage(0, 1337, myDemon3->GetID(), Msg_GoFuckShitUp, 0);
		startScreenTime = Clock->GetCurrentTimeInSeconds();
		alphaStart = 0.0f;
		delayCutscene = Clock->GetCurrentTimeInSeconds() + 1.5f;
	}
//	myEvilVanquished->SetPosition(glm::vec4(-170.0f, 0.0f, 0, 1));
//	myEvilVanquished->SetColor(glm::vec4(1, 1, 1, 1));
	//myBossAnnouncer->SetPosition(glm::vec4(-120.0f, 0.0f, 0, 1));
	//myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, 1));
	if (myBossBattle)
	{
		if (!myDemon2->myIsActive && !myDemon3->myIsActive && !myBossDead)
		{
			myBossDead = true;
			startScreenTime2 = Clock->GetCurrentTimeInSeconds();
			alphaStart = 0.0f;
			delayCutscene2 = Clock->GetCurrentTimeInSeconds() + 1.5f;
		}
	    if (Clock->GetCurrentTimeInSeconds() > delayCutscene && !cutSceneStarted)
		{
			startScreenTime = Clock->GetCurrentTimeInSeconds();
			cutSceneStarted = true;
		}
		if (Clock->GetCurrentTimeInSeconds() - startScreenTime < 4.0 && cutSceneStarted)
		{
			//myBossAnnouncer->SetPosition(glm::vec4(-120.0f, 0.0f, 0, 1));
			myBossAnnouncer->SetPosition(glm::vec4(-140.0f, 0.0f, 0, 1));
			myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, alphaStart));
			if (alphaStart < 1.0f)
				alphaStart += 0.01f;
			if (alphaStart > 1.0f)
				alphaStart = 1.0f;
		}
		else
		{

			if(!myBossDead)
			{
				myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, alphaStart));
				if (alphaStart > 0.0f)
				{
					alphaStart -= 0.01f;
					myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, alphaStart));
					if (alphaStart < 0.0f)
					{
						alphaStart = 0.0f;
						myBossAnnouncer->SetPosition(glm::vec4(-230.0f, 2000.0f, 0, 1));
					}
				}
			}


		}
	}
	if(myBossDead)
	{
		if (Clock->GetCurrentTimeInSeconds() > delayCutscene2 && !cutSceneStarted2)
		{
			startScreenTime2 = Clock->GetCurrentTimeInSeconds();
			cutSceneStarted2 = true;
		}
		if (Clock->GetCurrentTimeInSeconds() - startScreenTime2 < 4.0 && cutSceneStarted2)
		{
			myEvilVanquished->SetPosition(glm::vec4(-170.0f, 0.0f, 0, 1));
			myEvilVanquished->SetColor(glm::vec4(1, 1, 1, alphaStart));
			if (alphaStart < 1.0f)
				alphaStart += 0.01f;
			if (alphaStart > 1.0f)
				alphaStart = 1.0f;
		}
		else
		{

			myEvilVanquished->SetColor(glm::vec4(1, 1, 1, alphaStart));
			if (alphaStart > 0.0f)
			{
				alphaStart -= 0.01f;
				myEvilVanquished->SetColor(glm::vec4(1, 1, 1, alphaStart));
				if (alphaStart < 0.0f)
				{
					levelFinished = true;
					alphaStart = 0.0f;
					myEvilVanquished->SetPosition(glm::vec4(-230.0f, 2000.0f, 0, 1));
				}
			}

		}
	}
}
void CemetaryLevel::Tick(const unsigned int ups, const unsigned int fps)
{
	myFPSLabel->myText = std::to_string(fps) + " fps";
	std::cout << ups << " ups, " << fps << " fps" << std::endl;
}
void CemetaryLevel::Update()
{
	UpdatePlayer();
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->SetPlayerTile2(myPlayer->myAABB);
	//myCamera.setPosition(-myPlayer->mPosition);
	if (myPlayer->mPosition.x > 75.5f && myPlayer->mPosition.x < 3155.0f && (!myBossBattle))
		myCamera->setPosition(glm::vec3(-myPlayer->mPosition.x, 32.0f, -myPlayer->mPosition.z));

	myCamera->Update();
	myGraveyard->increaseUVAlongX(myScreenDirection *0.002f);
	myMountain->increaseUVAlongX(myScreenDirection *0.001f);
}
void CemetaryLevel::Render() 
{
/*	myBackgroundLayer->Render();
	myMountainsLayer->Render();
	myGraveyardLayer->Render();*/
	for (Layer* layer : myLayers)
		layer->Render();

	/*glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	myTileLayer->Render();*/
	//myDebugLayer->Render();
}
void CemetaryLevel::UpdatePlayerTiles()
{
	glm::mat4 transMat = glm::mat4(1.0f);
	glm::vec3 pos = glm::vec3(myMap->lastPlayerTileBottomLeft->myWorldPosition, 0.02f);
	myPlayerTileBottomLeft->SetTransformationMatrix(glm::translate(transMat, pos));

	transMat = glm::mat4(1.0f);
	pos = glm::vec3(myMap->lastPlayerTileTopLeft->myWorldPosition, 0.02f);
	myPlayerTileTopLeft->SetTransformationMatrix(glm::translate(transMat, pos));

	transMat = glm::mat4(1.0f);
	pos = glm::vec3(myMap->lastPlayerTileTopRight->myWorldPosition, 0.02f);
	myPlayerTileTopRight->SetTransformationMatrix(glm::translate(transMat, pos));

	transMat = glm::mat4(1.0f);
	pos = glm::vec3(myMap->lastPlayerTileBottomRight->myWorldPosition, 0.02f);
	myPlayerTileBottomRight->SetTransformationMatrix(glm::translate(transMat, pos));

	transMat = glm::mat4(1.0f);
	pos = glm::vec3(myMap->lastPlayerTileMidRight->myWorldPosition, 0.02f);
	myPlayerTileMidRight->SetTransformationMatrix(glm::translate(transMat, pos));

	transMat = glm::mat4(1.0f);
	pos = glm::vec3(myMap->lastPlayerTileMidLeft->myWorldPosition, 0.02f);
	myPlayerTileMidLeft->SetTransformationMatrix(glm::translate(transMat, pos));

	transMat = glm::mat4(1.0f);
	pos = glm::vec3(myMap->lastPlayerTile->myWorldPosition, 0.02f);
	myPlayerTile->SetTransformationMatrix(glm::translate(transMat, pos));
}
void CemetaryLevel::DeInitialize()
{

}
void CemetaryLevel::ProcessKeyBoard(int key, float deltaTime, int action)
{
	myPlayer->processKeyBoard(key, deltaTime, action);
	/*if (key == GLFW_KEY_W)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_S)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_A)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_D)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_V)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_B)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_T)
		myCamera->ShakeCamera(2000, 40, 32);
	if (key == GLFW_KEY_SPACE)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_E)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_Q)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_LEFT_CONTROL)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_C)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_R)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_G)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_1)
		myPlayer->SetAnimation("HeroRun");
	if (key == GLFW_KEY_2)
		myPlayer->SetAnimation("HeroAttack");
	if (key == GLFW_KEY_3)
		myPlayer->SetAnimation("HeroCrouch");
	if (key == GLFW_KEY_4)
		myPlayer->SetAnimation("HeroHurt");
	if (key == GLFW_KEY_5)
		myPlayer->SetAnimation("HeroIdle");
	if (key == GLFW_KEY_6)
		myPlayer->SetAnimation("HeroJump");*/

}
void CemetaryLevel::ProcessMouse(double xpos, double ypos, bool movement)
{
	myMouseMovement = movement;

	lastX = xpos;
	lastY = ypos;

	myCamera->setScreenPosition(glm::vec2(lastX, lastY));
}
void CemetaryLevel::AddEntity(Entity* entity)
{
	myEntitites.push_back(entity);
}

void CemetaryLevel::SpawnEntity(const std::string& type, const glm::vec3&  inpos, const glm::vec3& indir, int heading)
{
	myNumberOfEntities++;
	if (type == "Necromancer Projectile") 
	{
		NecromancerProjectile* necroProjectile = new NecromancerProjectile(myNumberOfEntities, "NecromancerProjectile" + std::to_string(myNumberOfEntities), inpos, indir);
		myEntitites.push_back(necroProjectile);
		enemyGroup->Add(necroProjectile->mySprite);
		CollisionMan->RegisterProjectile(necroProjectile);
		EntityMan->registerEntity(necroProjectile);
	}
	else if (type == "Imp Projectile")
	{
		ImpProjectile* impProjectile = new ImpProjectile(myNumberOfEntities, "ImpProjectile" + std::to_string(myNumberOfEntities), inpos, indir);
		myEntitites.push_back(impProjectile);
		enemyGroup->Add(impProjectile->mySprite);
		CollisionMan->RegisterProjectile(impProjectile);
		EntityMan->registerEntity(impProjectile);
	}
	else if (type == "Adventurer Projectile")
	{
		AdventurerProjectile* impProjectile = new AdventurerProjectile(myNumberOfEntities, "AdventurerProjectile" + std::to_string(myNumberOfEntities), inpos, indir);
		myEntitites.push_back(impProjectile);
		enemyGroup->Add(impProjectile->mySprite);
		CollisionMan->RegisterHeroProjectile(impProjectile);
		EntityMan->registerEntity(impProjectile);
	}
	else if (type == "Adventurer Arrow")
	{
		AdventurerProjectileArrow* impProjectile = new AdventurerProjectileArrow(myNumberOfEntities, "AdventurerProjectile" + std::to_string(myNumberOfEntities), inpos, indir);
		myEntitites.push_back(impProjectile);
		enemyGroup->Add(impProjectile->mySprite);
		CollisionMan->RegisterHeroProjectile(impProjectile);
		EntityMan->registerEntity(impProjectile);
	}
	else if (type == "Medium Hit")
	{
		Effect* effect = new Effect(myNumberOfEntities, "MediumHit" + std::to_string(myNumberOfEntities), inpos, new HitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(100, 100), TextureMan->GetTexture("hiteffect"), Heading::RIGHTFACING),"HitEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Large Hit")
	{
		Effect* effect = new Effect(myNumberOfEntities, "LargeHit" + std::to_string(myNumberOfEntities), inpos, new HitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(200, 200), TextureMan->GetTexture("hiteffectslow"), Heading::RIGHTFACING), "HitEffectSlow");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Large Hit Fast")
	{
		Effect* effect = new Effect(myNumberOfEntities, "LargeHitFast" + std::to_string(myNumberOfEntities), inpos, new HitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(200, 200), TextureMan->GetTexture("hiteffect"), Heading::RIGHTFACING), "HitEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Extra Large Hit")
	{
		Effect* effect = new Effect(myNumberOfEntities, "ExtraLargeHit" + std::to_string(myNumberOfEntities), inpos, new HitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(400, 400), TextureMan->GetTexture("hiteffectslow"), Heading::RIGHTFACING), "HitEffectSlow");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if(type == "Blood Effect Random")
	{
		int number = (rand() % 3);
		if (number == 0)
			number = 1;
		else if (number == 1)
			number = 3;
		else if (number == 2)
			number = 4;
		std::string blood = "HitEffectBlood" + std::to_string(number);
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), blood);
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Blood Effect 1")
	{
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "HitEffectBlood1");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Blood Effect 2")
	{
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "HitEffectBlood2");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Blood Effect 3")
	{
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "HitEffectBlood3");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Blood Effect 4")
	{
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "HitEffectBlood4");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Enemy Hit Effect")
	{
		int number = (rand() % 2);
		if (number == 0)
			number = 1;
		else if (number == 1)
			number = 2;
		std::string hit = "EnemyHitEffect" + std::to_string(number);
		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new EnemyHitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("enemyhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), hit);
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Sword Effect 1")
	{

		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new SwordHitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("swordhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "SwordHitEffect1");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Sword Effect 2")
	{

		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new SwordHitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("swordhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "SwordHitEffect1");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Sword Effect 3")
	{

		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new SwordHitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("swordhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "SwordHitEffect1");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Enemy Hit Death")
	{
		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new EnemyHitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("enemyhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "EnemyDeathEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);

	}
	else if (type == "Enemy Hit Death Large")
	{
		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new EnemyHitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(192, 192), TextureMan->GetTexture("enemyhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "EnemyDeathEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Enemy Hit Death Small")
	{
		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new EnemyHitEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(32, 32), TextureMan->GetTexture("enemyhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "EnemyDeathEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Pickup Destroyed")
	{
		Effect* effect = new Effect(myNumberOfEntities, "PickupDestroyed" + std::to_string(myNumberOfEntities), inpos, new PickupDestroyedSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(16, 16), TextureMan->GetTexture("pickupdestroyed"), Heading::RIGHTFACING), "PickupDestroyed");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Adventurer Slide")
	{
		Effect* effect = new Effect(myNumberOfEntities, "AdventurerSlide" + std::to_string(myNumberOfEntities), inpos, new AdventurerSlideEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(100 - 25, 74 - 18.5), TextureMan->GetTexture("slideeffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "AdventurerSlideEffect",true);
		myEntitites.push_back(effect);
		effectsGroupBack->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "Adventurer DropKick")
	{
		Effect* effect = new Effect(myNumberOfEntities, "AdventurerDropKick" + std::to_string(myNumberOfEntities), inpos, new AdventurerDropKickEffectSprite(glm::vec4(inpos.x, inpos.y, myEffectsLayerZValueFront, 1.0f), glm::vec2(100 - 25, 74 - 18.5), TextureMan->GetTexture("dropkickeffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "AdventurerDropKickEffect", true);
		myEntitites.push_back(effect);
		effectsGroupBack->Add(effect->mySprite);
		EntityMan->registerEntity(effect);
		myEffectsLayerZValueFront += 0.00001;
	}
	else if (type == "HP Potion")
	{
		PotionPickup* potion = new PotionPickup(myNumberOfEntities, "HPPotion" + std::to_string(myNumberOfEntities), inpos, "hppotion");
		myEntitites.push_back(potion);
		effectsGroup->Add(potion->mySprite);
		CollisionMan->RegisterPickup(potion);
		EntityMan->registerEntity(potion);
		
	}


}
void CemetaryLevel::RemoveEntity(Entity* entity)
{
	if(dynamic_cast<BaseProjectileEntity*>(entity))
	{
		if((dynamic_cast<BaseProjectileEntity*>(entity)->isHeroProjectile))
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