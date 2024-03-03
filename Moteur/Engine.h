#pragma once
#include "Graphics.h"
#include "EntityManager.h"
class Engine
{
public:
	Engine();
	void Run();
	void Pause();
	void Resume();
	void Exit();

	EntityManager* GetEntityManager();

private:
	Graphics* _pGraphics;
	EntityManager* _pEntityManager;

};

