#include "EntityManager.h"
#include "Entity.h"
#include "BaseProjectileEntity.h"
#include "CollisionManager.h"
#include "Effect.h"
#include "BaseEnemy.h"
EntityManager* EntityManager::Instance()
{
	static EntityManager instance;

	return &instance;
}

Entity* EntityManager::getEntityFromID(int id)const
{
	//find the entity
	EntityMap::const_iterator ent = mEntityMap.find(id);

	//assert that the entity is a member of the map
	assert((ent != mEntityMap.end()) && "<EntityManager::getEntityFromID>: invalid ID");

	return ent->second;
}

void EntityManager::removeEntity(Entity* entity)
{
	mEntityMap.erase(mEntityMap.find(entity->GetID()));
}

void EntityManager::registerEntity(Entity* NewEntity)
{
	mEntityMap.insert(std::make_pair(NewEntity->GetID(), NewEntity));
}

void EntityManager::DeleteAllEntities()
{
	for (auto iterator : mEntityMap)
		delete iterator.second;
	mEntityMap.clear();
}

void EntityManager::Update()
{
	std::map<int, Entity*>::iterator it = mEntityMap.begin();

	while (it != mEntityMap.end())
	{
		Entity* entity = it->second;
		if(entity->GetMarkedForDeletion())
		{
			if (dynamic_cast<BaseProjectileEntity*>(entity))
			{
				if ((dynamic_cast<BaseProjectileEntity*>(entity)->isHeroProjectile))
					CollisionMan->RemoveHeroProjectile((BaseProjectileEntity*)entity);
				else
					CollisionMan->RemoveProjectile((BaseProjectileEntity*)entity);
				
				delete entity;
				it = mEntityMap.erase(it);
			}
			else if (dynamic_cast<Effect*>(entity))
			{
				delete entity;
				it = mEntityMap.erase(it);
			}
			else if (dynamic_cast<BaseEnemy*>(entity))
			{
			/*	CollisionMan->RemoveEntity((BaseEnemy*)entity);
				delete entity;
				it = mEntityMap.erase(it);*/
				it++;
			}
		}
		else
		{
			entity->Update();
			it++;
		}
		

		
	}
}
