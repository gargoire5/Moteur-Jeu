#pragma once
#include "../Moteur/Script.h"
#include <vector>

class Bullet;
class ShootScript : public Script
{
public:
	ShootScript();
	void Update()override;
	std::vector<Bullet*>* GetBulletList();

private:
	std::vector<Bullet*> _vBulletList;
	float _fLastShootTime = 0;
};



