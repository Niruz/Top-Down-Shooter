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

#include <iostream>

void Shooter::Initialize()
{
	myShader = ShaderMan->getShader(SIMPLE_FORWARD_SHADER);
	myLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f));
	mySprite = new Sprite(glm::vec4(0.0f, 0.0f, 0.1f, 1), glm::vec2(512, 512), TextureMan->GetTexture("atlas"));
	mySprite->SetUVs(0, 15);

	myLayer->Add(mySprite);

	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-580, 340, 0.8)));
	myFPSLabel = new Label("", glm::vec4(-55, -10, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(myFPSLabel);

	myLayer->Add(fpsGroup);

	myMap = new TileMap("Levels/test3.level");

	myMap->printMap();

	std::vector<Tile*> myPath3;
	myMap->GetPath(1, 1, 18, 10, myPath3);

	myMap->printPath(myPath3);

	std::vector<Tile*> map = myMap->GetMap();
}
void Shooter::Tick()
{
	myFPSLabel->myText = std::to_string(getFPS()) + " fps";
	std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
}
void Shooter::Update()
{

}
void Shooter::Render()
{
	myLayer->Render();
}
void Shooter::ProcessKeyBoard(int direction, float deltaTime)
{
	GLfloat velocity = 200.5f * deltaTime;
	if (direction == 0)
		mySprite->myPosition += glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)*velocity;
	else if (direction == 1)
		mySprite->myPosition -= glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)*velocity;
	else if (direction == 2)
		mySprite->myPosition -= glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)*velocity;
	else if (direction == 3)
		mySprite->myPosition += glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)*velocity;
	else
	{

	}
}