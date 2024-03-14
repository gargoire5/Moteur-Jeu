#pragma once
//#include "Graphics.h"
#include "EntityManager.h"
#include "Graphics.h"

class Script;
class Entity;
class Input;
class Timer;
class Player;
class Engine
{
public:
	static Engine* Instance();
	void Init();
	void Run();
	void Pause();
	void Resume();
	void Exit();

	void SetMainCam(Camera* pCam);

	EntityManager* GetEntityManager();
	Graphics* GetGraphics();
	Timer* GetTimer();
	Input* GetInput();
	Camera* GetCurrCam();

	void AddScript(Script* pScript);
	std::vector<Script*> GetScriptList();

	bool _bSlowMotion = false;
	bool _bPaused = false;

private:
	Engine();
	static Engine* _pInstance;
	Graphics* _pGraphics;
	Timer* _pTimer;
	EntityManager* _pEntityManager;
	Input* _pInput;
	Camera* _pCurrCamera;
	std::vector<Script*> _vScriptList;
	bool _bIsRunning = true;
};

