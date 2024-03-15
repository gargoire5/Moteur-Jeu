#include "LifeBar.h"
#include "Game.h"
#include "MovementScript.h"
#include "Incl.h"
#include "Player.h"

LifeBar::LifeBar()
{
	_pEntityLife = nullptr;
}

void LifeBar::Init()
{
	Engine* pEngine = Engine::Instance();
	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();
	_pEntityLife = pEntityManager->CreateEntity();
	Game* pGame = Game::Instance();
	

	pLifeBar = _pEntityLife->AttachComponent<MeshRenderer>();
	pLifeBar->SetEntity(_pEntityLife);
	pLifeBar->SetShader();
	pLifeBar->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(4));
	pLifeBar->SetMesh(Game::Instance()->GetLifeMesh());
	_pEntityLife->SetPos(0, 0, 0);

}

void LifeBar::Update()
{
	Engine* pEngine = Engine::Instance();
	Camera* pCam = pEngine->GetCurrCam();
	Transform* pTransform = pCam->GetEntity()->GetTransform();

	int Hp = Game::Instance()->GetPlayer()->GetIHp();

	XMFLOAT3 Pos = pTransform->fPos;
	_pEntityLife->SetPos(Pos.x , Pos.y, Pos.z );

	_pEntityLife->GetTransform()->identityRot();
	_pEntityLife->GetTransform()->rotate(pCam->yaw, pCam->pitch, 0.0f);

	switch (Hp) {
	case 0:
		pLifeBar->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(9));
		break;
	case 1:
		pLifeBar->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(8));
		break;
	case 2:
		pLifeBar->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(7));
		break;
	case 3:
		pLifeBar->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(6));
		break;
	case 4:
		pLifeBar->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(5));
		break;
	}
}

LifeBar::~LifeBar()
{
}
