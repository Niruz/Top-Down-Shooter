#include "GothicVaniaGameStates.h"
#include "GothicVania.h"
#include "GLFW\glfw3.h"
#include "SplashScreen.h"
#include "SoundManager.h"
//------------------------------------------------------------------------methods for HeroFalling
GothicVaniaIntroState* GothicVaniaIntroState::Instance()
{
	static GothicVaniaIntroState instance;

	return &instance;
}


void GothicVaniaIntroState::Enter(GothicVania* game)
{
	game->myRenderingSplashScreen = true;
	game->mySplashScreen->Reset();
	SoundMan->GetSoundEngine()->play2D("Audio/rpg_village02_loop.wav", GL_TRUE);
}

void GothicVaniaIntroState::Execute(GothicVania* game)
{
	game->UpdateGameScreen();
//	game->RenderGameScreen();
	//game->myGameScreenDone = true;
//	game->mySplashScreen->myGameScreenDone = true;
	if(game->mySplashScreen->IsDone())
	{
		game->GetFSM()->changeState(GothicVaniaMenuState::Instance());
	}
}
void GothicVaniaIntroState::Exit(GothicVania* game)
{
	game->myRenderingSplashScreen = false;
}

bool GothicVaniaIntroState::OnMessage(GothicVania* game, const Message& msg)
{
	return false;
}

bool GothicVaniaIntroState::HandleInput(GothicVania* game, int key, int action)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		game->mySplashScreen->myGameScreenDone = true;
		game->myRenderingSplashScreen = false;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{

	}
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
GothicVaniaMenuState* GothicVaniaMenuState::Instance()
{
	static GothicVaniaMenuState instance;

	return &instance;
}


void GothicVaniaMenuState::Enter(GothicVania* game)
{
	game->myRenderingMenuScreen = true;
	game->mySplashScreen->Reset();
	
}

void GothicVaniaMenuState::Execute(GothicVania* game)
{
	game->UpdateMenuScreen();
}

void GothicVaniaMenuState::Exit(GothicVania* game)
{
	game->myRenderingMenuScreen = false;
}

bool GothicVaniaMenuState::OnMessage(GothicVania* game, const Message& msg)
{
	return false;
}

bool GothicVaniaMenuState::HandleInput(GothicVania* game, int key, int action)
{
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		game->GetFSM()->changeState(GothicVaniaPlayState::Instance());
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{

	}
	return true;
}
//------------------------------------------------------------------------methods for HeroFalling
GothicVaniaPlayState* GothicVaniaPlayState::Instance()
{
	static GothicVaniaPlayState instance;

	return &instance;
}


void GothicVaniaPlayState::Enter(GothicVania* game)
{
	game->activeLevel = 0;
}

void GothicVaniaPlayState::Execute(GothicVania* game)
{
	game->UpdateLevel();
}


void GothicVaniaPlayState::Exit(GothicVania* game)
{

}

bool GothicVaniaPlayState::OnMessage(GothicVania* game, const Message& msg)
{
	return false;
}

bool GothicVaniaPlayState::HandleInput(GothicVania* game, int key, int action)
{
	game->myLevels[game->activeLevel]->ProcessKeyBoard(key, 0, action);
	return true;
}