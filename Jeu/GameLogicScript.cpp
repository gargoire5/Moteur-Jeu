#include "GameLogicScript.h"
#include "Incl.h"
#include <cstdlib>
#include "Meteor.h"
#include "Game.h"
#include "ShootScript.h"
#include "Bullet.h"
#include "Player.h"
#include "LifeBar.h"

static int frameCnt = 0;
static float timeElapsed = 0.0f;

GameLogicScript::GameLogicScript()
{
	_LifeBar = new LifeBar();
	_LifeBar->Init();
}

void GameLogicScript::Update()
{
	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();

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
	else if (fTotalTime > 360)
	{
		Engine::Instance()->Exit();
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
				DestroyBullet(vBulletList->data()[i]);
				break;
			}
		}
	}

	Player* pPlayer = pGame->GetPlayer();
	for (int i = 0; i < _vMeteorList.size(); i++)
	{
		if (pPlayer->GetBoxColider()->IsColidWith(_vMeteorList[i]->GetColider()->GetBoxGeo(), _vMeteorList[i]->GetEntity()))
		{
			pPlayer->TakeDamage(1);
			DestroyMeteor(_vMeteorList[i]);
			if (pPlayer->GetIHp() < 1)
			{
				Engine::Instance()->Exit();
			}
		}
		if (_vMeteorList[i]->GetIHP() < 1)
		{
			score += 100;
			DestroyMeteor(_vMeteorList[i]);
		}
	}

	for (int i = 0; i < _vBulletToDestroy.size(); i++)
	{
		pEntityManager->DeleteEntity(_vBulletToDestroy[i]->GetEntity());
		for (int j = 0; j < vBulletList->size(); j++)
		{
			if (_vBulletToDestroy[i] == vBulletList->data()[j])
			{
				vBulletList->erase(vBulletList->begin() + j);
			}
		}
		delete _vBulletToDestroy[i];
	}
	_vBulletToDestroy.clear();

	for (int i = 0; i < _vMeteorToDestroy.size(); i++)
	{
		pEntityManager->DeleteEntity(_vMeteorToDestroy[i]->GetEntity());
		for (int j = 0; j < _vMeteorList.size(); j++)
		{
			if (_vMeteorToDestroy[i] == _vMeteorList[j])
			{
				_vMeteorList.erase(_vMeteorList.begin() + j);
				
			}
		}
		delete _vMeteorToDestroy[i];
	}
	_vMeteorToDestroy.clear();

	frameCnt++;
	if ((Engine::Instance()->GetTimer()->TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt;
		int pScore = score;
		int pTotaltime = Engine::Instance()->GetTimer()->TotalTime();

		std::wstring fpsStr = std::to_wstring(fps);
		std::wstring scoreStr = std::to_wstring(pScore);
		std::wstring totaltimeStr = std::to_wstring(pTotaltime);

		std::wstring windowText = Engine::Instance()->GetGraphics()->mMainWndCaption +
			L"    FPS: " + fpsStr +
			L"    Score:  " + scoreStr +
			L"    Temps:  " + totaltimeStr;

		SetWindowText(Engine::Instance()->GetGraphics()->_hWindow, windowText.c_str());

		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void GameLogicScript::SpawnRandomMeteor()
{
	Engine* pEngine = Engine::Instance();
	XMFLOAT3 pPlayerPos = pEngine->GetCurrCam()->GetEntity()->GetTransform()->fPos;

	float x = 50 - rand() % (100 + 1);
	float z = 25 - rand() % (25 + 1);
	float y = 50 - rand() % (100 + 1);

	Meteor* pMeteor = new Meteor();
	pMeteor->Init(x,y,z);
	_vMeteorList.push_back(pMeteor);
}

void GameLogicScript::DestroyMeteor(Meteor* pMeteor)
{
	_vMeteorToDestroy.push_back(pMeteor);
}

void GameLogicScript::DestroyBullet(Bullet* pBullet)
{
	_vBulletToDestroy.push_back(pBullet);
}

