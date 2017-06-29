#include "Map.h"

Map::Map() : X(10), Y(10), cRedApple(RED), cGreenApple(GREEN)
{
	for (int i = 0; i < 10; i++)
	{
		vector<int> element(10,0);
		vMap.push_back(element);
	}
}

Map::Map(int x, int y) : X(x), Y(y), cRedApple(RED), cGreenApple(GREEN)
{
	for (int i = 0; i < x; i++)
	{
		vector<int> element(y,0);
		vMap.push_back(element);
	}
}

Map::~Map()
{
	for (int i = 0; i < (int)vMap.size(); i++)
	{
		vMap[i].clear();
	}
	vMap.clear();
}

bool Map::ExistApple(int x, int y)
{
	return vMap[x][y] == 1 ? true : false;
}

void Map::MakeApple(APPLE_CLR c)
{
	Apple* pMake = NULL;

	if (c == RED)
		pMake = &cRedApple;
	else if (c == GREEN)
		pMake = &cGreenApple;
	else
	{
		//TraceListbox(&m_listmsg, L"[%d]Snake MakeApple Error", __LINE__);
		return;
	}

	Point pPosition = pMake->MakeApplePosition(X, Y);

	while (vMap[pPosition.x][pPosition.y] == 1)
	{
		pPosition = pMake->MakeApplePosition(X, Y);
	}

	vMap[pPosition.x][pPosition.y] = 1;				//사과가 있는 것을 표시
	pMake->MakeApple(pPosition.x, pPosition.y);
}

void Map::DeleteApple(int x, int y)
{
	if (vMap[x][y] == 0) return;

	if (cRedApple.ExistApple(x, y))
		cRedApple.DeleteApple(x, y);

	else if (cGreenApple.ExistApple(x, y))
		cGreenApple.DeleteApple(x, y);

	else
	{
		//TraceListbox(&m_listmsg, L"[%d]Snake DeleteApple Error", __LINE__);
		return;
	}

	vMap[x][y] = 0; //사과 없앤 후 Map에 정보 변경

	return;
}

void Map::MakeRandomApple(int Num)
{
	int RedNum = rand() % Num; // 0 ~ Num-1 사이의 난수 생성
	int GreenNum = Num - RedNum;

	while (RedNum--)
	{
		MakeApple(RED);
	}

	while (GreenNum--)
	{
		MakeApple(GREEN);
	}
}