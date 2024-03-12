
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
	pCubeComponent->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(0));
	pCubeEntity->SetPos(-15, 0, 0);

	Entity* pCubeEntity2 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent2 = pCubeEntity2->AttachComponent<MeshRenderer>();
	pCubeComponent2->SetEntity(pCubeEntity2);
	pCubeComponent2->SetShader();
	pCubeComponent2->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(1));
	pCubeEntity2->SetPos(0, 0, 15);

	Entity* pCubeEntity3 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent3 = pCubeEntity3->AttachComponent<MeshRenderer>();
	pCubeComponent3->SetEntity(pCubeEntity3);
	pCubeComponent3->SetShader();
	pCubeComponent3->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(2));
	pCubeEntity3->SetPos(10,0, 0);

	float d1 = +1.0f;
	float d2 = -1.0f;
	float d3 = -1.25f;

	Vertex vertices[] =
	{
		Vertex({ XMFLOAT3(d1, d1, d2), XMFLOAT2(1.0f, 1.0f) }), //0
		Vertex({ XMFLOAT3(d2, d1, d1), XMFLOAT2(0.0f, 1.0f) }),
		Vertex({ XMFLOAT3(d1, d1, d1), XMFLOAT2(1.0f, 1.0f) }), //2

		Vertex({ XMFLOAT3(-0.5f, 1.0f, d2), XMFLOAT2(0.0f, 1.0f) }),

		Vertex({ XMFLOAT3(d1, +0.5f, d2), XMFLOAT2(1.0f, 0.5f) }),
		Vertex({ XMFLOAT3(+0.5f, d1, d2), XMFLOAT2(0.5f, 1.0f)}), //5
		Vertex({ XMFLOAT3(+0.5f, +0.5f, d2), XMFLOAT2(0.5f, 0.5f) }),
		Vertex({ XMFLOAT3(+0.75f, +0.75f, d3), XMFLOAT2(0.75f, 0.75f) }),

		Vertex({ XMFLOAT3(d1, +0.0f, d2), XMFLOAT2(1.0f, 0.0f) }),
		Vertex({ XMFLOAT3(+0.0f, d1, d2), XMFLOAT2(0.0f, 1.0f)}), //9
		Vertex({ XMFLOAT3(+0.0f, +0.5f, d2), XMFLOAT2(0.0f, 0.5f) }),
		Vertex({ XMFLOAT3(+0.25f, +0.75f, d3), XMFLOAT2(0.25f, 0.75f) }),

		Vertex({ XMFLOAT3(0.5f, -0.5f, d2), XMFLOAT2(0.5f,0.0f) }),
		Vertex({ XMFLOAT3(-0.5f, -0.5f, d2), XMFLOAT2(0.0f, 0.0f) }), //13
		Vertex({ XMFLOAT3(+0.5f, -0.5f, d2), XMFLOAT2(0.5f, 0.0f) }),
		Vertex({ XMFLOAT3(0.0f, -0.25f, -1.75f),XMFLOAT2(0.0f, 0.0f) }),//15
		Vertex({ XMFLOAT3(-0.5f, +0.5f, d2), XMFLOAT2(0.0f, 0.5f) }),
		Vertex({ XMFLOAT3(+0.75f, +0.25f, d3), XMFLOAT2(0.75f, 0.25f) }),

		Vertex({ XMFLOAT3(d1, +0.0f, d2), XMFLOAT2(1.0f, 0.0f) }),
		Vertex({ XMFLOAT3(+0.5f, +0.0f, d2), XMFLOAT2(0.5f, 0.0f) }), //19

		Vertex({ XMFLOAT3(d1, d1, -0.5f), XMFLOAT2(1.0f, 1.0f)}),
		Vertex({ XMFLOAT3(d1, +0.0f, -0.5f), XMFLOAT2(1.0f, 0.0f) }),
		Vertex({ XMFLOAT3(d1, d1, 0.0f), XMFLOAT2(1.0f, 1.0f) }), //22
		Vertex({ XMFLOAT3(d1, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) }),

		Vertex({ XMFLOAT3(1.5f, d1, 0.5f), XMFLOAT2(1.0f, 1.0f)}),
		Vertex({ XMFLOAT3(d1, -0.5f, 0.75f), XMFLOAT2(1.0f, 0.0f) }),
		Vertex({ XMFLOAT3(d1, 1.5f, d1), XMFLOAT2(1.0f, 1.0f) }), //26
		Vertex({ XMFLOAT3(0.0f, 0.5f, d1), XMFLOAT2(0.0f, 0.5f) }),

		Vertex({ XMFLOAT3(d1, d1, 0.75f),XMFLOAT2(1.0f, 1.0f)}),
		Vertex({ XMFLOAT3(0.0f, -0.5f, d1), XMFLOAT2(0.0f,0.0f) }),
		Vertex({ XMFLOAT3(0.0f, 1.0f, 1.50f), XMFLOAT2(0.0f, 1.0f) }), //30
		Vertex({ XMFLOAT3(d2, -1.0f, d1), XMFLOAT2(0.0f, 0.0f) }),

		Vertex({ XMFLOAT3(-1.0f, 0.5f, 0.5f), XMFLOAT2(0.0f, 0.5f)}),
		Vertex({ XMFLOAT3(-0.75f, -0.75f, -0.25f), XMFLOAT2(0.0f, 0.0f) }), //33
		Vertex({ XMFLOAT3(-1.0f, d1, 0.0f), XMFLOAT2(0.0f, 1.0f) }),
		Vertex({ XMFLOAT3(-0.5f, 0.0f, -0.75f), XMFLOAT2(0.0f, 1.0f) }),

		Vertex({ XMFLOAT3(+0.0f, 1.25f, d1), XMFLOAT2(0.0f, 1.0f) }), //36
		Vertex({ XMFLOAT3(+0.0f, 0.5f, 0.0f), XMFLOAT2(0.0f, 0.5f) }),
		Vertex({ XMFLOAT3(+0.0f, -1.25f, -0.5f), XMFLOAT2(0.0f, 0.0f) }),

	};


	uint16_t indices[] =
	{
		//triangles first face
	   //top right side
		0, 7, 5,
		0, 4, 7,
		5, 7, 6,
		4, 6, 7,

		//top center
		5, 11, 9,
		5, 6, 11,
		9, 11, 10,
		6, 10, 11,

		//top medium
		15, 6, 14,
		13, 15, 12,
		16, 15, 13,
		6, 15, 16,

		//right 
		4, 17, 6,
		17, 4, 18,
		18, 19, 17,
		19, 6, 17,

		14, 19, 18,
		16, 9, 8,
		9, 16, 3,

		//triangles back face
		24, 2, 25,
		24, 26, 2,
		25, 2, 27,
		26, 28, 22,
		26, 24, 28,
		28, 24, 22,
		27, 29, 25,
		26, 27, 2,
		1, 27, 30,
		30, 27, 26,
		27, 1, 29,
		1, 31, 29,
		31, 25, 29,

		//triangles left face
		1, 32, 31,
		31, 32, 33,
		32, 34, 33,
		1, 34, 32,
		34, 35, 33,
		35, 13, 33,
		34, 3, 35,
		3, 13, 35,

		//triangles right face
		0, 20, 18,
		20, 21, 18,
		21, 14, 18,
		21, 20, 22,
		22, 23, 21,
		23, 22, 24,
		23, 24, 25,
		23, 25, 21,
		21, 25, 14,

		//triangles top face
		26, 1, 30,
		34, 9, 3,
		0, 9, 22,
		36, 34, 1,
		36, 26, 22,

		//center
		36, 37, 34,
		22, 37, 36,
		9, 37, 22,
		34, 37, 9,

		//triangles bottom faces
		12, 38, 13,
		38, 12, 25,
		38, 25, 31,
		31, 13, 38,
		31, 33, 13,

	};

	Mesh pMesh;
	int i = sizeof(vertices);
	int y = sizeof(indices);
	pMesh.UpLoadMesh(vertices, i/20, indices, y/2);
	pCubeComponent->SetMesh(&pMesh);
	pCubeComponent2->SetMesh(&pMesh);


	Vertex verticesCube[] =
	{
		// Front face
		Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0, 1) }), // Bottom-left
		Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT2(0, 0) }), // Top-left
		Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT2(1, 0) }), // Top-right
		Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT2(1, 1) }), // Bottom-right

		// Back face
		Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT2(0, 1) }), // Bottom-left
		Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT2(0, 0) }), // Top-left
		Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT2(1, 0) }), // Top-right
		Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT2(1, 1) }), // Bottom-right

		// Left face
		Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0, 1) }), // Bottom-front
		Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT2(0, 0) }), // Top-front
		Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT2(1, 0) }), // Top-back
		Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT2(1, 1) }), // Bottom-back

		// Right face
		Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT2(0, 1) }), // Bottom-front
		Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT2(0, 0) }), // Top-front
		Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT2(1, 0) }), // Top-back
		Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT2(1, 1) }), // Bottom-back

		// Top face
		Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT2(0, 1) }), // Bottom-left
		Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT2(0, 0) }), // Top-left
		Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT2(1, 0) }), // Top-right
		Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT2(1, 1) }), // Bottom-right

		// Bottom face
		Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0, 1) }), // Bottom-left
		Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT2(0, 0) }), // Top-left
		Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT2(1, 0) }), // Top-right
		Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT2(1, 1) })  // Bottom-right
	};

	uint16_t indicesCube[] =
	{
		// Front face
		0, 1, 2,
		0, 2, 3,

		// Back face
		4, 6, 5,
		4, 7, 6,

		// Left face
		8, 10, 9,
		8, 11, 10,

		// Right face
		12, 13, 14,
		12, 14, 15,

		// Top face
		16, 17, 18,
		16, 18, 19,

		// Bottom face
		20, 22, 21,
		20, 23, 22
	};

	Mesh pMeshCube;
	int io = sizeof(verticesCube);
	int yo = sizeof(indicesCube);
	pMeshCube.UpLoadMesh(verticesCube, io / 20, indicesCube, yo / 2);
	pCubeComponent3->SetMesh(&pMeshCube);

	MovementScript* pMovementScript = new MovementScript();
	pEngine->AddScript(pMovementScript);

	Game::Instance()->_bFPS = true;

	pEngine->Run();
}


