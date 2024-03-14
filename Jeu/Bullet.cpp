#include "Bullet.h"
#include "Incl.h"
#include "Game.h"

Bullet::Bullet()
{
	_pEntity = nullptr;
}

void Bullet::Init()
{
	Engine* pEngine = Engine::Instance();
	EntityManager* pEntityManager = pEngine->GetEntityManager();
	_pEntity = pEntityManager->CreateEntity();
	_pEntity->SetSca(0.3, 0.3, 1);

	MeshRenderer* pMeshComponent = _pEntity->AttachComponent<MeshRenderer>();
	pMeshComponent->SetEntity(_pEntity);
	pMeshComponent->SetShader();
	pMeshComponent->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(2));
	pMeshComponent->SetMesh(Game::Instance()->GetBulletMesh());

	_pColider = _pEntity->AttachComponent<BoxColider>();
	_pColider->Init(Game::Instance()->GetBulletMesh());
	_pColider->SetEntity(_pEntity);

	Transform* pPlayerTransform = pEngine->GetCurrCam()->GetEntity()->GetTransform();

	_pEntity->SetPos(pPlayerTransform->fPos.x, pPlayerTransform->fPos.y - 2, pPlayerTransform->fPos.z);
	_pEntity->GetTransform()->identityRot();
	_pEntity->GetTransform()->rotate(pEngine->GetCurrCam()->yaw, pEngine->GetCurrCam()->pitch, 0.0f);

	_fStartPos = _pEntity->GetTransform()->fPos;

	_yaw = pEngine->GetCurrCam()->yaw;
	_pitch = pEngine->GetCurrCam()->pitch;

}

void Bullet::Update()
{
	Camera* pCam = Engine::Instance()->GetCurrCam();
	float fDeltaTime = Engine::Instance()->GetTimer()->DeltaTime();

	XMFLOAT3 Pos = _pEntity->GetTransform()->fPos;

	float fSpeed = 100.0f;
	float fDistance = fSpeed * fDeltaTime;

	float x = sinf(XMConvertToRadians(_yaw)) * fDistance;
	float y = -sinf(XMConvertToRadians(_pitch)) * fDistance;
	float z = cosf(XMConvertToRadians(_yaw)) * fDistance;

	_pEntity->SetPos(Pos.x + x, Pos.y + y, Pos.z + z);
}

Entity* Bullet::GetEntity()
{
	return _pEntity;
}

XMFLOAT3 Bullet::GetStartPos()
{
	return _fStartPos;
}

BoxColider* Bullet::GetColider()
{
	return _pColider;
}

Bullet::~Bullet()
{

	Engine::Instance()->GetEntityManager()->DeleteEntity(_pEntity);
}

