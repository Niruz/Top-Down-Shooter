#include "Pacman.h"
#include "ShaderManager.h"
#include "Layer.h"
#include "Label.h"
#include "Sprite.h"
#include "BatchRenderer.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Group.h"
#include "TileMap.h"


#include <iostream>

void Pacman::Initialize()
{
	myShader = ShaderMan->getShader(SIMPLE_FORWARD_SHADER);
	myLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-960.0f, 960.0f, -540.0f, 540.0f, -1.0f, 1.0f));
	//myLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-1280.0f, 1280.0f, -720.0f, 720.0f, -1.0f, 1.0f));
	//myLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f));
	mySprite = new Sprite(glm::vec4(0.0f, 0.0f, 0.1f, 1), glm::vec2(512, 512), TextureMan->GetTexture("atlas"));
	mySprite->SetUVs(0, 15);

	//myLayer->Add(mySprite);

	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-580, 340, 0.8)));
	myFPSLabel = new Label("", glm::vec4(-55, -10, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(myFPSLabel);

	myLayer->Add(fpsGroup);
	myMap = new TileMap("Levels/pacman.level");

	std::vector<Tile*> map = myMap->GetMap();
	tileGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)));
	float startX = -32.0f * 14.0f;
	float startY = 32.0f * 16;
	for (int i = 0; i < map.size(); i++)
	{
		if (i % 28 == 0)
		{
			startY -= 32.0f;
			startX = -32.0f*14.0f;
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
}
void Pacman::Tick()
{
	myFPSLabel->myText = std::to_string(getFPS()) + " fps";
	std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
}
void Pacman::Update()
{

}
void Pacman::Render()
{
	myLayer->Render();
}
void Pacman::ProcessKeyBoard(int direction, float deltaTime)
{
	GLfloat velocity = 200.5f * deltaTime;
	if(direction == 0)
		mySprite->myPosition += glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)*velocity;
	else if(direction == 1)
		mySprite->myPosition -= glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)*velocity;
	else if(direction == 2)
		mySprite->myPosition -= glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)*velocity;
	else if(direction == 3)
		mySprite->myPosition += glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)*velocity;
	else
	{

	}
}