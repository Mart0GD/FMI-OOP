#pragma once
#include <iostream>

struct Point {
	int32_t x;
	int32_t y;
};

bool inRange(const Point& p1, const Point& p2);