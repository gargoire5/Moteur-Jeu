#include "../Moteur/Engine.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Engine* pEngine = new Engine(hInstance);
	pEngine->Run();

}

