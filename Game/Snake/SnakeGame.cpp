#include "SnakeGame.h"


SnakeGame::SnakeGame()
{
	pMap = new Map();
	pSnake = new Snake();
	nScore = 0;
}

SnakeGame::~SnakeGame()
{
	if (pMap)
		delete pMap;
	if (pSnake)
		delete pSnake;
}

bool SnakeGame::SnakeCanGo()
{
	bool bResult;
	// condition
	// 1. º®¿¡ Ãæµ¹ x
	// 2. ¹ì¿¡ Ãæµ¹ x 
	// 3. ¹ì ¸ö±æÀÌ 0 x


	return bResult;
}

void SnakeGame::MoveStraight()
{
	// ÇÑ Ä­¾¿ ÀÌµ¿
}

void SnakeGame::ChangDirection(Direction a_dir)
{

}
