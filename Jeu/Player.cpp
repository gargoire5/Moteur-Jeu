#include "Player.h"
#include "Incl.h"

Player::Player()
{
	_iHp = 5;
}

void Player::Init()
{
	Engine* pEngine = Engine::Instance();
	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();
	_pEntity = pEntityManager->CreateEntity();
	Camera* pCamComponent = _pEntity->AttachComponent<Camera>();
	pCamComponent->SetEntity(_pEntity);
	pCamComponent->Init();
	pCamComponent->SetShader();
	pCamComponent->GetEntity()->SetCurrCam();
	_pEntity->SetPos(0, 5, 0);

	_pBoxColider = _pEntity->AttachComponent<BoxColider>();
	_pBoxColider->Init(2, 2, 2);
	_pBoxColider->SetEntity(_pEntity);

	pEngine->SetMainCam(pCamComponent);
}

BoxColider* Player::GetBoxColider()
{
	return _pBoxColider;
}

Entity* Player::GetEntity()
{
	return _pEntity;
}

void Player::TakeDamage(int i)
{
	_iHp -= i;
}

int Player::GetIHp()
{
	return _iHp;
}

Player::~Player()
{
}

