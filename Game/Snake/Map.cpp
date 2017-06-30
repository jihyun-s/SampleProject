#include "Map.h"

Map::Map() : sMapSize(MAP_DEFAULT, MAP_DEFAULT)
{
	for (int i = 0; i < MAP_DEFAULT; i++)
	{
		vector<int> element(MAP_DEFAULT, 0);
		vMap.push_back(element);
	}
}

Map::Map(int x, int y) : sMapSize(x, y)
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
	pNewApple->CreateApple(sMapSize.x, sMapSize.y, NONECOLOR); // createapple �� �̷������ξ��°Ը³�.. && default�� NONECOLOR �� ���ڸ� �ִ°��ΰ�?
	
	Apple* pTmpApple = ExistApple(pNewApple->GetAppleX(), pNewApple->GetAppleY());
	while (pTmpApple)
	{
		pNewApple->CreateApple(sMapSize.x, sMapSize.y, NONECOLOR); // createapple �� �̷������ξ��°Ը³�.. && default�� NONECOLOR �� ���ڸ� �ִ°��ΰ�?
		pTmpApple = ExistApple(pNewApple->GetAppleX(), pNewApple->GetAppleY());
	}

	vApple.push_back(*pNewApple);
	vMap[pNewApple->GetAppleX()][pNewApple->GetAppleY()] = 1;
}

Apple* Map::ExistApple(int x, int y)
{

	/* <iterator version>
	for (vector<Apple>::iterator it = vApple.begin(); it != vApple.end(); ++it)
	{
		if (it->GetAppleX() == x && it->GetAppleY() == y)
			return NULL; //*it; �ش�κ� it�� �ش��ϴ� vApple pointer �����ֵ��� �����ʿ�
	}
	*/

	for (int i = 0; i < vApple.size(); i++)
	{
		if (vApple[i].GetAppleX() == x && vApple[i].GetAppleY() == y)
			return &vApple[i];
	}

	return NULL;
}

void Map::DeleteApple(int x, int y)
{
	/* <iterator version>
	for (vector<Apple>::iterator it = vApple.begin(); it != vApple.end(); ++it)
	{
		if (it->GetAppleX() == x && it->GetAppleY() == y)
			//�̺κе�. iterator �̿��ؼ� ������ ����� ���°��ΰ�
	}
	*/

	for (int i = 0; i < vApple.size(); i++)
	{
		if (vApple[i].GetAppleX() == x && vApple[i].GetAppleY() == y)
			vApple.erase(vApple.begin() + i);
	}
	return;
}

bool Map::DestroyWall(int x, int y)
{
	if (x < 0 || x >= sMapSize.x || y < 0 || y >= sMapSize.y) // snake crash from wall
		return true;
	else
		return false;
}