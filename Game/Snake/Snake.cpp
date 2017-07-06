#include "Snake.h"
#include "../stdafx.h"
#include "../utils.h"
Snake::Snake()
{
	init();
}

Snake::~Snake()
{
	vSnake.clear();
}

Snake::Snake(void *pDebugConsole) :m_pDebugConsole(pDebugConsole)
{
	init();
}

void Snake::init()
{
	vSnake.push_back(make_pair(0, 0));
	Dir = RIGHT;
	TraceListbox(m_pDebugConsole, L"[%d][Snake] init:x(0),y(0), direction:RIGHT", __LINE__);
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
	TraceListbox(m_pDebugConsole, L"[%d][Snake] SetDirection:%d->%d", __LINE__, cOldDir,Dir);
	return Dir;
}

//UML�� ���� int X, Y �� �־��� ���� ->
//UML�� ������ �̹� SnakeGameŬ������ Move()�Լ����� ExistApple(x,y)�� �˻���. 
//�̶��� �̹� �̵��� x,y�� Snakegame���� ����ߴٴ� ���̵�(ExistApple �˻��Ҷ� ���� ���� x,y�� �� �����̵��� ��ġ�ϱ�)
//�ٵ� �̷��� �Ǹ� Snake Ŭ������ Dir�� ������ �־�� �� ������ ������°� �ƴ��� .... ( Dir�� ����ϴ°��� Snake�� �ƴ� SnakeGame �Ǿ�����ϱ� )
//����, ���� �����̵��ϸ� ����ġ���ִ� ����� �������� ��. ���۾��� �� SnakeGame Ŭ�������� Snake::MoveSnake ȣ�� �Ŀ� �������� ���ٰ�. ( �ش� Ŭ���������� ��� ������)
bool Snake::MoveSnake(int X, int Y, APPLE_CLR c)
{
	//vector�� end()�� ���� �Ӹ���.
	TraceListbox(m_pDebugConsole, L"[%d][Snake] Start Move (%d,%d) color=%d", __LINE__, X, Y, c);

	int nSize = vSnake.size();

	if (SnakeSelfKill(X, Y))
	{
		TraceListbox(m_pDebugConsole, L"[%d][Error][Snake] self kill, size=%d", __LINE__, vSnake.size());
		return false;
	}

	if (c == RED) //���� �����̸� �÷� �Ӹ��� ����ĭ�� �̵���Ų��.
	{
		vSnake.push_back(make_pair(X, Y));
	}
	else if(c == GREEN) // ���� �̵��� ĭ�� �ʷϻ���� �ִٸ� �����̸� �ٿ��� ������ ��ġ�� ĭ�� ����ش�.( ��, �����̰� �پ���. ������ �״�ΰ� �ƴ�!)
	{
		vSnake.push_back(make_pair(X, Y));
		vSnake.erase(vSnake.begin(), vSnake.begin() + 2);//���� �����κ���ġ�� �ϴ� ����(��ġ�� ����������) �̵��� ������ġ�� �߰��� ����. (������ ����)
	}
	else //c == NONECOLOR , �����̰� '�״��'������
	{
		vSnake.push_back(make_pair(X, Y));
		vSnake.erase(vSnake.begin());
	}

	if (vSnake.size() == 0)
	{
		TraceListbox(m_pDebugConsole, L"[%d][Error][Snake] died, size=%d", __LINE__, vSnake.size());
		return false;
	}
	
	TraceListbox(m_pDebugConsole, L"[%d][Snake] Success Move (%d,%d) color=%d, size=%d", __LINE__, X, Y, c, vSnake.size());
	return true;
}

bool Snake::SnakeSelfKill(int x, int y)
{
	bool bSelfKill = false;
	if (GetSize() == 1) return bSelfKill;

	for (vector<pair<int, int>>::iterator it = vSnake.begin(); it != vSnake.end(); ++it)
	{
		if (it->first == x && it->second == y)
		{
			bSelfKill = true;
			break;
		}
	}
	return bSelfKill;
}

const Point Snake::GetNextPosition()
{
	pair<int, int> startPos = vSnake.back();
	int x = startPos.first;
	int y = startPos.second;

	switch(Dir)
	{
	case LEFT:
		--x;
		break;
		
	case RIGHT:
		++x;
		break;

	case UP:
		--y;
		break;

	case DOWN:
		++y;
		break;
	
	default:
		x = y = -1;
		break;
	}
	TraceListbox(m_pDebugConsole, L"[%d][Snake] Get Next(%d,%d)", __LINE__, x, y);
	return Point(x, y);
}