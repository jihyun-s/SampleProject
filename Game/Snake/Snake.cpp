#include "Snake.h"

Snake::Snake()
{
	vSnake.push_back(make_pair(0,0));
	Dir = RIGHT;
}

Snake::~Snake()
{
	vSnake.clear();
}

int Snake::GetSize()
{
	return vSnake.size();
}

Direction Snake::GetDir()
{
	return Dir;
}

Direction Snake::SetDir(Direction NextDir)
{
	Direction cOldDir = Dir;
	Dir = NextDir;
	return Dir;
}

//UML�� ���� int X, Y �� �־��� ���� ->
//UML�� ������ �̹� SnakeGameŬ������ Move()�Լ����� ExistApple(x,y)�� �˻���. 
//�̶��� �̹� �̵��� x,y�� Snakegame���� ����ߴٴ� ���̵�(ExistApple �˻��Ҷ� ���� ���� x,y�� �� �����̵��� ��ġ�ϱ�)
//�ٵ� �̷��� �Ǹ� Snake Ŭ������ Dir�� ������ �־�� �� ������ ������°� �ƴ��� .... ( Dir�� ����ϴ°��� Snake�� �ƴ� SnakeGame �Ǿ�����ϱ� )
//����, ���� �����̵��ϸ� ����ġ���ִ� ����� �������� ��. ���۾��� �� SnakeGame Ŭ�������� Snake::MoveSnake ȣ�� �Ŀ� �������� ���ٰ�. ( �ش� Ŭ���������� ��� ������)
bool Snake::MoveSnake(APPLE_CLR c, int X, int Y)
{
	//vector�� end()�� ���� �Ӹ���.

	int nSize = vSnake.size();

	if (c == RED) //���� �����̸� �÷� �Ӹ��� ����ĭ�� �̵���Ų��.
	{
		vSnake.push_back(make_pair(X, Y));
	}
	else if(c == GREEN) // ���� �̵��� ĭ�� �ʷϻ���� �ִٸ� �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�.( ��, �����̰� �پ���. ������ �״�ΰ� �ƴ�!)
	{
		vSnake.push_back(make_pair(X, Y));
		vSnake.erase(vSnake.begin(), vSnake.begin() + 1);//���� �����κ���ġ�� �ϴ� ����(��ġ�� ����������) �̵��� ������ġ�� �߰��� ����. (������ ����)
	}
	else //c == NONECOLOR , �����̰� '�״��'������
	{
		vSnake.push_back(make_pair(X, Y));
		vSnake.erase(vSnake.begin());
	}

	if (vSnake.size() == 0) 
		return false;

	if (SnakeSelfKill())
		return false;

	return true;
}

bool Snake::SnakeSelfKill()
{
	bool bSelfKill = false;

	for (int i = 0; i < GetSize(); i++)
	{
		if ((vSnake[i].first == vSnake[GetSize() - 1].first) && (vSnake[i].second == vSnake[GetSize() - 1].second))
		{
			bSelfKill = true;
			break;
		}
	}

	return bSelfKill;
}