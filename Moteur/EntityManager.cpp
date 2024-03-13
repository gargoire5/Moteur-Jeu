#include "EntityManager.h"

EntityManager::EntityManager()
{
	_vEntityList.clear();
}

Entity* EntityManager::CreateEntity()
{
	Entity* pEntity = new Entity();
	pEntity->SetCurrCam();
	_vEntityList.push_back(pEntity);
	return pEntity;
}

std::vector<Entity*> EntityManager::GetEntityList()
{
	return _vEntityList;
}

void EntityManager::DeleteEntity(Entity* pEntity)
{
	for (int i = 0; i < _vEntityList.size(); i++)
	{
		if (_vEntityList[i] == pEntity)
		{
			_vEntityList.erase(_vEntityList.begin() + i);
			
		}
	}
}

void EntityManager::UpdateDestroy()
{
	for (Entity* pEntity : _vEntityListToDestroy)
	{
		delete pEntity;
	}
	_vEntityList.clear();
}
