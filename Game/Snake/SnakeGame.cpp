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
	// 1. ���� �浹 x
	// 2. �쿡 �浹 x 
	// 3. �� ������ 0 x


	return bResult;
}

void SnakeGame::MoveStraight()
{
	// �� ĭ�� �̵�
}

void SnakeGame::ChangDirection(Direction a_dir)
{

}
