#pragma once


#include <map>
#include <cassert>
#include <string>

#include "AABB.h"
#include "BaseEnemy.h"

#define CollisionMan CollisionManager::Instance()

class CollisionManager
{
private:
	typedef std::map<int, BaseEnemy*> EnemyMap;
public:

	static CollisionManager* Instance();

	void RegisterEntity(BaseEnemy* entity);
	void RemoveEntity(BaseEnemy* entity);

	BaseEnemy* GetEntityFromID(int id) const;

	void CheckSwordEnemyCollision(AABB* swordAABB);


	bool TestAABBAABB(AABB* one, AABB* two);

private:

	CollisionManager() {}
	CollisionManager(const CollisionManager&);
	CollisionManager& operator=(const CollisionManager&);

	EnemyMap myEnemies;
};