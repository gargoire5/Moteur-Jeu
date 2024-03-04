#pragma once
#include "Incl.h"
#include "Mesh.h"
#include "Component.h"

class Entity
{
public:
	Entity(const char* cName);

	template <class T>
	T* AttachComponent(ComponentType iType);
	void UploadMesh(std::array<Vertex, 8> vertices, std::array<std::uint16_t, 36> indices);
	void DetachComponent(ComponentType iType);
	const char* GetName();

private:
	const char* _cName;
	std::vector<Component*> _vComponentList;
};

template <class T>
T* Entity::AttachComponent(ComponentType iType)
{
	for (Component* pComponent : _vComponentList)
	{
		if (pComponent->GetComponentType() == iType)
		{
			return nullptr;
		}
	}
	T* pComponent = new T();
	_vComponentList.push_back(pComponent);
	return pComponent;
}
