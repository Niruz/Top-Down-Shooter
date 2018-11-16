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

void GothicVania::Initialize()
{
	lastX = 640.0f;
	lastY = 360.0f;
	myHeight = 720.0f;
	myWidth = 1280.0f;
	myMouseMovement = false;

	glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);
	myCamera.setScreenPosition(glm::vec2(lastX, lastY));
	myCamera.setProjectionMatrix(ortho);
	myCamera.setWidth(myWidth);
	myCamera.setHeight(myHeight);


	myShader = ShaderMan->getShader(SIMPLE_FORWARD_SHADER);
	myTileLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f));
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

	

	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-580, 340, 0.8)));
	myFPSLabel = new Label("", glm::vec4(-55, -10, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(myFPSLabel);

	myCursor = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.8)));
	myCursor->Add(new Sprite(glm::vec4(0, 0, 0.3, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("cursor")/*, glm::vec2(0, 15)*/));

	myTileLayer->Add(fpsGroup);
	myTileLayer->Add(myCursor);

	myMap = new TileMap("Levels/test3.level");

	myMap->printMap();

	std::vector<Tile*> myPath3;
	myMap->GetPath(1, 1, 18, 10, myPath3);

	myMap->printPath(myPath3);
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	std::vector<Tile*> map = myMap->GetMap();
	tileGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)));
	float startX = -32.0f * 10.0f;
	float startY = 32.0f * 6;
	for (int i = 0; i < map.size(); i++)
	{
		if (i % 20 == 0)
		{
			startY -= 32.0f;
			startX = -32.0f*10.0f;
		}

		if (i == 239)
			int shitterooo = 5;
		/*if (map[i]->isPlayerOnTile)
		{ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mCamera.mTranslationMatrix * map[i]->myModelMatrix);
		}*/
		if (map[i]->myIsBlockingFlag)
		{
			//Should be 32 but 30 looks cool
			//myLayer->Add(new Sprite(glm::vec4(startX, startY, 0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("wall")/*, glm::vec2(0, 15)*/));
			tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.01, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("grass")/*, glm::vec2(0, 15)*/));
		}
		else
		{
			//myLayer->Add(new Sprite(glm::vec4(startX, startY, 0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floor")/*, glm::vec2(1, 15)*/));
			//tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0, 1), glm::vec2(30.0f, 30.0f), TextureMan->GetTexture("floor")/*, glm::vec2(1, 15)*/));
		}
		startX += 32.0f;
	}
	myTileLayer->Add(tileGroup);


	//Debug
	myPlayerTile = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.02)));
	myPlayerTile->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floor2")/*, glm::vec2(0, 15)*/));

	tileGroup->Add(myPlayerTile);
	myTileLayer->Add(tileGroup);
	myTileLayer->Add(myPlayer->mySprite);

	myPlayer->myTileMap = myMap;
	//myDebugLayer->Add(myPlayerTile);
}
void GothicVania::UpdatePlayer()
{
	myPlayer->Update();
	for (int i = 0; i < myMap->GetMap().size(); i++)
	{
		if (myMap->GetMap()[i]->isPlayerOnTile)
		{
			glm::mat4 transMat = glm::mat4(1.0);
			glm::vec3 pos = glm::vec3(myMap->GetMap()[i]->myWorldPosition, 0.02f);
			myPlayerTile->SetTransformationMatrix(glm::translate(transMat, pos));
			break;
		}
	}
	myPlayer->setDirection(myCamera.getPlayerDirection(myPlayer->mPosition));
	myPlayer->UpdateTransformationMatrix(myCamera);
	glm::vec2 mouseScreenWorld = myCamera.mouseScreenToWorld(glm::vec2(lastX, lastY));
	glm::mat4 tran = glm::mat4(1.0f);
	tran = glm::translate(tran, glm::vec3(mouseScreenWorld.x, mouseScreenWorld.y, 0.0f));
	myCursor->SetTransformationMatrix(tran);

	tileGroup->SetTransformationMatrix(myCamera.mTranslationMatrix);

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
	myCamera.setPosition(-myPlayer->mPosition);
	myGraveyard->increaseUVAlongX(-0.002f);
	myMountain->increaseUVAlongX(-0.001f);
}
void GothicVania::Render()
{
	myBackgroundLayer->Render();
	myMountainsLayer->Render();
	myGraveyardLayer->Render();
	
	myTileLayer->Render();
	//myDebugLayer->Render();
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

	myCamera.setScreenPosition(glm::vec2(lastX, lastY));
}