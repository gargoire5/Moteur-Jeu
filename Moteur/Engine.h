#pragma once
//#include "Graphics.h"
#include "EntityManager.h"
#include "Graphics.h"


class Camera;
class Input;
class Timer;
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
	void SetMainCam(Camera* pCam);

	EntityManager* GetEntityManager();
	Graphics* GetGraphics();
	Timer* GetTimer();
	Input* GetInput();
	Camera* GetCurrCam();

private:
	Engine();
	static Engine* _pInstance;
	Graphics* _pGraphics;
	Timer* _pTimer;
	EntityManager* _pEntityManager;
	Input* _pInput;
	Camera* _pCurrCamera;
};

