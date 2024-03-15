#include "Meteor.h"
#include "GameLogicScript.h"
#include "Incl.h"
#include "Game.h"

Meteor::Meteor()
{
	_iHp = 3;
}

void Meteor::Init(float x, float y, float z)
{
	Engine* pEngine = Engine::Instance();
	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();
	_pEntity = pEntityManager->CreateEntity();
	_pEntity->SetSca(3, 3, 3);

	pCubeComponent = _pEntity->AttachComponent<MeshRenderer>();
	pCubeComponent->SetEntity(_pEntity);
	pCubeComponent->SetShader();
	pCubeComponent->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(0));
	_pEntity->SetPos(x, y, z);

	pCubeComponent->SetMesh(Game::Instance()->GetMeteorMesh());

	_pColider = _pEntity->AttachComponent<BoxColider>();
	_pColider->Init(Game::Instance()->GetMeteorMesh());
	_pColider->SetEntity(_pEntity);
	
}

void Meteor::Update()
{
	Engine* pEngine = Engine::Instance();
	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();
	float fDeltaTime = pEngine->GetTimer()->DeltaTime();

	float fSpeed = 20.0f;
	float fDistance = fSpeed * fDeltaTime;

	if (_bHit == false) {
		pCubeComponent->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(0));
	}
	if (_bHit == true) {
		fDuration += fDeltaTime;
		pCubeComponent->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(1));
		if (fDuration >= 0.2f) {
			_bHit = false;
			fDuration = 0;
		}
	}

	XMFLOAT3 vPlayerPos = pEngine->GetCurrCam()->GetEntity()->GetTransform()->fPos;
	XMFLOAT3 vCurrPos = _pEntity->GetTransform()->fPos;

	_fYaw = _fYaw - (rand() % 10)/10.0f;
	_fPitch = _fPitch + (rand() % 10) / 10.0f;

	_pEntity->GetTransform()->identityRot();
	_pEntity->GetTransform()->rotate(_fYaw, _fPitch, 0.0f);

	_RDirection.x += -30 + rand() % (60 + 1);
	_RDirection.y += -30 + rand() % (60 + 1);
	_RDirection.z += -30 + rand() % (60 + 1);

	XMFLOAT3 vNormedDirection;
	XMStoreFloat3(&vNormedDirection, XMVector3Normalize(XMLoadFloat3(&vCurrPos) - XMLoadFloat3(&_RDirection)));
	XMFLOAT3 vNewPos;
	vNewPos.x = vCurrPos.x + vNormedDirection.x * fDistance;
	vNewPos.y = vCurrPos.y + vNormedDirection.y * fDistance;
	vNewPos.z = vCurrPos.z + vNormedDirection.z * fDistance;

	GameLogicScript* pLogic = Game::Instance()->GetGameLogicScript();

	if (vNewPos.x > 100)
	{
		pLogic->DestroyMeteor(this);
		return;
	}
	else if (vNewPos.x < -100)
	{
		pLogic->DestroyMeteor(this);
		return;
	}

	if (vNewPos.y > 50)
	{
		pLogic->DestroyMeteor(this);
		return;
	}
	else if (vNewPos.y < -50)
	{
		pLogic->DestroyMeteor(this);
		return;
	}

	if (vNewPos.z > 100)
	{
		pLogic->DestroyMeteor(this);
		return;
	}
	else if (vNewPos.z < -100)
	{
		pLogic->DestroyMeteor(this);
		return;
	}

	_pEntity->SetPos(vNewPos.x, vNewPos.y, vNewPos.z);
}

Entity* Meteor::GetEntity()
{
	return _pEntity;
}

BoxColider* Meteor::GetColider()
{
	return _pColider;
}

void Meteor::TakeDamage(int i)
{
	Engine* pEngine = Engine::Instance();
	_iHp -= i;
	_bHit = true;

}
int Meteor::GetIHP()
{
	return _iHp;
}
Meteor::~Meteor()
{}
