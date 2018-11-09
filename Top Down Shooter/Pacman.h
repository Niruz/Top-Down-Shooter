#pragma once
#include "Game.h"

class Shader;
class Layer;
class Label;
class Sprite;
class Group;
class TileMap;
class Player;
class PacmanEntity;
class Pacman : public Game
{
public:
	
	Pacman()
	{

	}
	~Pacman()
	{
		delete myLayer;
	}

	void Initialize() override;
	void Tick() override;
	void Update() override;
	void Render() override;

    void ProcessKeyBoard(int direction, float deltaTime) override;
private:

	Shader* myShader;
	Layer* myLayer;
	Sprite* mySprite;
	Label* myFPSLabel;
	Group* tileGroup;
	TileMap* myMap;
	//Player* myPlayer;
	PacmanEntity* myPlayer;
};



