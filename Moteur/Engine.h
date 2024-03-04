#pragma once
#include "Graphics.h"
#include "EntityManager.h"
class Engine
{
public:
	static Engine* Instance();
	void Run();
	void Pause();
	void Resume();
	void Exit();

	EntityManager* GetEntityManager();

private:
	Engine();
	static Engine* _pInstance;
	Graphics* _pGraphics;
	EntityManager* _pEntityManager;

};

