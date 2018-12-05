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
void GothicVania::Initialize()
{
	CemetaryLevel* levelOne = new CemetaryLevel("Cemetary");
	myLevels.push_back(levelOne);
	myLevels[0]->Initialize();

	GameWorld->RegisterLevel(levelOne);
	activeLevel = 0;

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
	myLevels[0]->Tick(getUPS(),getFPS());
}
void GothicVania::Update()
{
	myLevels[0]->Update();
}
void GothicVania::Render()
{
	myLevels[0]->Render();
}

void GothicVania::ProcessKeyBoard(int key, float deltaTime, int action)
{
	myLevels[0]->ProcessKeyBoard(key, deltaTime, action);
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