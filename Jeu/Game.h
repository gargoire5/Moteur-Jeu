#pragma once
#include "../Moteur/Mesh.h"

class Engine;
class Input;
class EntityManager;
class Timer;
class MovementScript;
class ShootScript;
class GameLogicScript;
class Player;

class Game
{
public:
	static Game* Instance();
	void Run();
	Mesh* GetBulletMesh();
	Mesh* GetMeteorMesh();

	bool _bFPS = false;

	MovementScript* GetMovementScript();
	ShootScript* GetShootScript();
	GameLogicScript* GetGameLogicScript();
	Entity* GetSkyBox();
	Player* GetPlayer();

private:
	Game();
	static Game* _pInstance;
	Mesh _BulletMesh;
	Mesh _MeteorMesh;

	Entity* _pSkyBox;
	MovementScript* _pMovementScript;
	ShootScript* _pShootScript;
	GameLogicScript* _pGameLogicScript;
	Player* _pPlayer;
};

