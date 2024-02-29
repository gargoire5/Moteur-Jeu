#pragma once
#include "Graphics.h"
#include "input.h"

class Engine
{
public:
	Engine(HINSTANCE hInstance);
	void Run();
	void Pause();
	void Resume();
	void Exit();
	void Update();
	void DrawText();

private:

	Graphics* _pGraphics;
	HINSTANCE _hInstance;
	Input* _InputManager;
};

