#pragma once
#include <vector>
#include <algorithm>
#include "COMMON_TYPES.h"
using namespace std;

class Apple
{
private:
	APPLE_CLR eColor;						//빨간사과인지, 초록사과인지 구분
	vector<pair<int, int>> vApple;			//사과 좌표 저장
public:
	Apple(APPLE_CLR c);
	~Apple();

	APPLE_CLR GetColor();					//사과 색깔 get함수
	int GetSize();							//사과의 갯수 get함수
	Point MakeApplePosition(int MAX);		//사과가 없는 곳에 사과를 생성
	bool ExistApple(int x, int y);			//x, y 의 위치에 이미 사과가 있는지 확인
	void MakeApple(int x, int y);			//사과 생성 함수
	void DeleteApple(int x, int y);			//사과 삭제 함수

};

