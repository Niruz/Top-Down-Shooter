#include "World.h"
#include "Level.h"

World* World::Instance()
{
	static World instance;

	return &instance;
}

Level* World::GetLevelFromName(const std::string& name)const
{
	//find the entity
	LevelMap::const_iterator ent = myLevelMap.find(name);

	//assert that the entity is a member of the map
	assert((ent != myLevelMap.end()) && "<EntityManager::getEntityFromID>: invalid ID");

	return ent->second;
}

void World::RemoveLevel(Level* level)
{
	myLevelMap.erase(myLevelMap.find(level->GetName()));
}

void World::RegisterLevel(Level* level)
{
	myLevelMap.insert(std::make_pair(level->GetName(), level));
}
