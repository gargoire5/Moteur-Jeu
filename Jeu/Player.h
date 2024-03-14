#pragma once
class Player
{
public:
	Player();
	void Init();
	int GetHp();
	~Player();
private:
	int _iHp;
};

