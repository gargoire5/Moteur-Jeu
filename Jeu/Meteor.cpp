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

	pCubeComponent = _pEntity->AttachComponent<MeshRenderer>();
	pCubeComponent->SetEntity(_pEntity);
	pCubeComponent->SetShader();
	pCubeComponent->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(0));
	_pEntity->SetPos(x, y, z);

	pCubeComponent->SetMesh(Game::Instance()->GetMeteorMesh());

	_pColider = _pEntity->AttachComponent<BoxColider>();
	_pColider->Init(Game::Instance()->GetMeteorMesh());
	_pColider->SetEntity(_pEntity);
	 rota = rand() % 7;
	
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

	XMFLOAT3 vDirection;
	XMStoreFloat3(&vDirection, XMVector3Normalize(XMLoadFloat3(&vPlayerPos) - XMLoadFloat3(&vCurrPos)));
	
	
	switch (rota) {
	case 0:
		_yaw += 0.1;
		
	case 1:
		_pitch += 0.1;
	case 2:
		_roll += 0.1;
	case 3:
		_yaw += 0.1;
		_pitch += 0.1;
	case 4:
		_yaw += 0.1;
		_roll += 0.1;
	case 5:
		_pitch += 0.1;
		_roll += 0.1;
	case 6:
		_yaw += 0.1;
		_pitch += 0.1;
		_roll += 0.1;
	}

	_pEntity->GetTransform()->identityRot();
	_pEntity->GetTransform()->rotate(_yaw, _pitch, _roll);

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
