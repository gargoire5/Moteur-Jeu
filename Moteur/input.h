#pragma once
#include <unordered_map>
#include "Incl.h"

enum class KeyState {
    None,
    Down,
    Up,
    Held,
    Inactive
};

class Input {
public:

    Input();
    void Update();
    KeyState GetKeyState(int virtualKeyCode) const;
    bool IsKeyDown(int virtualKeyCode) const;
    bool IsKeyUp(int virtualKeyCode) const;
    bool IsKeyHeld(int virtualKeyCode) const;
    int GetKeyPressed() const;

private:

    std::unordered_map<int, KeyState> _keyStates;
    std::unordered_map<int, KeyState> prevKeyStates;

};

