#include "input.h"

Input::Input() {
    for (int i = 0; i < 256; ++i) {
        _vKeyList[i] = KeyState::Inactive;
    }
}
void Input::Update() 
{
    for (int i = 0; i < sizeof(_vKeyList); i++)
    {
        if (GetAsyncKeyState(i) & 0x01)
        {
            _vKeyList[i] = KeyState::Inactive;
        }
    }
}
KeyState Input::ListenToKey(int iVirtualKey)
{
    if (GetAsyncKeyState(iVirtualKey) & 0x8000)
    {
        if (_vKeyList[iVirtualKey] == KeyState::Inactive)
        {
            _vKeyList[iVirtualKey] = KeyState::Down;
            return _vKeyList[iVirtualKey];
        }
        else if (_vKeyList[iVirtualKey] == KeyState::Down)
        {
            _vKeyList[iVirtualKey] = KeyState::Held;
        }
    }
}
