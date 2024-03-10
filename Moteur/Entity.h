#pragma once
#include "Incl.h"
#include "Mesh.h"
#include "Component.h"

class Camera;
class Entity
{
public:
	Entity();
	void Update();
	void SetPos(float x, float y, float z);
	Transform* GetTransform();

	template <class T>
	T* AttachComponent();
	template <class T>
	Component* GetComponent();
	template <class T>
	void DetachComponent();

	std::vector<Component*>& GetComponentsList();

	Camera* GetCurrCam();
	void SetCurrCam();



private:
	std::vector<Component*> _vComponentList;
	Transform* _pTransform;
	Camera* _pCurrCam;
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
Component* Entity::GetComponent()
{
	for (Component* pComponent : _vComponentList)
	{
		if (pComponent->GetID() == T::ID)
		{
			return pComponent;
		}
	}
	return nullptr;
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
