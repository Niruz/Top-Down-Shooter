#include "CollisionManager.h"
#include <cassert>
#include "MessageDispatcher.h"
#include "Messages.h"


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
void CollisionManager::CheckSwordEnemyCollision(AABB* swordAABB)
{
	std::map<int, BaseEnemy*>::iterator it = myEnemies.begin();

	while(it != myEnemies.end())
	{
		int enemyID = it->first;
		BaseEnemy* enemy = it->second;

		if(TestAABBAABB(swordAABB, enemy->myAABB))
		{
			MessageMan->dispatchMessage(0, 555, enemy->GetID(), Msg_TakeDamage, 0);
			break;
		}


		it++;
	}
}
bool CollisionManager::TestAABBAABB(AABB* one, AABB* two)
{
	if (std::fabs(one->myOrigin[0] - two->myOrigin[0]) > (one->halfX + two->halfX)) return false;
	if (std::fabs(one->myOrigin[1] - two->myOrigin[1]) > (one->halfY + two->halfY)) return false;
	return true;
}