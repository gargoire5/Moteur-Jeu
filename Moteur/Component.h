#pragma once
#include "Graphics.h"

class Shader;
class Entity;
class Component
{
public:
	Component();

	virtual int GetID() = 0;

	virtual void Update();
	virtual void SetShader();
	virtual void PreRender();
	virtual void Render();

	void SetEntity(Entity* pEntity);
	Entity* GetEntity();

protected:
	Shader* _pShader;
	Entity* _pEntity;
};
