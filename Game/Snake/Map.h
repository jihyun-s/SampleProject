#pragma once
#include "Apple.h"
#include "SnakeGameComponent.h"
#include <vector>
#include "../DebuggingModule.h"
using namespace std;
#define MAP_DEFAULT	10

class Map : public CDebuggingModule
{
private:
	Size sMapSize;
	vector<Apple> vApple;
	vector<vector<int>> vMap;
	
	void Init(int x = MAP_DEFAULT, int y = MAP_DEFAULT);
public:
	Map();
	Map(const int x, const int y);
#ifdef _DEBUG
	Map(void* pDebugConsole);
#endif
	~Map();
	Size GetMapSize();
	void MakeApple();
	bool ExistApple(const int x, const int y, Apple** sGetApple=NULL);
	bool DeleteApple(const int x, const int y);		// 예외처리를 위한 리턴 bool
	bool DestroyWall(const int x, const int y) const;
	const vector<Apple>* GetApplePosition() const { return &vApple; }
};

