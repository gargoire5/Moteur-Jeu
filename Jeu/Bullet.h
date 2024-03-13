#pragma once
#include "../Moteur/Incl.h"

class Entity;
class Bullet
{
public:
	Bullet();
	void Init();
	void Update();
	Entity* GetEntity();
	XMFLOAT3 GetStartPos();
	~Bullet();
private:
	Entity* _pEntity;
	XMFLOAT3 _fStartPos;

	float _yaw;
	float _pitch;
};

