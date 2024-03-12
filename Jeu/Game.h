#pragma once

class Engine;
class Input;
class EntityManager;
class Timer;
class Game
{
public:
	static Game* Instance();
	void Run();

	bool _bFPS = false;

private:
	Game();
	static Game* _pInstance;
};

