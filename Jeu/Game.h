#pragma once
#include "../Moteur/Mesh.h"

class Engine;
class Input;
class EntityManager;
class Timer;

class Game
{
public:
	static Game* Instance();
	void Run();
	Mesh* GetBulletMesh();
	Mesh* GetMeteorMesh();

	bool _bFPS = false;

private:
	Game();
	static Game* _pInstance;
	Mesh _BulletMesh;
	Mesh _MeteorMesh;
};

