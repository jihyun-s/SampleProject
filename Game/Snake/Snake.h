#pragma once
#include <vector>
#include "COMMON_TYPES.h" //���� ���ܿ��� ��Ŭ��� �� ��� ���ſ���
using namespace std;

class Snake
{
private:
	vector<pair<int, int>> vSnake;						//�� �� ��ǥ ���� -> �� ���� ���� �ε������� Ȯ���Ҽ��ֵ��� ť�� ���ϰ� ���ͷ� ��
	Direction Dir;										//�� ���� ����
	void* m_pDebugConsole;
public:
	Snake();
	~Snake();
#ifdef _DEBUG
	Snake(void* pDebugConsole);
#endif
	int GetSize();										//�� ���� get�Լ�
	Direction GetDir();									//�� ���� get�Լ�
	Direction SetDir(Direction NextDir);				//�� ���� set�Լ�
	bool MoveSnake(int X, int Y, APPLE_CLR c=NONECOLOR);			//���� �̵��� �� ���� ȣ��, c�� ���� �� ���̰� �޶���
	const Point GetNextPosition();
	const vector<pair<int, int>>* GetSnakePosition() const { return &vSnake; }

private:
	bool SnakeSelfKill(int x, int y);								//���� ���� ��ǥ�� �̹� �ִ� ��ǥ���� �˻� (������ ���� �ε����� ������� �˻�)
	void init();
};

