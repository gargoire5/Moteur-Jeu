#include "EntityManager.h"

EntityManager::EntityManager()
{
	_vEntityList.clear();
}

Entity* EntityManager::CreateEntity(const char* cName)
{
	Entity* pEntity = new Entity(cName);
	_vEntityList.push_back(pEntity);
	return pEntity;
}

std::vector<Entity*> EntityManager::GetEntityList()
{
	return _vEntityList;
}

Entity* EntityManager::GetEntityNamed(const char* cName)
{
	for each (Entity* pEntity in _vEntityList)
	{
		if (pEntity->GetName() == cName)
		{
			return pEntity;
		}
	}
	return nullptr;
}

void EntityManager::DeleteEntity(const char* cName)
{
	for (int i = 0; i < sizeof(_vEntityList); i++)
	{
		if (_vEntityList[i]->GetName() == cName)
		{
			Entity* pEntity = _vEntityList[i];
			_vEntityList.erase(_vEntityList.begin() + i);
			delete pEntity;
		}
	}
}