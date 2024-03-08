#include "Engine.h"
#include "Component.h"


Component::Component()
{
	_pShader = nullptr;
}

void Component::PreRender()
{

}

void Component::Render()
{

}

void Component::Update()
{
}

void Component::SetShader()
{
	_pShader = Engine::Instance()->GetGraphics()->GetShader();
}

