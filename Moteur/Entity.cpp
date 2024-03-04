#include "Entity.h"

Entity::Entity(const char* cName)
{}




const char* Entity::GetName()
{
	return _cName;
}

std::vector<Component*> Entity::GetComponents()
{
	return _vComponentList;
}