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

//UML에 없던 int X, Y 를 넣어준 이유 ->
//UML에 따르면 이미 SnakeGame클래스의 Move()함수에서 ExistApple(x,y)을 검사함. 
//이뜻은 이미 이동할 x,y를 Snakegame에서 계산했다는 뜻이됨(ExistApple 검사할때 들어가는 인자 x,y는 곧 뱀이이동할 위치니까)
//근데 이렇게 되면 Snake 클래스에 Dir을 가지고 있어야 할 이유가 사라지는것 아닌지 .... ( Dir를 사용하는곳이 Snake가 아닌 SnakeGame 되어버리니까 )
//또한, 원래 뱀이이동하면 그위치에있던 사과가 없어져야 함. 이작업은 꼭 SnakeGame 클래스에서 Snake::MoveSnake 호출 후에 잊지말고 해줄것. ( 해당 클래스에서는 사과 못지움)
bool Snake::MoveSnake(int X, int Y, APPLE_CLR c)
{
	//vector의 end()가 뱀의 머리임.
	TraceListbox(m_pDebugConsole, L"[%d][Snake] Start Move (%d,%d) color=%d", __LINE__, X, Y, c);

	int nSize = vSnake.size();

	if (SnakeSelfKill(X, Y))
	{
		TraceListbox(m_pDebugConsole, L"[%d][Error][Snake] self kill, size=%d", __LINE__, vSnake.size());
		return false;
	}

	if (c == RED) //뱀은 몸길이를 늘려 머리를 다음칸에 이동시킨다.
	{
		vSnake.push_back(make_pair(X, Y));
	}
	else if(c == GREEN) // 만약 이동한 칸에 초록사과가 있다면 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.( 즉, 몸길이가 줄어든다. 몸길이 그대로가 아님!)
	{
		vSnake.push_back(make_pair(X, Y));
		vSnake.erase(vSnake.begin(), vSnake.begin() + 2);//원래 꼬리부분위치를 일단 비우고(위치가 움직였으니) 이동한 꼬리위치를 추가로 비운다. (몸길이 줄임)
	}
	else //c == NONECOLOR , 몸길이가 '그대로'여야함
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