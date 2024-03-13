#pragma once
#include <unordered_map>
#include "Incl.h"

enum class KeyState {
    None,
    Down,
    Up,
    Held,
};

struct KeyMsg
{
    char KeyPressed;
    KeyState State;
};
struct KeyWithState
{
    int KeyPressed;
    KeyState State;
};

class Input {
public:

    Input();
    void Update();

    bool IsKey(int iVirtualKey);
    bool IsKeyDown(int iVirtualKey);

private:

    KeyState _vKeyList[256];
};

