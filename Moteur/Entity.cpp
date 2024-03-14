#include "Entity.h"
#include "Engine.h"

Entity::Entity()
{
	_pTransform = new Transform();
}

std::vector<Component*>& Entity::GetComponentsList()
{
	return _vComponentList;
}

Camera* Entity::GetCurrCam()
{
	return _pCurrCam;
}

void Entity::SetCurrCam()
{
	_pCurrCam = Engine::Instance()->GetCurrCam();
}

Entity::~Entity()
{
	for (int i = 0; i < _vComponentList.size(); i++)
	{
		delete _vComponentList[i];
	}
}

void Entity::Update()
{
	for (Component* pComponent : _vComponentList)
	{
		pComponent->Update();
	}
}

void Entity::SetPos(float x, float y, float z)
{
	_pTransform->fPos = { x,y,z };
	_pTransform->Update_mPos();
	_pTransform->Update_WorldMatrix();
}

void Entity::SetSca(float x, float y, float z)
{
	_pTransform->fSca = { x,y,z };
	_pTransform->Update_mSca();
	_pTransform->Update_WorldMatrix();
}

Transform* Entity::GetTransform()
{
	return _pTransform;
}
