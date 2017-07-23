#include "SnakeGame.h"

enum ScoreBoard { RedAppleScore = 30, GreenAppleScore=50, MoveScore = 5 };
SnakeGame::SnakeGame()
{
	pMap = new Map();
	pSnake = new Snake();
	nScore = 0;
	bGameOver = false;
	pMap->MakeApple();
}

SnakeGame::SnakeGame(CObserver* pObserver)
{
	pMap = new Map();
	pSnake = new Snake();
	nScore = 0;
	bGameOver = false;
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
	bGameOver = false;
	this->SetObserver(pObserver);
	pMap->MakeApple();
	NotifyObserver(false, nScore);
}
bool SnakeGame::MoveStraight()
{
	// 한 칸씩 이동
	bool ret1, ret2; 
	APPLE_CLR appleColor = NONECOLOR;
	Point nextPos = pSnake->GetNextPosition();

	bool bApple = false;
	// ret1 : 벽에 충돌
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

	// ret1의 결과값인 벽에 충돌하지 않은 경우에만 뱀을 진행시킨다. 
	// ret2 : 몸길이0 or self kill
	if (ret1 || !(ret2 = pSnake->MoveSnake(nextPos.x, nextPos.y, appleColor)))	// fail
		bGameOver = true;
	else
	{
		bGameOver = false;
		IncreaseGameScore();
	}

	NotifyObserver(true, nScore);

	return !bGameOver;
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