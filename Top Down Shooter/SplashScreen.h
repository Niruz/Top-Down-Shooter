#pragma once

class Layer;
class Label;
class Group;

struct SplashScreen
{
	SplashScreen();
	~SplashScreen();

	void Render();
	void Update();

	bool IsDone();

	void Reset();

	Layer* myGameScreenLayer;
	Label* myBossAnnouncer;
	Group* bossAnnouncerGroup;
	float myAlphaGameLayer;
	float myAlphaDirection;
	bool myGameScreenDone;
};