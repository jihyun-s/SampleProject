#pragma once
#include <vector>
#include "COMMON_TYPES.h"
using namespace std;


class Apple
{
private:
	APPLE_CLR eColor;						//�����������, �ʷϻ������ ����
	vector<pair<int, int>> vApple;			//��� ��ǥ ����
public:
	Apple(APPLE_CLR c);
	~Apple();

	APPLE_CLR GetColor();					//��� ���� get�Լ�
	int GetSize();							//����� ���� get�Լ�
	Point MakeApplePosition(int MAX_X, int MAX_Y);		//����� ���� ���� ����� ����
	bool ExistApple(int x, int y);			//x, y �� ��ġ�� �̹� ����� �ִ��� Ȯ��
	void MakeApple(int x, int y);			//��� ���� �Լ�
	void DeleteApple(int x, int y);			//��� ���� �Լ�

};

