#include "SnakeGame.h"

enum ScoreBoard { RedAppleScore = 30, GreenAppleScore=50, MoveScore = 5 };
SnakeGame::SnakeGame()
{
	pMap = new Map();
	pSnake = new Snake();
	nScore = 0;

	pMap->MakeApple();
}

SnakeGame::SnakeGame(CObserver* pObserver)
{
	pMap = new Map();
	pSnake = new Snake();
	nScore = 0;

	this->SetObserver(pObserver);
	pMap->MakeApple();
	NotifyObserver(false, nScore);
}

SnakeGame::~SnakeGame()
{
	if (pMap)
		delete pMap;
	if (pSnake)
		delete pSnake;
}
SnakeGame::SnakeGame(CObserver* pObserver, void* pDebugConsole)
{
	pMap = new Map(pDebugConsole);
	pSnake = new Snake(pDebugConsole);
	nScore = 0;

	this->SetObserver(pObserver);
	pMap->MakeApple();
	NotifyObserver(false, nScore);
}
bool SnakeGame::MoveStraight()
{
	// 한 칸씩 이동
	bool ret1, ret2, finalResult; 
	APPLE_CLR appleColor = NONECOLOR;
	Point nextPos = pSnake->GetNextPosition();

	bool bApple = false;
	// ret1 : 벽에 충돌
	// 벽에 충돌이어도 일단 이동시킴
	if (!(ret1=pMap->DestroyWall(nextPos.x, nextPos.y)))
	{
		Apple* tmp = NULL;
		bApple = pMap->ExistApple(nextPos.x, nextPos.y, &tmp);
		if (bApple)
		{
			appleColor = tmp->GetAppleColor();
			IncreaseGameScore(appleColor);
			pMap->DeleteApple(nextPos.x, nextPos.y);
		}
	}

	// ret2 : 몸길이0 or self kill
	ret2 = pSnake->MoveSnake(nextPos.x, nextPos.y, appleColor);

	if (ret1 || !ret2)	// fail
		finalResult = false;
	else
	{
		finalResult = true;
		IncreaseGameScore();
	}

	NotifyObserver(true, nScore);

	return finalResult;
}

void SnakeGame::ChangDirection(Direction a_dir)
{
	pSnake->SetDir(a_dir);
}

void SnakeGame::MakeApple()
{
	pMap->MakeApple();

	NotifyObserver();
}

void SnakeGame::SetObserver(CObserver* a_observer)
{
	m_observer = a_observer;
}

void SnakeGame::IncreaseGameScore(APPLE_CLR a_nColor)
{
	switch (a_nColor)
	{
	case RED:
		nScore += RedAppleScore;
		break;
	case GREEN:
		nScore += GreenAppleScore;
		break;
	case NONECOLOR:
		nScore += MoveScore;
		break;
	}
}