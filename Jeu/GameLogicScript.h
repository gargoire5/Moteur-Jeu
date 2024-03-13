#pragma once
#include "../Moteur/Script.h"
#include <vector>
class Meteor;
class Bullet;
class GameLogicScript : public Script
{
public:
	GameLogicScript();
	void Update()override;
	void SpawnRandomMeteor();

	int iMaxEnemie = 4;

private:
	std::vector<Meteor*> _vMeteorList;
	std::vector<Bullet*> _vBulletToDestroy;
	std::vector<Meteor*> _vMeteorToDestroy;
};

