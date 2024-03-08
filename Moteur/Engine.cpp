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
#include "../Moteur/MeshRenderer.h"
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
	bool running = true;
	_pTimer->Reset();
	_pTimer->Start();
	while (running)
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
				running = false;
				break;
			}
		}

		// Update (time, input, gameplay...)
		_pGraphics->Update();

		// Render
		_pGraphics->Draw();
		
	}
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
