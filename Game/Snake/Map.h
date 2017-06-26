#pragma once
#include "Apple.h"
#include <vector>
using namespace std;
#define MAP_MAX	10

class Map
{
private:
	int X;
	int Y;
	Apple cRedApple;
	Apple cGreenApple;
	vector< vector<int> > vMap;

public:
	Map();
	Map(int x, int y);
	~Map();
	bool ExistApple(int x, int y);
	void MakeApple(APPLE_CLR c);
	void DeleteApple(int x, int y);
	void MakeRandomApple(int Num);
};

