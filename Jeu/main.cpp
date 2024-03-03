#include "../Moteur/Engine.h"

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

	Engine* pEngine = new Engine();
	pEngine->Run();


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