#pragma once
#include <vector>
#include "COMMON_TYPES.h"
using namespace std;

class Apple
{
private:
	APPLE_CLR eColor;						//�����������, �ʷϻ������ ����
	Point sApplePosition;

private:
	Point RandomXY(int nMax_X, int nMax_Y);
	APPLE_CLR RandomColor();

public:
	Apple();
	~Apple();
	/*Apple**/ 
	void CreateApple(int nMapSizeX, int nMapSizeY, APPLE_CLR c=NONECOLOR); // ���ʿ��� apple* return
	const int GetAppleX() { return sApplePosition.x; }
	const int GetAppleY() { return sApplePosition.y; }
	const APPLE_CLR GetAppleColor() { return eColor; }

};

