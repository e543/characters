#pragma once
#include <vector>
#include "Character.h"

struct Vector2 {
	int x, y;
	Vector2(int _x, int _y) : x(_x), y(_y) {}
};

class Display
{
	std::vector<Vector2> va_chs; // va ~ vertex array
	LONG height, width;

public:
	Display(LONG _height, LONG _width) :
		height(_height), 
		width(_width)
	{

	}

	std::vector<Vector2>& getVa(size_t N, LONG start_x, LONG start_y);
};

std::vector<Vector2>&  Display::getVa(size_t N, LONG start_x, LONG start_y) {
	size_t i = 0;
	size_t cur_x = start_x, cur_y = start_y;

	while(i < N){
		while (cur_x + 2*ch_width < width && i < N) {
			va_chs.emplace_back(Vector2(cur_x, cur_y));
			i++;
			cur_x += ch_width;
		}
		cur_x = start_x;
		cur_y += ch_height;
	}

	return  va_chs;
}