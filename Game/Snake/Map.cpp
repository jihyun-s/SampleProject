#include "Map.h"

Map::Map() : sMapSize(MAP_DEFAULT, MAP_DEFAULT)
{
	Init();
}

Map::Map(const int x, const int y) : sMapSize(x, y)
{
	Init(x, y);
}

Map::Map(void *pDebugConsole) : sMapSize(MAP_DEFAULT, MAP_DEFAULT)
{
	SetDebugConsole(pDebugConsole);
	Init();
}

void Map::Init(int x, int y)
{
	for (int i = 0; i < MAP_DEFAULT; i++)
	{
		vector<int> element(MAP_DEFAULT, 0);
		vMap.push_back(element);
	}

	Trace(L"[%d][Map] init:x(%d),y(%d)", __LINE__, x, y);
}

Map::~Map()
{
	//임시객체와 swap하여 capacity 를 0으로 만들며 해제
	vector<vector<int>>().swap(vMap);
	vector<Apple>().swap(vApple); 
}

Size Map::GetMapSize()
{
	return sMapSize;
}


// MakeApple(APPLE_CLR c=NONECOLOR) 이렇게 인자로 넘겨주지 않으면 Apple->CreateApple 의 마지막 인자 c는 의미가 없어지는 것 아닌가욤?
// 차라리 아예 사과 만들때 컬러 지정 없이 항상 랜덤으로 만들도록 하는것은 어떨지??
void Map::MakeApple() 
{
	Apple cNewApple;
	cNewApple.CreateApple(sMapSize.x, sMapSize.y); //apple color는 현재 default로 random 생성하게 되어있음
	
	while (ExistApple(cNewApple.GetAppleX(), cNewApple.GetAppleY()))
		cNewApple.CreateApple(sMapSize.x, sMapSize.y);

	vApple.push_back(cNewApple);
	vMap[cNewApple.GetAppleX()][cNewApple.GetAppleY()] = 1;

	Trace(L"[%d][Map] MakeApple:x(%d),y(%d), color(%d)", __LINE__, cNewApple.GetAppleX(), cNewApple.GetAppleY(), cNewApple.GetAppleColor());
}

bool Map::ExistApple(const int x, const int y, Apple** sGetApple)
{
	// 사과가 있는 경우
	for (vector<Apple>::iterator it = vApple.begin(); it != vApple.end(); ++it)
	{
		if (it->GetAppleX() == x && it->GetAppleY() == y)
		{
			if(sGetApple!=NULL) *sGetApple = &(*it);
			Trace(L"[%d][Map] ExistApple:x(%d),y(%d)", __LINE__, x, y);
			return true;
		}
	}

	sGetApple = NULL;	// 사과가 없는 경우
	return false;
}

bool Map::DeleteApple(const int x, const int y)
{
	for (vector<Apple>::iterator it = vApple.begin(); it != vApple.end(); ++it)
	{
		if (it->GetAppleX() == x && it->GetAppleY() == y)
		{
			vApple.erase(it); 
			Trace(L"[%d][Map] DeletetApple:x(%d),y(%d)", __LINE__, x, y);
			return true;
		}
	}
	
	return false;
}

bool Map::DestroyWall(const int x, const int y) const
{
	if (x < 0 || x >= sMapSize.x || y < 0 || y >= sMapSize.y) // snake crash from wall
	{
		Trace(L"[%d][Error][Map] DestroyWall!!!!!!!!!!!", __LINE__);
		return true;
	}
	else
		return false;
}
