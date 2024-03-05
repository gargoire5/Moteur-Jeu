#pragma once
#include "Incl.h"
#include "Mesh.h"
#include "Component.h"

class Entity
{
public:
	Entity(const char* cName);

	template <class T>
	T* AttachComponent();

	template <class T>
	void DetachComponent();

	const char* GetName();
	std::vector<Component*> GetComponents();



private:
	const char* _cName;
	std::vector<Component*> _vComponentList;
};

template <class T>
T* Entity::AttachComponent()
{
	
	for (Component* pComponent : _vComponentList)
	{
		if (pComponent->GetID() == T::ID)
		{
			return nullptr;
		}
	}
	T* pComponent = new T();
	_vComponentList.push_back(pComponent);
	return pComponent;
}

template <class T>
void Entity::DetachComponent()
{
	for (Component* pComponent : _vComponentList)
	{
		if (pComponent->GetID() == T::ID)
		{
			Component* pComponent = _vComponentList[i];
			_vComponentList.erase(_vComponentList.begin() + i);
			delete pComponent;
		}
	}
}
