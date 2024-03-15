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

	Entity* CubeNight = Game::Instance()->GetSkyBox();

	Camera* pCam = pEngine->GetCurrCam();
	std::vector<Entity*> entityList = pEngine->GetEntityManager()->GetEntityList();
	if (pInput->IsKeyDown(VK_ESCAPE))
	{
		if (Engine::Instance()->_bPaused == false)
		{
			Engine::Instance()->Pause();
			ShowCursor(true);
		}
		else
		{
			Engine::Instance()->Resume();
			ShowCursor(false);
		}
	}

	if (Engine::Instance()->_bPaused == false)
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

		Transform* pTransform = pCam->GetEntity()->GetTransform();
		XMFLOAT3 Pos = pTransform->fPos;

		XMFLOAT3 NewPos = Pos;
		
		if (pInput->IsKey('Z'))
		{
			float fSpeed = 50.0f;
			float fDistance = fSpeed * fDeltaTime;

			float x = sinf(XMConvertToRadians(pCam->yaw)) * fDistance;
			float z = cosf(XMConvertToRadians(pCam->yaw)) * fDistance;

			NewPos.x += x;
			NewPos.z += z;
		}

		if (pInput->IsKey('S'))
		{
			float fSpeed = 50.0f;
			float fDistance = fSpeed * fDeltaTime;

			float x = sinf(XMConvertToRadians(pCam->yaw)) * fDistance;
			float z = cosf(XMConvertToRadians(pCam->yaw)) * fDistance;

			NewPos.x -= x;
			NewPos.z -= z;
		}
		if (pInput->IsKey('D'))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 50.0f;
			float fDistance = fSpeed * fDeltaTime;

			float x = sinf(XMConvertToRadians(pCam->yaw + 90)) * fDistance;
			float z = cosf(XMConvertToRadians(pCam->yaw + 90)) * fDistance;

			NewPos.x += x;
			NewPos.z += z;
		}
		if (pInput->IsKey('Q'))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 50.0f;
			float fDistance = fSpeed * fDeltaTime;

			float x = sinf(XMConvertToRadians(pCam->yaw + 90)) * fDistance;
			float z = cosf(XMConvertToRadians(pCam->yaw + 90)) * fDistance;

			NewPos.x -= x;
			NewPos.z -= z;
		}
		if (pInput->IsKey(VK_SPACE))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 20.0f;
			float fDistance = fSpeed * fDeltaTime;

			NewPos.y += fDistance;
		}
		if (pInput->IsKey(VK_LSHIFT))
		{
			Transform* pTransform = pCam->GetEntity()->GetTransform();
			XMFLOAT3 Pos = pTransform->fPos;

			float fSpeed = 20.0f;
			float fDistance = fSpeed * fDeltaTime;

			NewPos.y -= fDistance;
		}

		if (NewPos.x > 100)
			NewPos.x = 100;
		else if (NewPos.x < -100)
			NewPos.x = -100;

		if (NewPos.y > 50)
			NewPos.y = 50;
		else if (NewPos.y < -50)
			NewPos.y = -50;

		if (NewPos.z > 100)
			NewPos.z = 100;
		else if (NewPos.z < -100)
			NewPos.z = -100;

		pCam->GetEntity()->SetPos(NewPos.x, NewPos.y, NewPos.z);
		CubeNight->SetPos(NewPos.x, NewPos.y, NewPos.z);


		if (pInput->IsKeyDown(VK_RBUTTON))
		{
			if (Engine::Instance()->_bSlowMotion == true)
				Engine::Instance()->_bSlowMotion = false;
			else
				Engine::Instance()->_bSlowMotion = true;
		}
	}
	
};