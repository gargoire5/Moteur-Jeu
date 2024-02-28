#include "../Moteur/Engine.h"
#include <iostream>
void main() {
	Graphics* yo = new Graphics();
	int oui = yo->CreateWindow();
	std::cout << oui;
 }