#pragma once
#include <vector>
#include "COMMON_TYPES.h"
using namespace std;

class Apple
{
private:
	APPLE_CLR eColor;						//빨간사과인지, 초록사과인지 구분
	Point sApplePosition;

private:
	Point RandomXY(int nMax_X, int nMax_Y);
	APPLE_CLR RandomColor();

public:
	Apple();
	~Apple();
	Apple* CreateApple(int nMapSizeX, int nMapSizeY, APPLE_CLR c);
	int GetAppleX() { return sApplePosition.x; }
	int GetAppleY() { return sApplePosition.y; }

};

