#pragma once
#include "Incl.h"
class Meteor
{
public:
	Meteor();
	void Init(float x, float y, float z);
	void Update();
	Entity* GetEntity();
	BoxColider* GetColider();
	void TakeDamage(int i);
	int GetIHP();
	~Meteor();
private:
	int _iHp;
	Entity* _pEntity;
	BoxColider* _pColider;
};

