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
	/*Apple**/ 
	void CreateApple(int nMapSizeX, int nMapSizeY, APPLE_CLR c=NONECOLOR); // 불필요한 apple* return
	const int GetAppleX() { return sApplePosition.x; }
	const int GetAppleY() { return sApplePosition.y; }
	const APPLE_CLR GetAppleColor() { return eColor; }

};

