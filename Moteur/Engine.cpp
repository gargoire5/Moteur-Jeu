#include "Engine.h"
Engine::Engine()
{

}

void Engine::Run()
{
	_pEntityManager = new EntityManager();
	_pGraphics = new Graphics();
	_pGraphics->InitWindow();
	_pGraphics->InitDX();
	_pGraphics->OnResize();

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