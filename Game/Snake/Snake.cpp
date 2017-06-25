#include "Snake.h"

Snake::Snake()
{
	vSnake.push_back(make_pair(0,0));
	Dir = LEFT;
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

void Snake::MoveSnake(int x, int y)
{
	vSnake.push_back(make_pair(x, y));
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