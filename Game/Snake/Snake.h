#pragma once
#include <vector>
#include "../DebuggingModule.h"
#include "COMMON_TYPES.h" //추후 윗단에서 인클루드 할 경우 제거예정
using namespace std;

class Snake : public CDebuggingModule
{
private:
	vector<pair<int, int>> vSnake;						//뱀 몸 좌표 저장 -> 맵 정보 없이 부딪히는지 확인할수있도록 큐로 안하고 벡터로 함
	Direction Dir;										//뱀 방향 저장
public:
	Snake();
	~Snake();
#ifdef _DEBUG
	Snake(void* pDebugConsole);
#endif
	int GetSize();										//뱀 길이 get함수
	const Direction GetDir() const;									//뱀 방향 get함수
	Direction SetDir(Direction NextDir);				//뱀 방향 set함수
	bool MoveSnake(int X, int Y, APPLE_CLR c=NONECOLOR);			//뱀이 이동할 때 마다 호출, c에 따라 뱀 길이가 달라짐
	const Point GetNextPosition();
	const vector<pair<int, int>>* GetSnakePosition() const { return &vSnake; }

private:
	bool SnakeSelfKill(int x, int y);								//새로 들어온 좌표가 이미 있는 좌표인지 검사 (스스로 몸에 부딪히는 경우인지 검사)
	void init();
};

