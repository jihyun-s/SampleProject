#include "Map.h"

Map::Map() : sMapSize(MAP_DEFAULT, MAP_DEFAULT)
{
	for (int i = 0; i < MAP_DEFAULT; i++)
	{
		vector<int> element(MAP_DEFAULT, 0);
		vMap.push_back(element);
	}
}

Map::Map(const int x, const int y) : sMapSize(x, y)
{
	for (int i = 0; i < x; i++)
	{
		vector<int> element(y, 0);
		vMap.push_back(element);
	}
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
	Apple* pNewApple = new Apple;
	pNewApple->CreateApple(sMapSize.x, sMapSize.y); //apple color는 현재 default로 random 생성하게 되어있음
	
	while (ExistApple(pNewApple->GetAppleX(), pNewApple->GetAppleY()))
		pNewApple->CreateApple(sMapSize.x, sMapSize.y);

	vApple.push_back(*pNewApple);
	vMap[pNewApple->GetAppleX()][pNewApple->GetAppleY()] = 1;
}

bool Map::ExistApple(const int x, const int y, Apple** sGetApple)
{
	// 사과가 있는 경우
	for (vector<Apple>::iterator it = vApple.begin(); it != vApple.end(); ++it)
	{
		if (it->GetAppleX() == x && it->GetAppleY() == y)
		{
			if(sGetApple!=NULL) *sGetApple = &(*it);
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
			return true;
		}
	}
	
	return false;
}

bool Map::DestroyWall(const int x, const int y) const
{
	if (x < 0 || x >= sMapSize.x || y < 0 || y >= sMapSize.y) // snake crash from wall
		return true;
	else
		return false;
}