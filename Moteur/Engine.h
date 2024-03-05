#pragma once
//#include "Graphics.h"
#include "EntityManager.h"
class Graphics;
class Engine
{
public:
	static Engine* Instance();
	void Init();
	void Run();
	void Pause();
	void Resume();
	void Exit();

	EntityManager* GetEntityManager();
	Graphics* GetGraphics();

private:
	Engine();
	static Engine* _pInstance;
	Graphics* _pGraphics;
	EntityManager* _pEntityManager;
};

