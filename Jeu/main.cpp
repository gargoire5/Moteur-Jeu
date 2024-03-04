#include "../Moteur/Engine.h"

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

	Engine* pEngine = new Engine();
	pEngine->Run();
	EntityManager* pEntityManager = pEngine->GetEntityManager();
	Entity* pTestEntity = pEntityManager->CreateEntity("test");
	Mesh* pTestEntityMesh = pTestEntity->AttachComponent<Mesh>(ComponentType::CompoMesh);

	std::array<Vertex, 8> vertices =
	{
		Vertex({ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Yellow) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT4(Colors::Red) }),
		Vertex({ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Yellow) })
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
	pTestEntityMesh->UploadMesh()


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