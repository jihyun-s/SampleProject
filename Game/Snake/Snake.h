#pragma once
#include <vector>
#include <algorithm>
#include "COMMON_TYPES.h" //���� ���ܿ��� ��Ŭ��� �� ��� ���ſ���
using namespace std;

class Snake
{
private:
	vector<pair<int, int>> vSnake;			//�� �� ��ǥ ���� -> �� ���� ���� �ε������� Ȯ���Ҽ��ֵ��� ť�� ���ϰ� ���ͷ� ��
	Direction Dir;							//�� ���� ����
public:
	Snake();
	~Snake();
	int GetSize();							//�� ���� get�Լ�
	Direction GetDir();						//�� ���� get�Լ�
	Direction SetDir(Direction NextDir);	//�� ���� set�Լ�

	void MoveSnake(int x, int y);			//���� �̵��� �� ���� ȣ��
	bool SnakeSelfKill();					//���� ���� ��ǥ�� �̹� �ִ� ��ǥ���� �˻� (������ ���� �ε����� ������� �˻�)

};

