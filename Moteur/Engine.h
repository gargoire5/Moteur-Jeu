#pragma once
#include "Graphics.h"
#include "EntityManager.h"
class Engine
{
public:
	Engine(HINSTANCE hInstance);
	void Run();
	void Pause();
	void Resume();
	void Exit();

	EntityManager* GetEntityManager();

private:
	Graphics* _pGraphics;
	EntityManager* _pEntityManager;
	HINSTANCE _hInstance;

};

