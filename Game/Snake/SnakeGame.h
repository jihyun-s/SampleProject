#pragma once
#include "Map.h"
#include "Snake.h"

class SnakeGame
{
private:
	Map *pMap;
	Snake *pSnake;
	int nScore;

public:
	explicit SnakeGame();
#if _DEBUG
	explicit SnakeGame(void* pDebugConsole);
#endif
	~SnakeGame();

	bool MoveStraight();
	void ChangDirection(Direction a_dir);
	void MakeApple();
};

