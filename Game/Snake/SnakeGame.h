#pragma once
#include "Map.h"
#include "Snake.h"

class SnakeGame : public CSnakeGameComponent
{
protected:
	Map *pMap;
	Snake *pSnake;
	int nScore;
	bool bGameOver;

	virtual void SetObserver(CObserver* a_observer);
	void IncreaseGameScore(APPLE_CLR a_nColor = NONECOLOR);

public:
	explicit SnakeGame();
	explicit SnakeGame(CObserver* pObserver);
#if _DEBUG
	explicit SnakeGame(CObserver* pObserver, void* pDebugConsole);
#endif
	~SnakeGame();

	bool MoveStraight();
	void ChangDirection(Direction a_dir);
	void MakeApple();

	const Map* GetMap() const { return pMap; }
	const Snake* GetSnake() const { return pSnake; }
	const bool IsSnakeGameOver() const { return bGameOver; }
};

