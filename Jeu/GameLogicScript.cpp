#include "GameLogicScript.h"
#include "Incl.h"
#include <cstdlib>
#include "Meteor.h"

GameLogicScript::GameLogicScript()
{
}

void GameLogicScript::Update()
{
	for (int i = 0; i < _vMeteorList.size(); i++)
	{
		_vMeteorList[i]->Update();
	}
}

void GameLogicScript::SpawnRandomMeteor()
{
	Engine* pEngine = Engine::Instance();
	XMFLOAT3 pPlayerPos = pEngine->GetCurrCam()->GetEntity()->GetTransform()->fPos;
	bool val = (rand() % 2)==1;
	float x = rand() % 200 + 30;
	float z = rand() % 200 + 30;
	float y = rand() % 20;

	Meteor* pMeteor = new Meteor();
	pMeteor->Init(pPlayerPos.x + x, pPlayerPos.y + y, pPlayerPos.z + z);
	_vMeteorList.push_back(pMeteor);
}
