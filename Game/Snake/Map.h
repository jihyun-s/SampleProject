#pragma once
#include "Apple.h"
#include <vector>

using namespace std;
#define MAP_DEFAULT	10

class Map
{
private:
	Size sMapSize;
	vector<Apple> vApple;
	vector<vector<int>> vMap;

public:
	Map();
	Map(const int x, const int y);
	~Map();
	Size GetMapSize();
	void MakeApple();
	bool ExistApple(const int x, const int y, Apple** sGetApple=NULL);
	bool DeleteApple(const int x, const int y);		// ����ó���� ���� ���� bool
	bool DestroyWall(const int x, const int y) const;
	
};

