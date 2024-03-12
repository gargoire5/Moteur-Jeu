#include "Game.h"
#include "Incl.h"
#include "MovementScript.h"

Game* Game::_pInstance;

Game::Game()
{
}
Game* Game::Instance()
{
	if (!_pInstance)
	{
		_pInstance = new Game();
	}
    return _pInstance;
}

void Game::Run()
{

	Engine* pEngine = Engine::Instance();
	pEngine->Init();

	EntityManager* pEntityManager = pEngine->GetEntityManager();

	Entity* pCamEntity = pEntityManager->CreateEntity();
	Camera* pCamComponent = pCamEntity->AttachComponent<Camera>();
	pCamComponent->SetEntity(pCamEntity);
	pCamComponent->Init();
	pCamComponent->SetShader();
	pCamComponent->GetEntity()->SetCurrCam();
	pCamEntity->SetPos(0, 5, 0);

	pEngine->SetMainCam(pCamComponent);

	Entity* pCubeEntity = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent = pCubeEntity->AttachComponent<MeshRenderer>();
	pCubeComponent->SetEntity(pCubeEntity);
	pCubeComponent->SetShader();
	pCubeEntity->SetPos(-15, 0, 0);

	Entity* pCubeEntity2 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent2 = pCubeEntity2->AttachComponent<MeshRenderer>();
	pCubeComponent2->SetEntity(pCubeEntity2);
	pCubeComponent2->SetShader();
	pCubeEntity2->SetPos(0, 0, 15);

	Entity* pCubeEntity3 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent3 = pCubeEntity3->AttachComponent<MeshRenderer>();
	pCubeComponent3->SetEntity(pCubeEntity3);
	pCubeComponent3->SetShader();
	pCubeEntity3->SetPos(15, 0, 0);

	Entity* pCubeEntity4 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent4 = pCubeEntity4->AttachComponent<MeshRenderer>();
	pCubeComponent4->SetEntity(pCubeEntity4);
	pCubeComponent4->SetShader();
	pCubeEntity4->SetPos(15, 0, 15);

	Entity* pCubeEntity5 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent5 = pCubeEntity5->AttachComponent<MeshRenderer>();
	pCubeComponent5->SetEntity(pCubeEntity5);
	pCubeComponent5->SetShader();
	pCubeEntity5->SetPos(-15, 0, -15);

	Entity* pCubeEntity6 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent6 = pCubeEntity6->AttachComponent<MeshRenderer>();
	pCubeComponent6->SetEntity(pCubeEntity6);
	pCubeComponent6->SetShader();
	pCubeEntity6->SetPos(0, 0, -15);

	Entity* pCubeEntity7 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent7 = pCubeEntity7->AttachComponent<MeshRenderer>();
	pCubeComponent7->SetEntity(pCubeEntity7);
	pCubeComponent7->SetShader();
	pCubeEntity7->SetPos(15, 0, -15);

	Entity* pCubeEntity8 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent8 = pCubeEntity8->AttachComponent<MeshRenderer>();
	pCubeComponent8->SetEntity(pCubeEntity8);
	pCubeComponent8->SetShader();
	pCubeEntity8->SetPos(-15, 0, 15);

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
	pMesh.UpLoadMesh(vertices, 8, indices, 38);
	pCubeComponent->SetMesh(&pMesh);
	pCubeComponent2->SetMesh(&pMesh);
	pCubeComponent3->SetMesh(&pMesh);
	pCubeComponent4->SetMesh(&pMesh);
	pCubeComponent5->SetMesh(&pMesh);
	pCubeComponent6->SetMesh(&pMesh);
	pCubeComponent7->SetMesh(&pMesh);
	pCubeComponent8->SetMesh(&pMesh);

	MovementScript* pMovementScript = new MovementScript();
	pEngine->AddScript(pMovementScript);

	Game::Instance()->_bFPS = true;

	pEngine->Run();
}


