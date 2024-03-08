#pragma once
#include "Incl.h"
#include "Entity.h"
class EntityManager
{
public:
	EntityManager();
	Entity* CreateEntity(const char* cName);
	std::vector<Entity*> GetEntityList();
	Entity* GetEntityNamed(const char* cName);
	void DeleteEntity(const char* cName);

private:
	std::vector<Entity*> _vEntityList;

};

