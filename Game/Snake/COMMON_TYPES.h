#pragma once

struct Point
{
	int x;
	int y;
	Point(int i, int j) : x(i), y(j){} //持失切
};

struct Size
{
	int x;
	int y;
	Size(int i, int j) : x(i), y(j){} //持失切
};

enum Direction
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN,
};

enum APPLE_CLR
{
	RED = 0,
	GREEN,
	NONECOLOR,
};
