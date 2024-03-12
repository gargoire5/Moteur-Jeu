#include "ShootScript.h"
#include "Incl.h"

ShootScript::ShootScript()
{
}

void ShootScript::Update()
{
	Engine* pEngine = Engine::Instance();
	Input* pInput = pEngine->GetInput();

	if (pInput->IsKeyDown(VK_LBUTTON))
	{

	}
}
