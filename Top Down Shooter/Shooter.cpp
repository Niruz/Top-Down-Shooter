#include "Shooter.h"
#include "ShaderManager.h"
#include "Layer.h"
#include "Label.h"
#include "Sprite.h"
#include "BatchRenderer.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Group.h"
#include "TileMap.h"
#include "Player.h"
#include <iostream>
#include "glfw3.h"

void Shooter::Initialize()
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
	myLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f));
	//myDebugLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f));

	myPlayer = new Player();

	myLayer->Add(myPlayer->mySprite);

	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-580, 340, 0.8)));
	myFPSLabel = new Label("", glm::vec4(-55, -10, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(myFPSLabel);

	myCursor = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.8)));
	myCursor->Add(new Sprite(glm::vec4(0, 0, 0.3, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("cursor")/*, glm::vec2(0, 15)*/));

	myLayer->Add(fpsGroup);
	myLayer->Add(myCursor);

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
			tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0.01, 1), glm::vec2(30.0f, 30.0f), TextureMan->GetTexture("wall")/*, glm::vec2(0, 15)*/));
		}
		else
		{
			//myLayer->Add(new Sprite(glm::vec4(startX, startY, 0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floor")/*, glm::vec2(1, 15)*/));
			tileGroup->Add(new Sprite(glm::vec4(startX, startY, 0, 1), glm::vec2(30.0f, 30.0f), TextureMan->GetTexture("floor")/*, glm::vec2(1, 15)*/));
		}
		startX += 32.0f;
	}
	myLayer->Add(tileGroup);


	//Debug
	myPlayerTile = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.02)));
	myPlayerTile->Add(new Sprite(glm::vec4(0, 0, 0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("floor2")/*, glm::vec2(0, 15)*/));

	tileGroup->Add(myPlayerTile);
	myLayer->Add(tileGroup);
	//myDebugLayer->Add(myPlayerTile);
}
void Shooter::UpdatePlayer()
{
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
void Shooter::Tick()
{
	myFPSLabel->myText = std::to_string(getFPS()) + " fps";
	std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
}
void Shooter::Update()
{
	UpdatePlayer();
}
void Shooter::Render()
{
	myLayer->Render();
	//myDebugLayer->Render();
}
void Shooter::ProcessKeyBoard(int direction, float deltaTime)
{
	if (direction == GLFW_KEY_W)
		myPlayer->processKeyBoard(FORWARD, deltaTime,*myMap);
	if (direction == GLFW_KEY_S)
		myPlayer->processKeyBoard(BACKWARD, deltaTime, *myMap);
	if (direction == GLFW_KEY_A)
		myPlayer->processKeyBoard(LEFT, deltaTime, *myMap);
	if (direction == GLFW_KEY_D)
		myPlayer->processKeyBoard(RIGHT, deltaTime, *myMap);
	if (direction == GLFW_KEY_SPACE)
		myPlayer->processKeyBoard(UP, deltaTime, *myMap);
	if (direction == GLFW_KEY_LEFT_CONTROL)
		myPlayer->processKeyBoard(DOWN, deltaTime, *myMap);

	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myCamera.setPosition(-myPlayer->mPosition);
}
void Shooter::ProcessMouse(double xpos, double ypos, bool movement)
{
	myMouseMovement = movement;

	lastX = xpos;
	lastY = ypos;

	myCamera.setScreenPosition(glm::vec2(lastX, lastY));
}