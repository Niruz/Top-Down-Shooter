#include "MenuScreen.h"
#include "Layer.h"
#include "Label.h"
#include "Group.h"
#include "BatchRenderer.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include "TextureManager.h"

#include <glm/gtc/matrix_transform.hpp>
MenuScreen::MenuScreen()
{
	myGameScreenDone = false;
	//myGameScreenLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_FORWARD_SHADER), glm::ortho(-320.0f - 64, 320.0f + 64, -180.0f - 36, 180.0f + 36, -100.0f, 100.0f));
	myGameScreenLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_FORWARD_SHADER), glm::ortho(-320.0f - 64, 320.0f + 64, -180.0f - 36, 180.0f + 36, -100.0f, 100.0f));
	bossAnnouncerGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 40.8f)), 40.8);
	myBossAnnouncer = new Label("Press ENTER to start.", glm::vec4(-240.0f, 0.0f, 0, 1), "Adventurer48", glm::vec4(1, 1, 1, 1));
	myBossAnnouncer->SetColor(glm::vec4(1.0, 1.0, 1, 1));
	//Moon
	myMoonBackground = new Sprite(glm::vec4(0, 0, -99.0f, 1), glm::vec2(768.0f, 432.0f), TextureMan->GetTexture("bridgebackground"));
	myGameScreenLayer->Add(myMoonBackground);
	//Background
	myGraveyardBackground = new Sprite(glm::vec4(0, -108, -97.0f, 1), glm::vec2(768.0f, 216.0f), TextureMan->GetTexture("bridgemiddleground"));
	myGameScreenLayer->Add(myGraveyardBackground);

	//bossAnnouncerGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(640.0f, 360.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0)));
	bossAnnouncerGroup->Add(myBossAnnouncer);
	myGameScreenLayer->Add(bossAnnouncerGroup);
	myAlphaGameLayer = 1.0f;
	myAlphaDirection = 0.005f;
}
MenuScreen::~MenuScreen()
{
	delete myGameScreenLayer;
	delete myBossAnnouncer;
}
void MenuScreen::Reset()
{
	myGameScreenDone = false;
	myAlphaGameLayer = 0.0f;
	myAlphaDirection = 0.005f;
}
void MenuScreen::Update()
{
	//myAlphaGameLayer += myAlphaDirection;
	myGraveyardBackground->increaseUVAlongX(0.5 *0.002f);
}
void MenuScreen::Render()
{
	myGameScreenLayer->Render();
//	myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, myAlphaGameLayer));
}
bool MenuScreen::IsDone()
{
	return myGameScreenDone;
}