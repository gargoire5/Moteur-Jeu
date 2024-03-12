#include "Bullet.h"
#include "Incl.h"

Bullet::Bullet()
{
	_pEntity = nullptr;
}

void Bullet::Init()
{
	Engine* pEngine = Engine::Instance();
	EntityManager* pEntityManager = pEngine->GetEntityManager();
	_pEntity = pEntityManager->CreateEntity();

	MeshRenderer* pMeshComponent = _pEntity->AttachComponent<MeshRenderer>();
	pMeshComponent->SetEntity(_pEntity);
	pMeshComponent->SetShader();
	pMeshComponent->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(1));

	Transform* pPlayerTransform = pEngine->GetCurrCam()->GetEntity()->GetTransform();

	_pEntity->SetPos(pPlayerTransform->fPos.x, pPlayerTransform->fPos.y, pPlayerTransform->fPos.z);
	_pEntity->GetTransform()->identityRot();
	_pEntity->GetTransform()->rotate(pEngine->GetCurrCam()->yaw, pEngine->GetCurrCam()->pitch, 0.0f);

	_fStartPos = _pEntity->GetTransform()->fPos;
}

void Bullet::Update()
{
	Camera* pCam = Engine::Instance()->GetCurrCam();
	float fDeltaTime = Engine::Instance()->GetTimer()->DeltaTime();

	XMFLOAT3 Pos = _pEntity->GetTransform()->fPos;

	float fSpeed = 50.0f;
	float fDistance = fSpeed * fDeltaTime;

	float x = sinf(XMConvertToRadians(pCam->yaw)) * fDistance;
	float y = sinf(XMConvertToRadians(pCam->pitch)) * fDistance;
	float z = cosf(XMConvertToRadians(pCam->yaw)) * fDistance;

	_pEntity->SetPos(Pos.x + x, Pos.y + y, Pos.z + z);

	XMFLOAT3 vCurrPos = _pEntity->GetTransform()->fPos;

	XMFLOAT3 vTotalDistance = vCurrPos - _fStartPos;

	//XMVector3Normalize()
	//XMLoadFloat3(&vTotalDistance)


	//if ( > 10)
	//{

	//}
}
