#pragma once
#include "Incl.h"
#include "Component.h"

class Entity
{
public:
	Entity();
	void AttachComponent(ComponentType iType);

private:
	std::vector<Component*> _vComponentList;
};

