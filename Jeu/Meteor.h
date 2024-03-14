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
	float fDuration =0;
	int _iHp;
	bool _bHit;
	Entity* _pEntity;
	MeshRenderer* pCubeComponent;
	//Texture2D* texture;
	BoxColider* _pColider;
};
