#include "Meteor.h"
#include "Incl.h"
#include "Game.h"

Meteor::Meteor()
{
}

void Meteor::Init(float x, float y, float z)
{
	Engine* pEngine = Engine::Instance();
	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();
	Entity* pCubeEntity = pEntityManager->CreateEntity();
	pCubeEntity->SetSca(1, 1, 1);

	MeshRenderer* pCubeComponent = pCubeEntity->AttachComponent<MeshRenderer>();
	pCubeComponent->SetEntity(pCubeEntity);
	pCubeComponent->SetShader();
	pCubeComponent->SetTexture2D(pEngine->Instance()->GetGraphics()->GetTextureList(0));
	pCubeEntity->SetPos(x, y, z);

	pCubeComponent->SetMesh(Game::Instance()->GetMeteorMesh());
}
