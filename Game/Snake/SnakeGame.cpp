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

bool SnakeGame::MoveStraight()
{
	// 한 칸씩 이동
	bool ret; // 몸길이 0이거나, self kill
	Point nextPos = pSnake->GetNextPosition();

	if (!pMap->DestroyWall(nextPos.x, nextPos.y))
	{
		Apple* tmp = NULL;
		bool bApple = pMap->ExistApple(nextPos.x, nextPos.y, &tmp);
		if (bApple)
			ret = pSnake->MoveSnake(nextPos.x, nextPos.y, tmp->GetAppleColor());
		else
			ret = pSnake->MoveSnake(nextPos.x, nextPos.y);
	}
	else // 벽에 충돌
		return false;
	
	return ret;
}

void SnakeGame::ChangDirection(Direction a_dir)
{

}
