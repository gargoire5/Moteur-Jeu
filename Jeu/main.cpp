#include "../Moteur/Engine.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Engine* pEngine = new Engine(hInstance);
	pEngine->Run();

}

