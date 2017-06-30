#include "Apple.h"

Apple::Apple() : eColor(NONECOLOR), sApplePosition(-1,-1)
{
}

Apple::~Apple()
{
}

Point Apple::RandomXY(int MAX_X, int MAX_Y)
{
	int nX = rand() % (MAX_X); // 0 ~ MAX-1 사이의 난수 생성
	int nY = rand() % (MAX_Y);

	Point sRet(nX, nY);
	return sRet;
}

APPLE_CLR Apple::RandomColor()
{
	APPLE_CLR nRandom = (APPLE_CLR) (rand() % 2);
	return nRandom;
}

Apple* Apple::CreateApple(int nMapSizeX, int nMapSizeY, APPLE_CLR c)
{
	if (c == RED || c == GREEN)
	{
		eColor = c;
	}
	else
	{
		eColor = RandomColor();
	}

	sApplePosition = RandomXY(nMapSizeX, nMapSizeY);

	return this;
}