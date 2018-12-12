
#include "MessageDispatcher.h"
#include "CollisionManager.h"
#include <cassert>

#include "Messages.h"
#include "BaseEnemy.h"
#include "HeroEntity.h"
#include "BaseProjectileEntity.h"
CollisionManager* CollisionManager::Instance()
{
	static CollisionManager instance;

	return &instance;
}

BaseEnemy* CollisionManager::GetEntityFromID(int id)const
{
	//find the entity
	EnemyMap::const_iterator ent = myEnemies.find(id);

	//assert that the entity is a member of the map
	assert((ent != myEnemies.end()) && "<EntityManager::getEntityFromID>: invalid ID");

	return ent->second;
}

void CollisionManager::RemoveEntity(BaseEnemy* entity)
{
	myEnemies.erase(myEnemies.find(entity->GetID()));
}

void CollisionManager::RegisterEntity(BaseEnemy* NewEntity)
{
	myEnemies.insert(std::make_pair(NewEntity->GetID(), NewEntity));
}
bool CollisionManager::CheckSwordEnemyCollision(AABB* swordAABB)
{
	bool foundCollision = false;
	std::map<int, BaseEnemy*>::iterator it = myEnemies.begin();

	while(it != myEnemies.end())
	{
		int enemyID = it->first;
		BaseEnemy* enemy = it->second;
		if (enemy->myIsActive)
		{
			if (TestAABBAABB(swordAABB, enemy->myAABB))
			{
				foundCollision = true;
				MessageMan->dispatchMessage(0, 555, enemy->GetID(), Msg_TakeDamage, 0);
				break;
			}
		}



		it++;
	}
	return foundCollision;
}
bool CollisionManager::CheckSwordHeroCollisiion(BaseEnemy* enemy)
{
	int enemyID = enemy->GetID();
	if (TestAABBAABB(myHero->myAABB, enemy->myHitAABB))
	{
		MessageMan->dispatchMessage(0, enemy->GetID(), myHero->GetID(), Msg_TakeDamage, 0);
		return true;
	}
	return false;
}
void CollisionManager::Update()
{
	if (myProjectiles.size() != 0)
	{
		std::map<int, BaseProjectileEntity*>::iterator it = myProjectiles.begin();

		while (it != myProjectiles.end())
		{
			int enemyID = it->first;
			BaseProjectileEntity* enemy = it->second;

			if (TestAABBAABB(myHero->myAABB, enemy->myAABB))
			{
				MessageMan->dispatchMessage(0, 555, myHero->GetID(), Msg_TakeDamage, 0);
				enemy->MarkForDeletion();
				break;
			}


			it++;
		}
	}

	if(myHeroProjectiles.size() != 0)
	{
		std::map<int, BaseProjectileEntity*>::iterator it = myHeroProjectiles.begin();

		while (it != myHeroProjectiles.end())
		{
			int projectileID = it->first;
			BaseProjectileEntity* projectile = it->second;
			


			std::map<int, BaseEnemy*>::iterator iter = myEnemies.begin();

			while (iter != myEnemies.end())
			{
				int enemyID = iter->first;
				BaseEnemy* enemy = iter->second;
				if (enemy->myIsActive)
				{
					if (TestAABBAABB(projectile->myAABB, enemy->myAABB))
					{
						MessageMan->dispatchMessage(0, 555, enemy->GetID(), Msg_TakeDamage, 0);
						projectile->MarkForDeletion();
						break;
					}
				}



				iter++;
			}



			it++;
		}
	}
}
bool CollisionManager::TestAABBAABB(AABB* one, AABB* two)
{
	if (std::fabs(one->myOrigin[0] - two->myOrigin[0]) > (one->halfX + two->halfX)) return false;
	if (std::fabs(one->myOrigin[1] - two->myOrigin[1]) > (one->halfY + two->halfY)) return false;
	return true;
}

void CollisionManager::RegisterProjectile(BaseProjectileEntity* projectile)
{
	myProjectiles.insert(std::make_pair(projectile->GetID(), projectile));
}
void CollisionManager::RemoveProjectile(BaseProjectileEntity* projectile)
{
	myProjectiles.erase(myProjectiles.find(projectile->GetID()));
}

void CollisionManager::RegisterHeroProjectile(BaseProjectileEntity* projectile)
{
	myHeroProjectiles.insert(std::make_pair(projectile->GetID(), projectile));
}
void CollisionManager::RemoveHeroProjectile(BaseProjectileEntity* projectile)
{
	myHeroProjectiles.erase(myHeroProjectiles.find(projectile->GetID()));
}


void CollisionManager::RegisterPlayer(HeroEntity* hero)
{
	myHero = hero;
}