#include "Apple.h"

Apple::Apple(APPLE_CLR c) : eColor(c)
{
}

Apple::~Apple()
{
	vApple.clear();
}


APPLE_CLR Apple::GetColor()
{
	return eColor;
}

int Apple::GetSize()
{
	return vApple.size();
}

Point Apple::MakeApplePosition(int MAX_X, int MAX_Y)
{
	int nX = rand() % (MAX_X); // 0 ~ MAX-1 사이의 난수 생성
	int nY = rand() % (MAX_Y);

	while (ExistApple(nX, nY))
	{
		nX = rand() % (MAX_X);
		nY = rand() % (MAX_Y);
	}

	Point sRet = { nX, nY };
	return sRet;
}

bool Apple::ExistApple(int x, int y)
{
	bool bExist = false;

	for (int i = 0; i < GetSize(); i++)
	{
		if ((vApple[i].first == x) && (vApple[i].second == y))
		{
			bExist = true;
			break;
		}
	}
	return bExist;
}

void Apple::MakeApple(int x, int y)
{
	vApple.push_back(make_pair(x, y));
}

void Apple::DeleteApple(int x, int y)
{
	for (int i = 0; i < GetSize(); i++)
	{
		if ((vApple[i].first == x) && (vApple[i].second == y))
		{
			vApple.erase(vApple.begin() + i);
			break;
		}
	}
}
