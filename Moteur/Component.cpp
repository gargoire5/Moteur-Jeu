#include "Component.h"


Component::Component()
{

}

void Component::SetShader()
{
	_pShader = Engine::Instance()->GetGraphics()->GetShader();
}

