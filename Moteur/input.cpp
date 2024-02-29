#include "input.h"

Input::Input(HWND _hWindow) : _Input(nullptr), _KeyboardDevice(nullptr) {

    // Initialisation de DirectInput
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_Input, NULL);

    // Initialisation du clavier
    _Input->CreateDevice(GUID_SysKeyboard, &_KeyboardDevice, NULL);
    _KeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    _KeyboardDevice->SetCooperativeLevel(_hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    _KeyboardDevice->Acquire();
}


Input::~Input() {

    if (_KeyboardDevice != nullptr) {
        _KeyboardDevice->Unacquire();
        _KeyboardDevice->Release();
    }
    if (_Input != nullptr) {
        _Input->Release();
    }
}


void Input::Update() {

    // Code de mise à jour des événements d'entrée
    HRESULT hr;

    hr = _KeyboardDevice->GetDeviceState(sizeof(_KeyboardState), (LPVOID)&_KeyboardState);
    if (FAILED(hr)) {
        // Si la perte de focus ou autre problème survient, réacquérir le clavier
        if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)) {
            _KeyboardDevice->Acquire();
        }
    }
}


bool Input::IsKeyPressed(unsigned char keyCode) const {

    return (_KeyboardState[keyCode] & 0x80) != 0;
}

