#include "SplashScreen.h"
#include "Layer.h"
#include "Label.h"
#include "Group.h"
#include "BatchRenderer.h"
#include "ShaderManager.h"
#include "Sprite.h"

#include <glm/gtc/matrix_transform.hpp>
SplashScreen::SplashScreen()
{
	myGameScreenDone = false;
	myGameScreenLayer = new Layer(new BatchRenderer(), ShaderMan->getShader(SIMPLE_FORWARD_SHADER), glm::ortho(-320.0f, 320.0f, -180.0f, 180.0f, -10.0f, 10.0f));

	bossAnnouncerGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.8f)));
	myBossAnnouncer = new Label("What The Moon Brings", glm::vec4(-240.0f, 0.0f, 0, 1), "Adventurer48", glm::vec4(1, 1, 1, 1));
	myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, 0));
	bossAnnouncerGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(640.0f, 360.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0)));
	bossAnnouncerGroup->Add(myBossAnnouncer);
	myGameScreenLayer->Add(bossAnnouncerGroup);
	myAlphaGameLayer = 0.0f;
	myAlphaDirection = 0.005f;
}
SplashScreen::~SplashScreen()
{
	delete myGameScreenLayer;
	delete myBossAnnouncer;
}
void SplashScreen::Reset()
{
	myGameScreenDone = false;
	myAlphaGameLayer = 0.0f;
	myAlphaDirection = 0.005f;
}
void SplashScreen::Update()
{
	myAlphaGameLayer += myAlphaDirection;
	if (myAlphaGameLayer >= 1.0f)
	{
		myAlphaGameLayer = 1.0f;
		myAlphaDirection = -0.005f;
	}
	if (myAlphaDirection < 0.0f && myAlphaGameLayer <= 0.0f && !myGameScreenDone)
	{
		myGameScreenDone = true;
	}
}
void SplashScreen::Render()
{
	myGameScreenLayer->Render();
	myBossAnnouncer->SetColor(glm::vec4(1, 1, 1, myAlphaGameLayer));
}
bool SplashScreen::IsDone()
{
	return myGameScreenDone;
}