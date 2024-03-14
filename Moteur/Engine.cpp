#include "Engine.h"
#include "Graphics.h"
#include "Timer.h"
#include "input.h"
Engine* Engine::_pInstance;

Engine::Engine()
{
	_pEntityManager = nullptr;
	_pGraphics = nullptr;
	_pTimer = nullptr;
	_pInput = nullptr;
}

Engine* Engine::Instance()
{
	if (!_pInstance)
	{
		_pInstance = new Engine();
	}
	return _pInstance;
}
void Engine::Init()
{
	_pEntityManager = new EntityManager();
	_pGraphics = new Graphics();
	_pGraphics->InitWindow();
	_pGraphics->InitDX();
	_pGraphics->OnResize();
	_pTimer = new Timer();
	_pInput = new Input();
}
void Engine::Run()
{
	_pTimer->Reset();
	_pTimer->Start();
	while (_bIsRunning)
	{
		MSG msg = {0};

		// If there are Window messages then process them.
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				_pTimer->Stop();
				_bIsRunning = false;
				break;
			}
		}

		// Update (time, input, gameplay...)
		_pGraphics->Update();

		// Render
		_pGraphics->Draw();
		
	}
}

void Engine::Pause()
{
	_bPaused = true;
}

void Engine::Resume()
{
	_bPaused = false;
}

void Engine::Exit()
{
	_bIsRunning = false;
}

void Engine::SetMainCam(Camera* pCam)
{
	_pCurrCamera = pCam;
}

EntityManager* Engine::GetEntityManager()
{
	return _pEntityManager;
}
Graphics* Engine::GetGraphics()
{
	return _pGraphics;
}

Timer* Engine::GetTimer()
{
	return _pTimer;
}

Input* Engine::GetInput()
{
	return _pInput;
}

Camera* Engine::GetCurrCam()
{
	return _pCurrCamera;
}

void Engine::AddScript(Script* pScript)
{
	_vScriptList.push_back(pScript);
}

std::vector<Script*> Engine::GetScriptList()
{
	return _vScriptList;
}
