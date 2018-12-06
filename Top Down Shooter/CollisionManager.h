#pragma once


#include <map>
#include <cassert>
#include <string>

#include "AABB.h"


#define CollisionMan CollisionManager::Instance()

class BaseEnemy;
class HeroEntity;
class BaseProjectileEntity;
class CollisionManager
{
private:
	typedef std::map<int, BaseEnemy*> EnemyMap;
	typedef std::map<int, BaseProjectileEntity*> ProjectileMap;
public:

	static CollisionManager* Instance();

	void RegisterEntity(BaseEnemy* entity);
	void RemoveEntity(BaseEnemy* entity);

	BaseEnemy* GetEntityFromID(int id) const;

	bool CheckSwordEnemyCollision(AABB* swordAABB);
	bool CheckSwordHeroCollisiion(BaseEnemy* enemy);
	bool TestAABBAABB(AABB* one, AABB* two);

	void RegisterProjectile(BaseProjectileEntity* projectile);
	void RemoveProjectile(BaseProjectileEntity* projectile);

	void RegisterPlayer(HeroEntity* hero);

	void Update();
private:

	CollisionManager() {}
	CollisionManager(const CollisionManager&);
	CollisionManager& operator=(const CollisionManager&);

	EnemyMap myEnemies;
	ProjectileMap myProjectiles;
	HeroEntity* myHero;
};