#include "GameLogicScript.h"
#include "Incl.h"
#include <cstdlib>
#include "Meteor.h"
#include "Game.h"
#include "ShootScript.h"
#include "Bullet.h"
#include "LifeBar.h"

GameLogicScript::GameLogicScript()
{
	_LifeBar = new LifeBar();
	_LifeBar->Init();
}

void GameLogicScript::Update()
{
	Game* pGame = Game::Instance();
	Timer* pTimer = Engine::Instance()->GetTimer();
	

	
	_LifeBar->Update();

	for (int i = 0; i < _vMeteorList.size(); i++)
	{
		_vMeteorList[i]->Update();
	}

	float fTotalTime = pTimer->TotalTime();

	if (fTotalTime < 60)
	{
		iMaxEnemie = 4;
	}
	else if (fTotalTime > 60 && fTotalTime < 120)
	{
		iMaxEnemie = 5;
	}
	else if (fTotalTime > 120 && fTotalTime < 180)
	{
		iMaxEnemie = 6;
	}
	else if (fTotalTime > 180 && fTotalTime < 240)
	{
		iMaxEnemie = 7;
	}
	else if (fTotalTime > 240 && fTotalTime < 300)
	{
		iMaxEnemie = 8;
	}

	if (_vMeteorList.size() < iMaxEnemie)
	{
		SpawnRandomMeteor();
	}

	std::vector<Bullet*>* vBulletList = pGame->GetShootScript()->GetBulletList();
	for (int i = 0; i < vBulletList->size(); i++)
	{
		for (int j = 0; j < _vMeteorList.size(); j++)
		{
			if (vBulletList->data()[i]->GetColider()->IsColidWith(_vMeteorList[j]->GetColider()->GetBoxGeo(), _vMeteorList[j]->GetEntity()))
			{
				_vMeteorList[j]->TakeDamage(1);
				_vBulletToDestroy.push_back(vBulletList->data()[i]);
				break;
			}
		}
	}

	for (int i = 0; i < _vMeteorList.size(); i++)
	{
		if (_vMeteorList[i]->GetIHP() < 1)
		{
			_vMeteorToDestroy.push_back(_vMeteorList[i]);
		}
	}

	for (int i = 0; i < _vBulletToDestroy.size(); i++)
	{
		Bullet* tmp = _vBulletToDestroy[i];
		for (int j = 0; j < vBulletList->size(); j++)
		{
			if (vBulletList->data()[j] == _vBulletToDestroy[i])
			{
				vBulletList->erase(vBulletList->begin() + j);
				break;
			}
		}
		delete tmp;
	}
	_vBulletToDestroy.clear();

	for (int i = 0; i < _vMeteorToDestroy.size(); i++)
	{
		Meteor* tmp = _vMeteorToDestroy[i];
		for (int j = 0; j < _vMeteorList.size(); j++)
		{
			if (_vMeteorList[j] == _vMeteorToDestroy[i])
			{
				_vMeteorList.erase(_vMeteorList.begin() + j);
				break;
			}
		}
		delete tmp;
	}
	_vMeteorToDestroy.clear();
}

void GameLogicScript::SpawnRandomMeteor()
{
	Engine* pEngine = Engine::Instance();
	XMFLOAT3 pPlayerPos = pEngine->GetCurrCam()->GetEntity()->GetTransform()->fPos;

	float x = rand() % 200 + 30;
	float z = rand() % 200 + 30;
	float y = rand() % 20;

	bool val = (rand() % 2)==1;
	if (val)
		x = -x;
	val = (rand() % 2) == 1;
	if (val)
		y = -y;
	val = (rand() % 2) == 1;
	if (val)
		z = -z;

	Meteor* pMeteor = new Meteor();
	pMeteor->Init(pPlayerPos.x + x, pPlayerPos.y + y, pPlayerPos.z + z);
	_vMeteorList.push_back(pMeteor);
}

