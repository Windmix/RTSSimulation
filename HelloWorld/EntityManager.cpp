#include "EntityManager.h"
#include <iostream>

std::shared_ptr<EntityManager> EntityManager::instance()
{
	static std::shared_ptr<EntityManager> entityManager = std::make_shared<EntityManager>();
	return entityManager;
}

void EntityManager::registerEntity(std::shared_ptr<BaseGameEntity> NewEntity)
{
	entityMap[NewEntity->getEntityID()] = NewEntity;
}

std::shared_ptr<BaseGameEntity> EntityManager::getEntityFromID(int ID)
{

	auto iterator = entityMap.find(ID);
	if (iterator != entityMap.end())
	{
		return iterator->second;
	}

	return nullptr;
}

void EntityManager::removeEntity(std::shared_ptr<BaseGameEntity> spEntity)
{
	auto iterator = entityMap.find(spEntity->getEntityID());
	if (iterator != entityMap.end())
	{
		entityMap.erase(iterator);
	}
	else
	{
		std::cout << "selected entity does not excist! " << std::endl;
	}

}

EntityManager::EntityMap EntityManager::getAllEntities()
{
	return this->entityMap;
}

bool EntityComparator::operator()(const std::shared_ptr<BaseGameEntity>& lhs, const std::shared_ptr<BaseGameEntity>& rhs) const
{
	return lhs->getEntityID() < rhs->getEntityID();  // Compare based on EntityID
}
