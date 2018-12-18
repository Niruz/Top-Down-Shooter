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
void GothicVania::Initialize()
{
	CemetaryLevel* levelOne = new CemetaryLevel("Cemetary");
	myLevels.push_back(levelOne);
	myLevels[0]->Initialize();

	GameWorld->RegisterLevel(levelOne);
	activeLevel = 0;
	myGameScreenDone = false;
	myGameScreenLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_FORWARD_SHADER) , glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));

	bossAnnouncerGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.8f)));
	myBossAnnouncer = new Label("What The Moon Brings", glm::vec4(-240.0f, 0.0f, 0, 1), "Adventurer48", glm::vec4(1, 1, 1, 1));
	myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, 0));
	bossAnnouncerGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(640.0f, 360.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0)));
	bossAnnouncerGroup->Add(myBossAnnouncer);
	myGameScreenLayer->Add(bossAnnouncerGroup);

	myStateMachine = new StateMachine<GothicVania>(this);
	myStateMachine->setCurrentState(GothicVaniaIntroState::Instance());
	myStateMachine->changeState(GothicVaniaIntroState::Instance());

	myAlphaGameLayer = 0.0f;
	myAlphaDirection = 0.005f;
	/*myLevels.push_back(new CemetaryLevel());
	myLevels[1]->Initialize();
	delete myLevels[0];
	myLevels.clear();

	myLevels.push_back(new CemetaryLevel());
	myLevels[0]->Initialize();
	delete myLevels[0];
	myLevels.clear();

	myLevels.push_back(new CemetaryLevel());
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
	myLevels[activeLevel]->Render();
	//myStateMachine->render();
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
	myLevels[0]->ProcessMouse(xpos, ypos, movement);
}
void GothicVania::RenderGameScreen()
{
	myGameScreenLayer->Render();
	myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, myAlphaGameLayer));
}
void GothicVania::UpdateGameScreen()
{
	myAlphaGameLayer += myAlphaDirection;
	if (myAlphaGameLayer >= 1.0f)
	{
		myAlphaGameLayer = 1.0f;
		myAlphaDirection = -0.005f;
	}
	if(myAlphaDirection < 0.0f && myAlphaGameLayer <= 0.0f && !myGameScreenDone)
	{
		myGameScreenDone = true;
	}
}