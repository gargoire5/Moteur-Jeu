#include "input.h"

Input::Input() {

    for (int i = 0; i < 256; ++i) {
        _keyStates[i] = KeyState::None;
    }
}

void Input::Update() {

    for (auto& pair : _keyStates) {
        prevKeyStates[pair.first] = pair.second;
    }

    for (auto& pair : _keyStates) {

        bool isKeyDown = (GetAsyncKeyState(pair.first) & 0x8000);
        bool wasKeyDown = (pair.second == KeyState::Down || pair.second == KeyState::Held);

        if (isKeyDown) {
            if (wasKeyDown) {
                pair.second = KeyState::Held;
            }
            else {
                pair.second = KeyState::Down;
            }
        }
        else {
            if (wasKeyDown) {
                pair.second = KeyState::Up;
            }
            else {
                pair.second = KeyState::Inactive;
            }
        }
    }

    for (auto& pair : _keyStates) {

        wchar_t character;
        UINT scanCode = MapVirtualKey(pair.first, MAPVK_VK_TO_CHAR);
        if (scanCode != 0) {
            character = static_cast<wchar_t>(scanCode);
        }
        else {
            character = L' ';
        }

        if (pair.second == KeyState::Down) {
            std::wstring message = L"Touche enfoncée : ";
            message += character;
            OutputDebugString(message.c_str());
            OutputDebugString(L"\n");
        }
        else if (pair.second == KeyState::Up) {
            std::wstring message = L"Touche relâchée : ";
            message += character;
            OutputDebugString(message.c_str());
            OutputDebugString(L"\n");
        }
        else if (pair.second == KeyState::Held && prevKeyStates[pair.first] != KeyState::Held) {
            std::wstring message = L"Touche maintenue : ";
            message += character;
            OutputDebugString(message.c_str());
            OutputDebugString(L"\n");
        }
    }
}

KeyState Input::GetKeyState(int virtualKeyCode) const {
    auto it = _keyStates.find(virtualKeyCode);
    if (it != _keyStates.end()) {
        return it->second;
    }
    else {
        return KeyState::None;
    }
}

bool Input::IsKeyDown(int virtualKeyCode) const {
    return GetKeyState(virtualKeyCode) == KeyState::Down;
}

bool Input::IsKeyUp(int virtualKeyCode) const {
    return GetKeyState(virtualKeyCode) == KeyState::Up;
}

bool Input::IsKeyHeld(int virtualKeyCode) const {
    return GetKeyState(virtualKeyCode) == KeyState::Held;
}

int Input::GetKeyPressed() const {
    for (const auto& pair : _keyStates) {
        if (pair.second == KeyState::Down) {
            int scanCode = MapVirtualKey(pair.first, MAPVK_VK_TO_CHAR);
            return (scanCode == 0) ? pair.first : scanCode;
        }
    }
    return -1;
}




