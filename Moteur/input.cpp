#include "input.h"

Input::Input() {
    for (int i = 0; i < 256; ++i) {
        _vKeyList[i] = KeyState::None;
    }
}
void Input::Update() 
{
    for (int i = 0; i < 256; i++)
    {
        if (GetAsyncKeyState(i) < 0)
        {
            // push
            switch (_vKeyList[i])
            {
            case KeyState::None:
                _vKeyList[i] = KeyState::Down;
                break;
            case KeyState::Down:
                _vKeyList[i] = KeyState::Held;
                break;
            case KeyState::Up:
                _vKeyList[i] = KeyState::Down;
                break;
            }
        }
        else
        {
            switch (_vKeyList[i])
            {
            case KeyState::Held:
                _vKeyList[i] = KeyState::Up;
                break;
            case KeyState::Up:
                _vKeyList[i] = KeyState::None;
                break;
            case KeyState::Down:
                _vKeyList[i] = KeyState::Up;
                break;
            }
        }
    }
}

bool Input::IsKey(int iVirtualKey)
{
    return _vKeyList[iVirtualKey] == KeyState::Down || _vKeyList[iVirtualKey] == KeyState::Held;
}

bool Input::IsKeyDown(int iVirtualKey)
{
    return _vKeyList[iVirtualKey] == KeyState::Down;
}
