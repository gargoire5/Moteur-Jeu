#include "../Moteur/Engine.h"
#include "../Moteur/MeshRenderer.h"
#include "../Moteur/Camera.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

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

	Entity* cam = pEntityManager->CreateEntity("camera");
	Camera* pcamera = cam->AttachComponent<Camera>();
	pcamera->Init();
	pcamera->SetShader();

	Entity* pTest = pEntityManager->CreateEntity("test");
	MeshRenderer* pMeshTest = pTest->AttachComponent<MeshRenderer>();
	pMeshTest->SetShader();

	std::array<Vertex, 8> vertices =
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

	std::array<std::uint16_t, 36> indices =
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
	pMesh.UpLoadMesh(vertices, indices);
	pMeshTest->SetMesh(&pMesh);
	pMeshTest->SetPosition(0,0,0);

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
