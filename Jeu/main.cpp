#include "../Moteur/Engine.h"
#include "../Moteur/MeshRenderer.h"
#include "../Moteur/Camera.h"
#include "../Moteur/input.h"
#include "../Moteur/timer.h"
#include "../Moteur/Collider.h"
#include "MovementScript.h"


#ifdef _DEBUG
#include <crtdbg.h>
#endif

void MovementScript::Update()
{

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
	pCamComponent->GetEntity()->SetCurrCam();
	pCamEntity->SetPos(0, 5, 0);

	pEngine->SetMainCam(pCamComponent);

	Entity* pCubeEntity = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent = pCubeEntity->AttachComponent<MeshRenderer>();
	pCubeComponent->SetEntity(pCubeEntity);
	pCubeComponent->SetShader();
	pCubeEntity->SetPos(-15,0,0);
	
	Entity* pCubeEntity2 = pEntityManager->CreateEntity();
	MeshRenderer* pCubeComponent2 = pCubeEntity2->AttachComponent<MeshRenderer>();
	pCubeComponent2->SetEntity(pCubeEntity2);
	pCubeComponent2->SetShader();
	pCubeEntity2->SetPos(0,0,15);

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


	//Vaisseau 3D
	Entity* pVaisseauEntity = pEntityManager->CreateEntity();
	MeshRenderer* pVaisseauComponent = pVaisseauEntity->AttachComponent<MeshRenderer>();
	pVaisseauComponent->SetEntity(pVaisseauEntity);
	pVaisseauComponent->SetShader();
	pVaisseauComponent->GetEntity()->SetCurrCam();
	pVaisseauEntity->SetPos(20, 0, 0);


	Vertex verticesVaisseau[] =
	{
		Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Cyan) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Yellow) }),
		Vertex({ XMFLOAT3(-0.5f, +0.0f, -2.5f), XMFLOAT4(Colors::Green) })
	};

	uint16_t indicesVaisseau[] =
	{
		//first triangle
		0, 2, 1,

		//2nd triangle
		0, 1, 3,

		//3rd triangle
		1, 2, 3,

		//4th triangle
		0, 3, 2
	};

	Mesh pMeshVaisseau;
	int iVaisseau = sizeof(verticesVaisseau);
	int yVaisseau = sizeof(indicesVaisseau);
	pMeshVaisseau.UpLoadMesh(verticesVaisseau, 8, indicesVaisseau, 36);
	pVaisseauComponent->SetMesh(&pMeshVaisseau);

    Collider boxVaisseau;
    boxVaisseau.CreateBoxCollide(verticesVaisseau, indicesVaisseau, 4);

    //astéroide 3D
    Entity* pAstEntity = pEntityManager->CreateEntity();
    MeshRenderer* pAstComponent = pAstEntity->AttachComponent<MeshRenderer>();
    pAstComponent->SetEntity(pAstEntity);
    pAstComponent->SetShader();
    pAstComponent->GetEntity()->SetCurrCam();
    pAstEntity->SetPos(5, 0, 0);

    float d1 = +1.0f;
    float d2 = -1.0f;
    float d3 = -1.25f;

    Vertex verticesAst[] =
    {
        Vertex({ XMFLOAT3(d1, d1, d2), XMFLOAT4(Colors::Red) }), //0
        Vertex({ XMFLOAT3(d2, d1, d1), XMFLOAT4(Colors::Yellow) }),
        Vertex({ XMFLOAT3(d1, d1, d1), XMFLOAT4(Colors::Cyan) }), //2
        Vertex({ XMFLOAT3(-0.5f, d1, d2), XMFLOAT4(Colors::Magenta) }),

        Vertex({ XMFLOAT3(d1, +0.5f, d2), XMFLOAT4(Colors::DarkBlue) }),
        Vertex({ XMFLOAT3(+0.5f, d1, d2), XMFLOAT4(Colors::Red) }), //5
        Vertex({ XMFLOAT3(+0.5f, +0.5f, d2), XMFLOAT4(Colors::DarkGreen) }),
        Vertex({ XMFLOAT3(+0.75f, +0.75f, d3), XMFLOAT4(Colors::Lime) }),

        Vertex({ XMFLOAT3(d1, +0.0f, d2), XMFLOAT4(Colors::GreenYellow) }),
        Vertex({ XMFLOAT3(+0.0f, d1, d2), XMFLOAT4(Colors::Green) }), //9
        Vertex({ XMFLOAT3(+0.0f, +0.5f, d2), XMFLOAT4(Colors::Orange) }),
        Vertex({ XMFLOAT3(+0.25f, +0.75f, d3), XMFLOAT4(Colors::Lime) }),

        Vertex({ XMFLOAT3(0.5f, -0.5f, d2), XMFLOAT4(Colors::Cyan) }),
        Vertex({ XMFLOAT3(-0.5f, -0.5f, d2), XMFLOAT4(Colors::Red) }), //13
        Vertex({ XMFLOAT3(+0.5f, -0.5f, d2), XMFLOAT4(Colors::DarkGreen) }),
        Vertex({ XMFLOAT3(0.0f, -0.25f, -1.75f), XMFLOAT4(Colors::Pink) }),//15
        Vertex({ XMFLOAT3(-0.5f, +0.5f, d2), XMFLOAT4(Colors::DarkGreen) }),
        Vertex({ XMFLOAT3(+0.75f, +0.25f, d3), XMFLOAT4(Colors::Red) }),

        Vertex({ XMFLOAT3(d1, +0.0f, d2), XMFLOAT4(Colors::Red) }),
        Vertex({ XMFLOAT3(+0.5f, +0.0f, d2), XMFLOAT4(Colors::Green) }), //19

        Vertex({ XMFLOAT3(d1, d1, -0.5f), XMFLOAT4(Colors::DarkGreen)}),
        Vertex({ XMFLOAT3(d1, +0.0f, -0.5f), XMFLOAT4(Colors::Gray) }),
        Vertex({ XMFLOAT3(d1, d1, 0.0f), XMFLOAT4(Colors::Pink) }), //22
        Vertex({ XMFLOAT3(d1, 0.0f, 0.0f), XMFLOAT4(Colors::Green) }),

        Vertex({ XMFLOAT3(1.5f, d1, 0.5f), XMFLOAT4(Colors::Red)}),
        Vertex({ XMFLOAT3(d1, -0.5f, 0.75f), XMFLOAT4(Colors::Pink) }),
        Vertex({ XMFLOAT3(d1, 1.5f, d1), XMFLOAT4(Colors::AliceBlue) }), //26
        Vertex({ XMFLOAT3(0.0f, 0.5f, d1), XMFLOAT4(Colors::DarkBlue) }),

        Vertex({ XMFLOAT3(d1, d1, 0.75f), XMFLOAT4(Colors::Orange)}),
        Vertex({ XMFLOAT3(0.0f, -0.5f, d1), XMFLOAT4(Colors::Red) }),
        Vertex({ XMFLOAT3(0.0f, d1, 1.50f), XMFLOAT4(Colors::Orange) }), //30
        Vertex({ XMFLOAT3(d2, d2, d1), XMFLOAT4(Colors::Cyan) }),

        Vertex({ XMFLOAT3(d2, 0.5f, 0.5f), XMFLOAT4(Colors::Green)}),
        Vertex({ XMFLOAT3(-0.75f, -0.75f, -0.25f), XMFLOAT4(Colors::Red) }), //33
        Vertex({ XMFLOAT3(d2, d1, 0.0f), XMFLOAT4(Colors::Blue) }),
        Vertex({ XMFLOAT3(-0.5f, 0.0f, -0.75f), XMFLOAT4(Colors::Orange) }),

        Vertex({ XMFLOAT3(+0.0f, 1.25f, d1), XMFLOAT4(Colors::Orange) }), //36
        Vertex({ XMFLOAT3(+0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::DarkBlue) }),
        Vertex({ XMFLOAT3(+0.0f, -1.25f, -0.5f), XMFLOAT4(Colors::Orange) }),

    };

    uint16_t indicesAst[] =
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

    Mesh pMeshAst;
    int iAst = sizeof(verticesAst);
    int yAst = sizeof(indicesAst);
    pMeshAst.UpLoadMesh(verticesAst, 40, indicesAst, 200);
    pAstComponent->SetMesh(&pMeshAst);

    Collider boxAst;
    boxAst.CreateBoxCollide(verticesAst, indicesAst, 39);

	MovementScript* pMovementScript = new MovementScript();
	pEngine->AddScript(pMovementScript);

	pEngine->FPS = true;

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