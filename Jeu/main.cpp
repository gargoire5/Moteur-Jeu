#include "../Moteur/Engine.h"
#include "../Moteur/MeshRenderer.h"
#include "../Moteur/Camera.h"
#include "../Moteur/input.h"
#include "../Moteur/timer.h"
#include "MovementScript.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

void MovementScript::Update()
{
	Engine* pEngine = Engine::Instance();
	Input* pInput = pEngine->GetInput();
	float deltaTime = pEngine->GetTimer()->DeltaTime();
	pInput->Update();

	KeyState state = pInput->ListenToKey(0x5A);
	if ((state == KeyState::Down) || (state == KeyState::Held))
	{
		OutputDebugStringW(L"test");
		XMFLOAT3 fCurrPos = pEngine->GetCurrCam()->GetEntity()->GetTransform()->fPos;
		pEngine->GetCurrCam()->GetEntity()->SetPos(fCurrPos.x , fCurrPos.y, fCurrPos.z + (-0.5 * deltaTime));
	}	
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
//#ifdef _DEBUG
//	_CrtMemState memStateInit;
//	_CrtMemCheckpoint(&memStateInit);
//#endif
	//------------------------------------------------------

	Engine* pEngine = Engine::Instance();
	pEngine->Init();

	EntityManager* pEntityManager = pEngine->GetEntityManager();

	Entity* pCamEntity = pEntityManager->CreateEntity();
	Camera* pCamComponent = pCamEntity->AttachComponent<Camera>();
	pCamComponent->SetEntity(pCamEntity);
	pCamComponent->Init();
	pCamComponent->SetShader();
	pCamEntity->SetPos(-3, 0, 10);

	pEngine->SetMainCam(pCamComponent);

	Entity* pCubeEntity = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent = pCubeEntity->AttachComponent<MeshRenderer>();
	pCubeComponent->SetEntity(pCubeEntity);
	pCubeComponent->SetShader();
	pCubeComponent->GetEntity()->SetCurrCam();
	pCubeEntity->SetPos(0,0,0);

	Vertex vertices[] =
	{
		Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::White) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Black) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Green) }),
		Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Blue) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Yellow) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Cyan) }),
		Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Magenta) })
	};


	uint16_t indices[] =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	Mesh pMesh;
	int i = sizeof(vertices);
	int y = sizeof(indices);
	pMesh.UpLoadMesh(vertices, 8, indices, 36);
	pCubeComponent->SetMesh(&pMesh);

	MovementScript* pMovementScript = new MovementScript();
	pEngine->AddScript(pMovementScript);

	pEngine->Run();

	//------------------------------------------------------
//#ifdef _DEBUG
//	_CrtMemState memStateEnd, memStateDiff;
//	_CrtMemCheckpoint(&memStateEnd);
//	if (_CrtMemDifference(&memStateDiff, &memStateInit, &memStateEnd))
//	{
//		MessageBoxA(NULL, "MEMORY LEAKS", "DISCLAIMER", 0);
//	}
//#endif
}
