#pragma once
#include "../Moteur/Mesh.h"

class Player;
class Engine;
class Input;
class EntityManager;
class Timer;
class MovementScript;
class ShootScript;
class GameLogicScript;

class Game
{
public:
	static Game* Instance();
	void Run();
	Mesh* GetBulletMesh();
	Mesh* GetMeteorMesh();
	Mesh* GetLifeMesh();

	bool _bFPS = false;

	MovementScript* GetMovementScript();
	ShootScript* GetShootScript();
	GameLogicScript* GetGameLogicScript();
	Entity* GetSkyBox();
	Entity* GetLifeEntity();
	Player* GetPlayer();

private:
	Game();
	static Game* _pInstance;
	Mesh _BulletMesh;
	Mesh _MeteorMesh;
	Mesh _LifeBar;
	Entity* _pSkyBox;
	Entity* _pLifeEntity;
	MovementScript* _pMovementScript;
	ShootScript* _pShootScript;
	GameLogicScript* _pGameLogicScript;
	Player* _pPlayer;
};

