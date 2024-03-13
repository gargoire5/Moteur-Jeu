#pragma once
#include "Incl.h"
#include "Entity.h"
class EntityManager
{
public:
	EntityManager();
	Entity* CreateEntity();
	std::vector<Entity*> GetEntityList();
	void DeleteEntity(Entity* pEntity);
	void UpdateDestroy();

private:
	std::vector<Entity*> _vEntityList;
	std::vector<Entity*> _vEntityListToDestroy;

};

