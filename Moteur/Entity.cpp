#include "Entity.h"

Entity::Entity(const char* cName)
{}


void Entity::DetachComponent(ComponentType iType)
{
	for (int i = 0; i < sizeof(_vComponentList); i++)
	{
		if (_vComponentList[i]->GetComponentType() == iType)
		{
			Component* pComponent = _vComponentList[i];
			_vComponentList.erase(_vComponentList.begin() + i);
			delete pComponent;
		}
	}
}

const char* Entity::GetName()
{
	return _cName;
}