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
	// �� ĭ�� �̵�
	bool ret; // ������ 0�̰ų�, self kill
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
	else // ���� �浹
		return false;
	
	return ret;
}

void SnakeGame::ChangDirection(Direction a_dir)
{

}
