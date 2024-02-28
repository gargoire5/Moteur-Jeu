#pragma once
#include "Graphics.h"
class Engine
{
public:
	Engine(HINSTANCE hInstance);
	void Run();
	void Pause();
	void Resume();
	void Exit();

private:
	Graphics* _pGraphics;
	HINSTANCE _hInstance;

};

