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
#include "GhoulEntity.h"
#include "UndeadWarriorEntity.h"
#include "ReaperEntity.h"
#include "ImpEntity.h"
#include "NecromancerEntity.h"
#include "CollisionManager.h"
#include "World.h"
#include "GothicVaniaGameStates.h"
#include "SplashScreen.h"

void GothicVania::Initialize()
{
	CemetaryLevel* levelOne = new CemetaryLevel("Cemetary");
	myLevels.push_back(levelOne);
	myLevels[0]->Initialize();

	GameWorld->RegisterLevel(levelOne);
	activeLevel = 0;
	myRenderingSplashScreen = false;
	mySplashScreen = new SplashScreen();

	myStateMachine = new StateMachine<GothicVania>(this);
	myStateMachine->setCurrentState(GothicVaniaIntroState::Instance());
	myStateMachine->changeState(GothicVaniaIntroState::Instance());

	

	
/*	for (int i = 0; i < 10000; i++)
	{
		Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(260, 160, 0.8)));
		//NecromancerEntity* myPlayer = new NecromancerEntity(26, "Necromancer1", glm::vec3(1456.0f, -120.0f, 0.07f), glm::vec3(1840.0f, -120.0f, 0.07f));
		HeroEntity* myPlayer = new HeroEntity(0, "Player");
		EntityMan->registerEntity(myPlayer);
		//HeroEntity* myPlayer = new HeroEntity(0, "Player");
		fpsGroup->Add(myPlayer->mySprite);
		//delete myPlayer;

		EntityMan->DeleteAllEntities();
		delete fpsGroup;
	}

/*	myLevels.push_back(new CemetaryLevel("Cemetary"));
	myLevels[0]->Initialize();
	delete myLevels[0];
	myLevels.clear();

	myLevels.push_back(new CemetaryLevel("Cemetary"));
	myLevels[0]->Initialize();
	delete myLevels[0];
	myLevels.clear();

	myLevels.push_back(new CemetaryLevel("Cemetary"));
	myLevels[0]->Initialize();
	delete myLevels[0];
	myLevels.clear();

	myLevels.push_back(new CemetaryLevel("Cemetary"));
	myLevels[0]->Initialize();
	delete myLevels[0];
	myLevels.clear();

	myLevels.push_back(new CemetaryLevel("Cemetary"));
	myLevels[0]->Initialize();
	delete myLevels[0];
	myLevels.clear();

	myLevels.push_back(new CemetaryLevel("Cemetary"));
	myLevels[0]->Initialize();
	delete myLevels[0];
	myLevels.clear();*/
}
void GothicVania::Tick()
{
	//myStateMachine->tick();
	myLevels[activeLevel]->Tick(getUPS(),getFPS());
}
void GothicVania::Update()
{
	myStateMachine->update();
}
void GothicVania::Render()
{
	if (myRenderingSplashScreen)
		RenderGameScreen();
	else
		myLevels[activeLevel]->Render();
}
void GothicVania::RenderLevel()
{
	myLevels[activeLevel]->Render();
}
void GothicVania::UpdateLevel()
{
	myLevels[activeLevel]->Update();
}
void GothicVania::ProcessKeyBoard(int key, float deltaTime, int action)
{
	myStateMachine->HandleInput(key, action);
	//myLevels[0]->ProcessKeyBoard(key, deltaTime, action);
	/*if (key == GLFW_KEY_T)
		activeLevel = 1;
	else
	{
		myLevels[activeLevel]->ProcessKeyBoard(key, deltaTime, action);
	}*/
	
}
void GothicVania::ProcessMouse(double xpos, double ypos, bool movement)
{
	myLevels[activeLevel]->ProcessMouse(xpos, ypos, movement);
}
void GothicVania::RenderGameScreen()
{
	mySplashScreen->Render();
}
void GothicVania::UpdateGameScreen()
{
	mySplashScreen->Update();
}