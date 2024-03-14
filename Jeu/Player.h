#pragma once
class BoxColider;
class Entity;

class Player
{
public:
	Player();
	void Init();
	BoxColider* GetBoxColider();
	Entity* GetEntity();
	void TakeDamage(int i);
	int GetIHp();
	~Player();
private:
	int _iHp;
	BoxColider* _pBoxColider;
	Entity* _pEntity;

};

