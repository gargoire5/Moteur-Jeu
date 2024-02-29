#include "Engine.h"
#include "Timer.h"
Engine::Engine(HINSTANCE hInstance)
{
	_hInstance = hInstance;
}

void Engine::Run()
{
	_pGraphics = new Graphics();
	_pGraphics->InitWindow(_hInstance);
	_pGraphics->InitDX();
	Timer* _cTime = new Timer();
	bool running = true;
	_cTime->Reset();
	_cTime->Start();
	while (running)
	{
		MSG msg = { 0 };

		// If there are Window messages then process them.
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			//_cTime->Tick(_pGraphics->_hWindow);
			if (msg.message == WM_QUIT)
			{
				_cTime->Stop();
				running = false;
				break;
			}
		}

		// Update (time, input, gameplay...)

		// Render
	}
}