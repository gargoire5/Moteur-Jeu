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
			Entity* pEntity = _vEntityList[i];
			_vEntityList.erase(_vEntityList.begin() + i);
			delete pEntity;
		}
	}
}