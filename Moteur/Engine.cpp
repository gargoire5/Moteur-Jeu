#include "Engine.h"
Engine::Engine(HINSTANCE hInstance)
{
	_hInstance = hInstance;
}

void Engine::Run()
{
	_pGraphics = new Graphics();
	_pGraphics->InitWindow(_hInstance);
	_pGraphics->InitDX();
}