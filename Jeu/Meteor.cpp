#include "Meteor.h"
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

	MeshRenderer* pCubeComponent = _pEntity->AttachComponent<MeshRenderer>();
	pCubeComponent->SetEntity(_pEntity);
	pCubeComponent->SetShader();
	texture = pEngine->Instance()->GetGraphics()->GetTextureList(0);
	pCubeComponent->SetTexture2D(texture);
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
		texture = pEngine->Instance()->GetGraphics()->GetTextureList(1);
	}
	if (_bHit == true) {
		fDuration += fDeltaTime;
		texture = pEngine->Instance()->GetGraphics()->GetTextureList(0);
		if (fDuration >= 0.5f) {
			_bHit = false;
			fDuration = 0;
		}
	}
	
	

	XMFLOAT3 vPlayerPos = pEngine->GetCurrCam()->GetEntity()->GetTransform()->fPos;
	XMFLOAT3 vCurrPos = _pEntity->GetTransform()->fPos;

	XMFLOAT3 vDirection;
	XMStoreFloat3(&vDirection, XMVector3Normalize(XMLoadFloat3(&vPlayerPos) - XMLoadFloat3(&vCurrPos)));

	_pEntity->SetPos(vCurrPos.x + vDirection.x * fDistance, vCurrPos.y + vDirection.y *fDistance, vCurrPos.z + vDirection.z * fDistance);
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
{
	Engine::Instance()->GetEntityManager()->DeleteEntity(_pEntity);
}
