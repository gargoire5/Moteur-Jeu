#include "Engine.h"
#include "Graphics.h"
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
}
void Engine::Run()
{

	bool running = true;
	while (running)
	{
		MSG msg = { 0 };

		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				running = false;
				break;
			}
		}
		else
		{
			// Update (time, input, gameplay...)

			// Render
			_pGraphics->Draw();
		}
		
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