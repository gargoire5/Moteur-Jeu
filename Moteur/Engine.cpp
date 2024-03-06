#include "Engine.h"
#include <string> 


Engine::Engine(HINSTANCE hInstance)
{
	_hInstance = hInstance;
}

void Engine::Run()
{

	_pGraphics = new Graphics();
	_pGraphics->InitWindow(_hInstance);
	_pGraphics->InitDX();
	_pInput = new Input();


	bool running = true;
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
				running = false;
				break;
			}
		}

		// Update (time, input, gameplay...)

		_pInput->Update();


		if (_pInput->IsKeyDown(VK_ESCAPE))
		{
			OutputDebugString( L"Touche enfoncée \n");
		}
		if (_pInput->IsKeyUp(VK_ESCAPE))
		{
			OutputDebugString(L"Touche relaché \n");
		}
		if (_pInput->IsKeyHeld(VK_ESCAPE))
		{
			OutputDebugString(L"Touche maintenu\n");
		}

		// Render

		
	}
}






