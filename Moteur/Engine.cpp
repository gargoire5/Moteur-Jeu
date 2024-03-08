#include "Engine.h"
#include "Graphics.h"
#include "Timer.h"
Engine* Engine::_pInstance;

Engine::Engine()
{
	_pEntityManager = nullptr;
	_pGraphics = nullptr;
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
	_pInput = new Input();
}
void Engine::Run()
{
	_cTimer = new Timer();
	bool running = true;
	_cTimer->Reset();
	_cTimer->Start();
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
				_cTimer->Stop();
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
	return _cTimer;
}
