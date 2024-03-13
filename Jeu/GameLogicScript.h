#pragma once
#include "../Moteur/Script.h"
#include <vector>
class Meteor;
class GameLogicScript : public Script
{
public:
	GameLogicScript();
	void Update()override;
	void SpawnRandomMeteor();

private:
	std::vector<Meteor*> _vMeteorList;
};

