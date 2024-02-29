#include "Engine.h"
#include <Windows.h> 
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

	_InputManager = new Input(_pGraphics->_hWindow);

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

		Update();


		// Render

		
	}
}

void Engine::Update()
{
	_InputManager->Update();


	if (_InputManager->IsKeyPressed(DIKEYBOARD_UP)) {
		std::cout << "D�placer vers le haut" << std::endl;
	}
	if (_InputManager->IsKeyPressed(DIK_DOWN)) {
		std::cout << "D�placer vers le bas" << std::endl;
	}
	if (_InputManager->IsKeyPressed(DIK_LEFT)) {
		std::cout << "D�placer vers la gauche" << std::endl;
	}
	if (_InputManager->IsKeyPressed(DIK_RIGHT)) {
		std::cout << "D�placer vers la droite" << std::endl;
	}
}





