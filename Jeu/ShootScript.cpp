#include "ShootScript.h"
#include "Incl.h"
#include "Bullet.h"

ShootScript::ShootScript()
{
}

void ShootScript::Update()
{
	Engine* pEngine = Engine::Instance();
	Input* pInput = pEngine->GetInput();
	Timer* pTimer = pEngine->GetTimer();

	if (pInput->IsKey(VK_LBUTTON))
	{
		float fCurrTime = pTimer->TotalTime();
		if (fCurrTime - _fLastShootTime >=0.3f)
		{
			Bullet* pBullet = new Bullet();
			pBullet->Init();
			_vBulletList.push_back(pBullet);
			_fLastShootTime = fCurrTime;
		}
	}

	for (int i = 0; i < _vBulletList.size(); i++)
	{
		_vBulletList[i]->Update();

		XMFLOAT3 vCurrPos = _vBulletList[i]->GetEntity()->GetTransform()->fPos;

		XMFLOAT3 vTotalDistance;
		XMStoreFloat3(&vTotalDistance, (XMLoadFloat3(&vCurrPos) - XMLoadFloat3(&_vBulletList[i]->GetStartPos())));

		float fTotalDistance = sqrt((vTotalDistance.x * vTotalDistance.x) + (vTotalDistance.y * vTotalDistance.y) + (vTotalDistance.z * vTotalDistance.z));

		if (fTotalDistance > 300)
		{
			Bullet* tmp = _vBulletList[i];
			_vBulletList.erase(_vBulletList.begin() + i);
			delete tmp;
		}
	}
}

std::vector<Bullet*>* ShootScript::GetBulletList()
{
	return &_vBulletList;
}
