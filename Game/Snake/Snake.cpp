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

//UML에 없던 int X, Y 를 넣어준 이유 ->
//UML에 따르면 이미 SnakeGame클래스의 Move()함수에서 ExistApple(x,y)을 검사함. 
//이뜻은 이미 이동할 x,y를 Snakegame에서 계산했다는 뜻이됨(ExistApple 검사할때 들어가는 인자 x,y는 곧 뱀이이동할 위치니까)
//근데 이렇게 되면 Snake 클래스에 Dir을 가지고 있어야 할 이유가 사라지는것 아닌지 .... ( Dir를 사용하는곳이 Snake가 아닌 SnakeGame 되어버리니까 )
//또한, 원래 뱀이이동하면 그위치에있던 사과가 없어져야 함. 이작업은 꼭 SnakeGame 클래스에서 Snake::MoveSnake 호출 후에 잊지말고 해줄것. ( 해당 클래스에서는 사과 못지움)
bool Snake::MoveSnake(APPLE_CLR c, int X, int Y)
{
	//vector의 end()가 뱀의 머리임.

	int nSize = vSnake.size();

	if (c == RED) //뱀은 몸길이를 늘려 머리를 다음칸에 이동시킨다.
	{
		vSnake.push_back(make_pair(X, Y));
	}
	else if(c == GREEN) // 만약 이동한 칸에 초록사과가 있다면 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.( 즉, 몸길이가 줄어든다. 몸길이 그대로가 아님!)
	{
		vSnake.push_back(make_pair(X, Y));
		vSnake.erase(vSnake.begin(), vSnake.begin() + 1);//원래 꼬리부분위치를 일단 비우고(위치가 움직였으니) 이동한 꼬리위치를 추가로 비운다. (몸길이 줄임)
	}
	else //c == NONECOLOR , 몸길이가 '그대로'여야함
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