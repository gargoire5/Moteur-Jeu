#pragma once
#include "../Moteur/Incl.h"

class Entity;
class BoxColider;
class Bullet
{
public:
	Bullet();
	void Init();
	void Update();
	Entity* GetEntity();
	XMFLOAT3 GetStartPos();
	BoxColider* GetColider();
	~Bullet();
private:
	Entity* _pEntity;
	BoxColider* _pColider;
	XMFLOAT3 _fStartPos;

	float _yaw;
	float _pitch;
};

