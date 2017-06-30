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
	Map(int x, int y);
	~Map();
	Size GetMapSize();
	void MakeApple();
	Apple* ExistApple(int x, int y);
	void DeleteApple(int x, int y);
	bool DestroyWall(int x, int y);
	
};

