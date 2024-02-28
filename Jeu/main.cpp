#include "../Moteur/Engine.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Engine* pEngine = new Engine(hInstance);
	pEngine->Run();

	while (true)
	{
		MSG msg = { 0 };

		while (msg.message != WM_QUIT)
		{
			// If there are Window messages then process them.
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}