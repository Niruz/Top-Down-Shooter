#pragma once

#include "Level.h"

#include <map>
#include <cassert>
#include <string>

#define GameWorld World::Instance()

class World
{
private:
	typedef std::map<std::string, Level*> LevelMap;
public:

	static World* Instance();

private:

	LevelMap myLevelMap;

	World() {}
	World(const World&);
	World& operator=(const World&);
};