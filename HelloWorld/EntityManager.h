#pragma once
#include<map>
#include"BaseGameEntity.h"
struct EntityComparator
{
	bool operator()(const std::shared_ptr<BaseGameEntity>& lhs, const std::shared_ptr<BaseGameEntity>& rhs) const;
	
};
class EntityManager
{
private:
	typedef std::map<int, std::shared_ptr<BaseGameEntity>> EntityMap;

private:
	EntityMap entityMap;
	
public:

	class EntityManager() {};
	static std::shared_ptr<EntityManager> instance();
	void registerEntity(std::shared_ptr<BaseGameEntity> NewEntity);
	std::shared_ptr<BaseGameEntity> getEntityFromID(int ID);
	void removeEntity(std::shared_ptr<BaseGameEntity> spEntity);
	EntityMap getAllEntities();
};
#define Entity_Manager EntityManager::instance() // provide easy acess to instance of entityManager