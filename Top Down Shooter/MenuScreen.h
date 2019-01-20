#pragma once

class Layer;
class Label;
class Group;
class Sprite;

struct MenuScreen
{
	MenuScreen();
	~MenuScreen();

	void Render();
	void Update();

	bool IsDone();

	void Reset();

	Layer* myGameScreenLayer;
	Label* myBossAnnouncer;
	Group* bossAnnouncerGroup;
	Sprite* myMoonBackground;
	Sprite* myGraveyardBackground;
	float myAlphaGameLayer;
	float myAlphaDirection;
	bool myGameScreenDone;
};