#include "MovementScript.h"
#include "Incl.h"
#include "Game.h"

MovementScript::MovementScript()
{}

void MovementScript::Update()
{
	Engine* pEngine = Engine::Instance();
	Input* pInput = pEngine->GetInput();
	float fDeltaTime = pEngine->GetTimer()->DeltaTime();


	Entity* LifeBar = Game::Instance()->GetLifeEntity();
	Entity* CubeNight = Game::Instance()->GetSkyBox();

	Camera* pCam = pEngine->GetCurrCam();
	std::vector<Entity*> entityList = pEngine->GetEntityManager()->GetEntityList();
	if (pInput->IsKeyDown(VK_ESCAPE))
	{
		if (Game::Instance()->_bFPS == false)
		{
			Game::Instance()->_bFPS = true;
			ShowCursor(false);
		}
		else
		{
			Game::Instance()->_bFPS = false;
			ShowCursor(true);
		}
	}

	if (Game::Instance()->_bFPS)
	{
		POINT vWindowSize = pEngine->GetGraphics()->GetWindowSize();

		RECT rect = { NULL };
		GetWindowRect(pEngine->GetGraphics()->_hWindow, &rect);

		POINT CurrPos;
		POINT WindowCenter;
		WindowCenter.x = rect.left + (vWindowSize.x / 2);
		WindowCenter.y = rect.top + (vWindowSize.y / 2);
		GetCursorPos(&CurrPos);

		POINT Rotation;
		Rotation.x = CurrPos.x - WindowCenter.x;
		Rotation.y = CurrPos.y - WindowCenter.y;

		pCam->yaw += (Rotation.x / 20.0f);
		pCam->pitch += (Rotation.y / 20.0f);

		if (pCam->pitch > 90.0f)
		{
			pCam->pitch = 90.0f;
		}
		else if (pCam->pitch < -90.0f)
		{
			pCam->pitch = -90.0f;
		}

		pCam->GetEntity()->GetTransform()->identityRot();
		//LifeBar->GetTransform()->identityRot();
		pCam->GetEntity()->GetTransform()->rotate(pCam->yaw, pCam->pitch, 0.0f);
		//LifeBar->GetTransform()->rotate(pCam->yaw, pCam->pitch, 0.0f);
		SetCursorPos(WindowCenter.x, WindowCenter.y);

		if (pInput->IsKey('Z'))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 50.0f;
			float fDistance = fSpeed * fDeltaTime;

			float x = sinf(XMConvertToRadians(pCam->yaw)) * fDistance;
			float z = cosf(XMConvertToRadians(pCam->yaw)) * fDistance;

			pCam->GetEntity()->SetPos(Pos.x + x, Pos.y, Pos.z + z);
			CubeNight->SetPos(Pos.x + x, Pos.y, Pos.z + z);
			
		}

		if (pInput->IsKey('S'))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 50.0f;
			float fDistance = fSpeed * fDeltaTime;

			float x = sinf(XMConvertToRadians(pCam->yaw)) * fDistance;
			float z = cosf(XMConvertToRadians(pCam->yaw)) * fDistance;

			pCam->GetEntity()->SetPos(Pos.x - x, Pos.y, Pos.z - z);
			CubeNight->SetPos(Pos.x - x, Pos.y, Pos.z - z);
			//LifeBar->SetPos(Pos.x - x, Pos.y, Pos.z - z);
		}
		if (pInput->IsKey('D'))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 50.0f;
			float fDistance = fSpeed * fDeltaTime;

			float x = sinf(XMConvertToRadians(pCam->yaw + 90)) * fDistance;
			float z = cosf(XMConvertToRadians(pCam->yaw + 90)) * fDistance;

			pCam->GetEntity()->SetPos(Pos.x + x, Pos.y, Pos.z + z);
			CubeNight->SetPos(Pos.x + x, Pos.y, Pos.z + z);
			//LifeBar->SetPos(Pos.x + x, Pos.y, Pos.z + z);
		}
		if (pInput->IsKey('Q'))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 50.0f;
			float fDistance = fSpeed * fDeltaTime;

			float x = sinf(XMConvertToRadians(pCam->yaw + 90)) * fDistance;
			float z = cosf(XMConvertToRadians(pCam->yaw + 90)) * fDistance;

			pCam->GetEntity()->SetPos(Pos.x - x, Pos.y, Pos.z - z);
			CubeNight->SetPos(Pos.x - x, Pos.y, Pos.z - z);
			//LifeBar->SetPos(Pos.x - x, Pos.y, Pos.z - z);
		}
		if (pInput->IsKey(VK_SPACE))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 20.0f;
			float fDistance = fSpeed * fDeltaTime;

			pCam->GetEntity()->SetPos(Pos.x, Pos.y + fDistance, Pos.z);
			CubeNight->SetPos(Pos.x, Pos.y + fDistance, Pos.z);
		}
		if (pInput->IsKey(VK_LSHIFT))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 20.0f;
			float fDistance = fSpeed * fDeltaTime;

			pCam->GetEntity()->SetPos(Pos.x, Pos.y - fDistance, Pos.z);
			CubeNight->SetPos(Pos.x, Pos.y - fDistance, Pos.z);

		}
		if (pInput->IsKeyDown(VK_RBUTTON))
		{
			if (Engine::Instance()->bSlowMotion == true)
				Engine::Instance()->bSlowMotion = false;
			else
				Engine::Instance()->bSlowMotion = true;
		}
	}
	
};