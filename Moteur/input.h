#pragma once

#include <dinput.h>
#include "Graphics.h"

class Input
{
private:

	LPDIRECTINPUT8 _Input;
	LPDIRECTINPUTDEVICE8 _KeyboardDevice;
	char _KeyboardState[256];

public:

	Input(HWND _hWindow);

	~Input();

	void Update();

	bool IsKeyPressed(unsigned char keyCode) const;
};

