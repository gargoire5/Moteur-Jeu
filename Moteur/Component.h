#pragma once
#include "Graphics.h"
#include "Shader.h"

class Component
{
public:
	Component();

	virtual int GetID() = 0;

	virtual void SetShader();
	virtual void PreRender();
	virtual void Render();

protected:
	Shader* _pShader;
};

