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
	Entity* pCamEntity = pEntityManager->CreateEntity();
	Camera* pCamComponent = pCamEntity->AttachComponent<Camera>();
	pCamComponent->SetEntity(pCamEntity);
	pCamComponent->Init();
	pCamComponent->SetShader();
	pCamComponent->GetEntity()->SetCurrCam();
	pCamEntity->SetPos(0, 5, 0);

	pEngine->SetMainCam(pCamComponent);

}

int Player::GetHp()
{
	return _iHp;
}

Player::~Player()
{
}

