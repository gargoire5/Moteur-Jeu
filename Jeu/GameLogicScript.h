#pragma once
#include "../Moteur/Script.h"
#include <vector>
class Meteor;
class Bullet;
class LifeBar;
class GameLogicScript : public Script
{
public:
	GameLogicScript();
	void Update()override;
	void SpawnRandomMeteor();

	void DestroyMeteor(Meteor* pMeteor);
	void DestroyBullet(Bullet* pBullet);

	int iMaxEnemie;

private:
	std::vector<Meteor*> _vMeteorList;
	std::vector<Bullet*> _vBulletToDestroy;
	std::vector<Meteor*> _vMeteorToDestroy;
	LifeBar* _LifeBar;
};

