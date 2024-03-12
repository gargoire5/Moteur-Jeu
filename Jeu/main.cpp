#include "Game.h"
#include "../Moteur/Engine.h"
#include "../Moteur/MeshRenderer.h"
#include "../Moteur/Camera.h"
#include "../Moteur/input.h"
#include "../Moteur/timer.h"
#include "MovementScript.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	//#ifdef _DEBUG
	//	_CrtMemState memStateInit;
	//	_CrtMemCheckpoint(&memStateInit);
	//#endif
		//------------------------------------------------------

	Game::Instance()->Run();

	//------------------------------------------------------
//#ifdef _DEBUG
//	_CrtMemState memStateEnd, memStateDiff;
//	_CrtMemCheckpoint(&memStateEnd);
//	if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
//	{
//		MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
//	}
//#endif
}
