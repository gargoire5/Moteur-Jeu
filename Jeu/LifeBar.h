#pragma once
#include "Incl.h"

class Entity;
class BoxColider;
class LifeBar
{
public:
	LifeBar();
	void Init();
	void Update();
	~LifeBar();
private:
	Entity* _pEntityLife;
	MeshRenderer* pLifeBar;
	float yaw = 0;
	float pitch = 0;
};
