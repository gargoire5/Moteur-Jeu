#pragma once

typedef enum ComponentType
{
	CompoMesh,
	CompoBoxGeo
};

class Component
{
public:
	Component();
	Component(ComponentType iType);
	ComponentType GetComponentType();
	//virtual void SetComponent();

private:
	ComponentType _iType;
};

