#include "EntityManager.h"
#include "Entity.h"

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
	_vEntityListToDestroy.push_back(pEntity);
}

void EntityManager::UpdateDestroy()
{
	for (int i = 0; i < _vEntityListToDestroy.size(); i++)
	{
		for (int j = 0; j < _vEntityList.size(); j++)
		{
			if (_vEntityListToDestroy[i] == _vEntityList[j])
			{
				_vEntityList.erase(_vEntityList.begin() + j);
				break;
			}
		}
		delete _vEntityListToDestroy[i];
	}
	_vEntityListToDestroy.clear();
}
