#include "input.h"

std::unordered_map<int, bool> keyStates;


Input::Input()
{
}

void Input::InitializeKeyStates() {
	// Initialiser l'état des touches à false.
	keyStates[VK_ESCAPE] = false;
	keyStates['Z'] = false;
	keyStates['Q'] = false;
	keyStates['S'] = false;
	keyStates['D'] = false;
}

void Input::CheckKeyboardState()
{

	for (auto& pair : keyStates) {

		bool isKeyDown = (GetAsyncKeyState(pair.first) & 0x8000);

		if (isKeyDown && !pair.second) {
			pair.second = true;
			if (pair.first == VK_ESCAPE) {
				PostQuitMessage(0);
			}
			else {

				switch (pair.first) {
				case 'Z':
					OutputDebugString(L"Touche 'Z' enfoncée : Déplacement vers le haut.\n");
					break;
				case 'Q':
					OutputDebugString(L"Touche 'Q' enfoncée : Déplacement vers la gauche.\n");
					break;
				case 'S':
					OutputDebugString(L"Touche 'S' enfoncée : Déplacement vers le bas.\n");
					break;
				case 'D':
					OutputDebugString(L"Touche 'D' enfoncée : Déplacement vers la droite.\n");
					break;
				default:
					break;
				}
			}
		}
		else if (!isKeyDown && pair.second) {
			pair.second = false;
			OutputDebugString(L"Touche relaché\n");
		}
	}
}



