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
	~SnakeGame();

	bool MoveStraight();
	void ChangDirection(Direction a_dir);
};

