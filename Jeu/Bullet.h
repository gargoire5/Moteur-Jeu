#pragma once
class Entity;
class Bullet
{
public:
	Bullet();
	void Init();
	void Update();
	~Bullet();
private:
	Entity* _pEntity;
	XMFLOAT3 _fStartPos;
};

