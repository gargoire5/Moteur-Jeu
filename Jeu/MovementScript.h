#pragma once
#include "../Moteur/Script.h"
class MovementScript : public Script
{
public:
	MovementScript();
	void Update()override;

private:

};

MovementScript::MovementScript()
{
}