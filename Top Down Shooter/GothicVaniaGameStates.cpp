#include "GothicVaniaGameStates.h"
#include "GothicVania.h"
#include "GLFW\glfw3.h"
//------------------------------------------------------------------------methods for HeroFalling
GothicVaniaIntroState* GothicVaniaIntroState::Instance()
{
	static GothicVaniaIntroState instance;

	return &instance;
}


void GothicVaniaIntroState::Enter(GothicVania* game)
{
	
}

void GothicVaniaIntroState::Execute(GothicVania* game)
{
	game->UpdateGameScreen();
	if(game->myGameScreenDone)
	{
		game->GetFSM()->changeState(GothicVaniaPlayState::Instance());
	}
}

void GothicVaniaIntroState::Render(GothicVania* game)
{
	game->RenderGameScreen();
}

void GothicVaniaIntroState::Exit(GothicVania* game)
{

}

bool GothicVaniaIntroState::OnMessage(GothicVania* game, const Message& msg)
{
	return false;
}

bool GothicVaniaIntroState::HandleInput(GothicVania* game, int key, int action)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		game->myGameScreenDone = true;
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

}

void GothicVaniaMenuState::Execute(GothicVania* game)
{

}

void GothicVaniaMenuState::Exit(GothicVania* game)
{

}

bool GothicVaniaMenuState::OnMessage(GothicVania* game, const Message& msg)
{
	return false;
}

bool GothicVaniaMenuState::HandleInput(GothicVania* game, int key, int action)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{

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

}

void GothicVaniaPlayState::Execute(GothicVania* game)
{
	game->UpdateLevel();
}

void GothicVaniaPlayState::Render(GothicVania* game)
{
	game->RenderLevel();
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
	game->myLevels[0]->ProcessKeyBoard(key, 0, action);
	return true;
}