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

private:
	std::vector<Entity*> _vEntityList;

};

