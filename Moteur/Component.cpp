#include "Engine.h"
#include "Component.h"


Component::Component()
{

}

void Component::PreRender()
{

}

void Component::Render()
{

}

void Component::SetShader()
{
	_pShader = Engine::Instance()->GetGraphics()->GetShader();
}

