#include "Engine.h"
Engine::Engine(HINSTANCE hInstance)
{
	_hInstance = hInstance;
	_pEntityManager = new EntityManager();
}

void Engine::Run()
{
	_pGraphics = new Graphics();
	_pGraphics->InitWindow(_hInstance);
	_pGraphics->InitDX();

	bool running = true;
	while (running)
	{
		MSG msg = { 0 };

		// If there are Window messages then process them.
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				running = false;
				break;
			}
		}

		// Update (time, input, gameplay...)

		// Render
		_pGraphics->Draw();
	}
}

EntityManager* Engine::GetEntityManager()
{
	return _pEntityManager;
}