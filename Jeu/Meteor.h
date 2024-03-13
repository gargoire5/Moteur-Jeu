#pragma once
#include "Incl.h"
class Meteor
{
public:
	Meteor();
	void Init(float x, float y, float z);
	void Update();
	Entity* GetEntity();
	//~Meteor();
private:
	int _iHp;
	Entity* _pEntity;
};

