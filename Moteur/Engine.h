#pragma once
//#include "Graphics.h"
#include "EntityManager.h"
#include "Graphics.h"
#include "input.h"

class Engine
{
public:
	static Engine* Instance();
	void Init();
	void Run();
	void Pause();
	void Resume();
	void Exit();
	void Update();

	EntityManager* GetEntityManager();
	Graphics* GetGraphics();

private:
	Engine();
	static Engine* _pInstance;
	Graphics* _pGraphics;
	EntityManager* _pEntityManager;
	Input* _pInput;
};

