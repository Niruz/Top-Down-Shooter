#include "GothicVania.h"
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
void GothicVania::Initialize()
{
	lastX = 640.0f;
	lastY = 360.0f;
	myHeight = 720.0f;
	myWidth = 1280.0f;
	myMouseMovement = false;

	glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);
	myCamera = new Camera(666, "Camera1");
	myCamera->setScreenPosition(glm::vec2(lastX, lastY));
	myCamera->setProjectionMatrix(ortho);
	myCamera->setWidth(myWidth);
	myCamera->setHeight(myHeight);
	EntityMan->registerEntity(myCamera);

	myShader = ShaderMan->getShader(SIMPLE_FORWARD_SHADER);
	myTileLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -1.0f, 1.0f));
	myBackgroundLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_BACKGROUND1_SHADER) , glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f));
	myGraveyardLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_BACKGROUND2_SHADER) , glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f));
	myMountainsLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_BACKGROUND3_SHADER) , glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f));

	myBackgroundLayer->Add(new Sprite(glm::vec4(0, 0, -0.9, 1), glm::vec2(1.0f, 1.0f), TextureMan->GetTexture("moonbackground")/*, glm::vec2(0, 15)*/));

	myGraveyard= new Sprite(glm::vec4(0, -0.25f, -0.7, 1), glm::vec2(1.0f, 0.5f), TextureMan->GetTexture("graveyard")/*, glm::vec2(0, 15)*/);
	myGraveyardLayer->Add(myGraveyard);
	//myGraveyardLayer->Add(new Sprite(glm::vec4(0, -0.25f, -0.7, 1), glm::vec2(1.0f, 0.5f), TextureMan->GetTexture("graveyard")/*, glm::vec2(0, 15)*/));


	myMountain = new Sprite(glm::vec4(0, -0.25, -0.8, 1), glm::vec2(1.0f, 1.0f), TextureMan->GetTexture("mountains")/*, glm::vec2(0, 15)*/);
	myMountain->setUVSpecialized(glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(2, 1), glm::vec2(2, 0));
	myMountainsLayer->Add(myMountain);
	//myMountainsLayer->Add(new Sprite(glm::vec4(0, -0.25, -0.8, 1), glm::vec2(1.0f, 1.0f), TextureMan->GetTexture("mountains")/*, glm::vec2(0, 15)*/));
	//myDebugLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f));

	myPlayer = new HeroEntity(0, "Player");
/*	mySkeleton = new SkeletonEntity(1, "Skeleton1", glm::vec3(64.0f, -152.0f, 0.1f), glm::vec3(224.0f, -152.0f, 0.1f));
	myGhost = new GhostEntity(2, "Ghost1", glm::vec3(-128.0f, -96.0f, 0.1f), glm::vec3(-128.0f, 32.0f, 0.1f));
	myHellCat = new HellCatEntity(3, "HellCat1", glm::vec3(640.0f, -150.0f, 0.1f), glm::vec3(864.0f, -150.0f, 0.1f));
	myEyeMonster = new EyeMonsterEntity(4, "EyeMonster1", glm::vec3(96.0f, -96.0f, 0.09f), glm::vec3(256.0f, -96.0f, 0.09f));
	myDemon = new DemonEntity(5, "Demon1", glm::vec3(128, -96 - 15, 0.1f), glm::vec3(128.0f, -32.0f, 0.1f));
	myGhost2 = new GhostEntity(6, "Ghost2", glm::vec3(1328.0f, -160.0f, 0.1f), glm::vec3(1328.0f, -32.0f, 0.1f));
	myGhost3 = new GhostEntity(7, "Ghost3", glm::vec3(2624.0f, -128.0f, 0.1f), glm::vec3(2624.0f, -32.0f, 0.1f));
	myDemon2 = new DemonEntity(8, "Demon2", glm::vec3(3008.0f, 224 - 15, 0.0999f), glm::vec3(3008.0f, -32.0f, 0.1f));
	myDemon3 = new DemonEntity(9, "Demon3", glm::vec3(3264.0f, 224 - 15, 0.1f), glm::vec3(3264.0f, -32.0f, 0.1f));
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
	myFireGolem1 =  new FireGolemEntity(21, "FireGolem1", glm::vec3(-288.0f, -125.0, 0.1f), glm::vec3(-32.0f, -125.0, 0.1f));
	

	

	myEntitites.push_back(myPlayer);
	/*myEntitites.push_back(mySkeleton);
	myEntitites.push_back(myGhost); 
	myEntitites.push_back(myGhost2);
	myEntitites.push_back(myGhost3);
	myEntitites.push_back(myHellCat);
	myEntitites.push_back(myEyeMonster);
	myEntitites.push_back(myDemon);
	myEntitites.push_back(myDemon2);
	myEntitites.push_back(myDemon3);
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

	for (Entity* entity : myEntitites)
		EntityMan->registerEntity(entity);

	//myDemon2->myAnimatedSprite->SetHeading(Heading::LEFTFACING);
	
	//Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-580, 340, 0.8)));
	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(260, 160, 0.8)));
	myFPSLabel = new Label("", glm::vec4(-55, -10, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	//myFPSLabel = new Label("", glm::vec4(0, 0, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(myFPSLabel);

	bossAnnouncerGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.8f)));
	myBossAnnouncer = new Label("Fire & Fury", glm::vec4(-180.0f, 2000.0f, 0, 1), "DefaultFont96", glm::vec4(1, 1, 1, 1));
	myBossAnnouncer->SetColor(glm::vec4(1,1,1,0));
	//bossAnnouncerGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(320.0f, 180.0f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	bossAnnouncerGroup->Add(myBossAnnouncer);

	myCursor = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.8)));
	myCursor->Add(new Sprite(glm::vec4(0, 0, 0.3, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("cursor")/*, glm::vec2(0, 15)*/));

	myTileLayer->Add(fpsGroup);

	//myTileLayer->Add(myCursor);

	myMap = new TileMap("Levels/test3.level",glm::vec2(-320, 3488), glm::vec2(160, -192), glm::vec2(0, 119), glm::vec2(0, 11));

	myMap->printMap();

	std::vector<Tile*> myPath3;
	myMap->GetPath(1, 1, 18, 10, myPath3);

	myMap->printPath(myPath3);
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->SetPlayerTile2(myPlayer->myAABB);
	std::vector<Tile*> map = myMap->GetMap();
	tileGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)));
	float startX = -32.0f * 10.0f;
	float startY = 32.0f * 6;
	srand(54);

	int grassType = 1;
	for (int i = 0; i < map.size(); i++)
	{
		if (i % 120 == 0)
		{
			startY -= 32.0f;
			startX = -32.0f*10.0f;
		}

		if (i == 1439)
			int shitterooo = 5;
		/*if (map[i]->isPlayerOnTile)
		{ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mCamera.mTranslationMatrix * map[i]->myModelMatrix);
		}*/
		if (map[i]->myIsBlockingFlag)
		{
			//Should be 32 but 30 looks cool
			//myLayer->Add(new Sprite(glm::vec4(startX, startY, 0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("wall")/*, glm::vec2(0, 15)*/));
			if (map[i]->myIsSpikedFloor)
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.01, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("spikes")/*, glm::vec2(0, 15)*/));
			}
			else if (map[i]->myIsPillar)
			{
				std::string pillar = (rand() % 2) == 0 ? "pillar1" : "pillar2";
				tileGroup->Add(new Sprite(glm::vec4(startX, startY+32.5, 0.01, 1), glm::vec2(32.0f, 96.0f), TextureMan->GetTexture(pillar)/*, glm::vec2(0, 15)*/));
			//	tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.011, 1), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
			}
			else if (map[i]->myIsOneWayTile)
			{
				//tileGroup->Add(new Sprite(glm::vec4(startX, startY+14.5f, 0.011, 1), glm::vec2(32.0f, 4.50f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
				if (map[i]->myTileType == "F")
				{
					tileGroup->Add(new Sprite(glm::vec4(startX, startY + 5, 0.0092, 1), glm::vec2(32.0f, 41), TextureMan->GetTexture("floatinggrass")/*, glm::vec2(0, 15)*/));
				//	tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.011, 1), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
				}
			}
			else
			{
				if(!(map[i]->myTileType == "o"))
					tileGroup->Add(new Sprite(glm::vec4(startX, startY+5, 0.01, 1), glm::vec2(32.0f, 41), grassType > 0 ? TextureMan->GetTexture("grass") : TextureMan->GetTexture("grass2")/*, glm::vec2(0, 15)*/));
				grassType *= -1;
			//	tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.011, 1), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f,0.0f,1.0f,0.5f)));
			}
			//tileGroup->Add(new Sprite(glm::vec4(startX, startY , 0.01, 1), glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
		}
		else
		{
			if (map[i]->myIsSpikedFloor)
			{
				if(map[i]->myTileType == "y")
					tileGroup->Add(new Sprite(glm::vec4(startX, startY+ 31, 0.01, 1), glm::vec2(32.0f, 94.0f), TextureMan->GetTexture("spikedpillar")/*, glm::vec2(0, 15)*/));
				else
					tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.01, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("spikes")/*, glm::vec2(0, 15)*/));
			//	tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.011, 1), glm::vec2(32.0f, 16.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
			}
			else if (map[i]->myTileType == "f")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY+0.5f, 0.0092, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floatingsolid2")/*, glm::vec2(0, 15)*/));
				//	tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.011, 1), glm::vec2(32.0f, 16.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
			}
			else if (map[i]->myTileType == "e")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY - 21.0f, 0.0092, 1), glm::vec2(32.0f, 64.0f), TextureMan->GetTexture("floatingleftgrass")/*, glm::vec2(0, 15)*/));
				//	tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.011, 1), glm::vec2(32.0f, 16.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
			}
			else if (map[i]->myTileType == "E")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY - 19.0f, 0.008, 1), glm::vec2(32.0f, 64.0f), TextureMan->GetTexture("floatingrightgrass")/*, glm::vec2(0, 15)*/));
				//	tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.011, 1), glm::vec2(32.0f, 16.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.5f)));
			}
			else if (map[i]->myTileType == "1")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.009, 1), glm::vec2(27.0f, 39.0f), TextureMan->GetTexture("stone1")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			else if (map[i]->myTileType == "2")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.009, 1), glm::vec2(27.0f, 40.0f), TextureMan->GetTexture("stone2")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			else if (map[i]->myTileType == "3")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.009, 1), glm::vec2(27.0f, 33.0f), TextureMan->GetTexture("stone3")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			else if (map[i]->myTileType == "4")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.009, 1), glm::vec2(19.0f, 38.0f), TextureMan->GetTexture("stone4")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			else if (map[i]->myTileType == "S")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY+20.0f, 0.009, 1), glm::vec2(63.0f, 75.0f), TextureMan->GetTexture("statue")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			else if (map[i]->myTileType == "b")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.009, 1), glm::vec2(34.0f, 29.0f), TextureMan->GetTexture("bushsmall")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			else if (map[i]->myTileType == "B")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY+10, 0.009, 1), glm::vec2(76.0f, 65.0f), TextureMan->GetTexture("bushlarge")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			else if (map[i]->myTileType == "T")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY + 40.0f, 0.0091, 1), glm::vec2(166.0f, 117.0f), TextureMan->GetTexture("tree1")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			else if (map[i]->myTileType == "t")
			{
				tileGroup->Add(new Sprite(glm::vec4(startX, startY + 60.0f, 0.0091, 1), glm::vec2(176.0f, 171.0f), TextureMan->GetTexture("tree3")/*, glm::vec2(0, 15)*/));
				//tileGroup->Add()
			}
			//myLayer->Add(new Sprite(glm::vec4(startX, startY, 0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floor")/*, glm::vec2(1, 15)*/));
			//tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0, 1), glm::vec2(30.0f, 30.0f), TextureMan->GetTexture("floor")/*, glm::vec2(1, 15)*/));
		}
		startX += 32.0f;
	}
	myTileLayer->Add(tileGroup);

	//Temp
	myGuiGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-260, 160, 0.8)));
	myHPBar = new Sprite(glm::vec4(0.0f, 0.0f, 0.2f, 1.0f), glm::vec2(85, 25), TextureMan->GetTexture("hpbar"));
	myGuiGroup->Add(myHPBar);
	myTileLayer->Add(myGuiGroup);

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
	tileGroup->Add(myDemon->mySprite);
	tileGroup->Add(myDemon2->mySprite);
	tileGroup->Add(myDemon3->mySprite);
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
	tileGroup->Add(myFireGolem1->mySprite);

	myTileLayer->Add(tileGroup);
	myTileLayer->Add(myPlayer->mySprite);
	//screen
	myTileLayer->Add(bossAnnouncerGroup);
	myPlayer->myTileMap = myMap;
	//myDebugLayer->Add(myPlayerTile);
	lastPlayerX = myPlayer->mPosition.x;
	myScreenDirection = 0.0f;
	myBossBattle = false;
	cutSceneStarted = false;

	myFireGolem1->myTileMap = myMap;
}
void GothicVania::UpdatePlayer()
{
	for (int i = 0; i < myEntitites.size(); i++)
		myEntitites[i]->Update();
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

	tileGroup->SetTransformationMatrix(myCamera->mTranslationMatrix);

	myScreenDirection = 0.0f;
	if ((myPlayer->mPosition.x > -0.5f) && (myPlayer->mPosition.x < 3150.0f) && (!myBossBattle))
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
	if (myPlayer->mPosition.x >= 3150.0f && !myBossBattle)
	{
		myBossBattle = true;
		myMap->GetTile2(98,  1)->myIsBlockingFlag = true; 
		myMap->GetTile2(98,  2)->myIsBlockingFlag = true;
		myMap->GetTile2(98,  3)->myIsBlockingFlag = true;
		myMap->GetTile2(98,  4)->myIsBlockingFlag = true;
		myMap->GetTile2(98,  5)->myIsBlockingFlag = true;
		myMap->GetTile2(98,  6)->myIsBlockingFlag = true;
		myMap->GetTile2(98,  7)->myIsBlockingFlag = true;
		myMap->GetTile2(98,  8)->myIsBlockingFlag = true;
		myMap->GetTile2(98,  9)->myIsBlockingFlag = true;
		myMap->GetTile2(98, 10)->myIsBlockingFlag = true;
		//1337 is the game itself
		MessageMan->dispatchMessage(0, 1337, myDemon2->GetID(), Msg_GoFuckShitUp, 0);
		MessageMan->dispatchMessage(0, 1337, myDemon3->GetID(), Msg_GoFuckShitUp, 0);
		startScreenTime = Clock->GetCurrentTime();
		alphaStart = 0.0f;
		delayCutscene = Clock->GetCurrentTime() + 1.5f;
	}
	if (myBossBattle)
	{
		if(Clock->GetCurrentTime() > delayCutscene && !cutSceneStarted)
		{
			startScreenTime = Clock->GetCurrentTime();
			cutSceneStarted = true;
		}
		if (Clock->GetCurrentTime() - startScreenTime < 4.0 && cutSceneStarted)
		{
			myBossAnnouncer->SetPosition(glm::vec4(-230.0f, 0.0f, 0, 1));
			myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, alphaStart));
			if(alphaStart < 1.0f)
				alphaStart += 0.01f;
			if (alphaStart > 1.0f)
				alphaStart = 1.0f;
		}
		else
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
void GothicVania::Tick()
{
	myFPSLabel->myText = std::to_string(getFPS()) + " fps";
	std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
}
void GothicVania::Update()
{
	UpdatePlayer();
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->SetPlayerTile2(myPlayer->myAABB);
	//myCamera.setPosition(-myPlayer->mPosition);
	if(myPlayer->mPosition.x > -0.5f && myPlayer->mPosition.x < 3150.0f &&(!myBossBattle))
		myCamera->setPosition(glm::vec3(-myPlayer->mPosition.x, 32.0f, -myPlayer->mPosition.z));
	
	myCamera->Update();
	myGraveyard->increaseUVAlongX(myScreenDirection *0.002f);
	myMountain->increaseUVAlongX(myScreenDirection *0.001f);
}
void GothicVania::Render()
{
	myBackgroundLayer->Render();
	myMountainsLayer->Render();
	myGraveyardLayer->Render();
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	myTileLayer->Render();
	//myDebugLayer->Render();
}
void GothicVania::UpdatePlayerTiles()
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
void GothicVania::ProcessKeyBoard(int key, float deltaTime, int action)
{
	if (key == GLFW_KEY_W)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_S)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_A)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_D)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_V)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_T)
		myCamera->ShakeCamera(2000,40,32);
	if (key == GLFW_KEY_SPACE)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_LEFT_CONTROL)
		myPlayer->processKeyBoard(key, deltaTime, action);
	if (key == GLFW_KEY_C)
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
		myPlayer->SetAnimation("HeroJump");




}
void GothicVania::ProcessMouse(double xpos, double ypos, bool movement)
{
	myMouseMovement = movement;

	lastX = xpos;
	lastY = ypos;

	myCamera->setScreenPosition(glm::vec2(lastX, lastY));
}