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
SnakeGame::SnakeGame(void* pDebugConsole)
{
	pMap = new Map(pDebugConsole);
	pSnake = new Snake(pDebugConsole);
	nScore = 0;
}
bool SnakeGame::MoveStraight()
{
	// �� ĭ�� �̵�
	bool ret1, ret2; 
	APPLE_CLR appleColor = NONECOLOR;
	Point nextPos = pSnake->GetNextPosition();

	// ret1 : ���� �浹
	// ���� �浹�̾ �ϴ� �̵���Ŵ
	if (!(ret1=pMap->DestroyWall(nextPos.x, nextPos.y)))
	{
		Apple* tmp = NULL;
		bool bApple = pMap->ExistApple(nextPos.x, nextPos.y, &tmp);
		if (bApple)
			appleColor = tmp->GetAppleColor();		
	}

	// ret2 : ������0 or self kill
	ret2 = pSnake->MoveSnake(nextPos.x, nextPos.y, appleColor);
	
	return (ret1||!ret2)?false:true;
}

void SnakeGame::ChangDirection(Direction a_dir)
{
	pSnake->SetDir(a_dir);
}
