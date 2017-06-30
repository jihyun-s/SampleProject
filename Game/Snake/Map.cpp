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
	for (int i = 0; i < (int)vMap.size(); i++)
	{
		vMap[i].clear();
	}
	vMap.clear();
}

Size Map::GetMapSize()
{
	return sMapSize;
}

void Map::MakeApple()
{
	Apple* pNewApple = new Apple;
	pNewApple->CreateApple(sMapSize.x, sMapSize.y); // createapple �� �̷������ξ��°Ը³�.. && default�� NONECOLOR �� ���ڸ� �ִ°��ΰ�?
	
	while (ExistApple(pNewApple->GetAppleX(), pNewApple->GetAppleY()))
		pNewApple->CreateApple(sMapSize.x, sMapSize.y);

	vApple.push_back(*pNewApple);
	vMap[pNewApple->GetAppleX()][pNewApple->GetAppleY()] = 1;
}

bool Map::ExistApple(const int x, const int y, Apple** sGetApple)
{
	// ����� �ִ� ���
	for (vector<Apple>::iterator it = vApple.begin(); it != vApple.end(); ++it)
	{
		if (it->GetAppleX() == x && it->GetAppleY() == y)
		{
			if(sGetApple!=NULL) *sGetApple = &(*it);
			return true;
		}
	}
	
	sGetApple = NULL;	// ����� ���� ���
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