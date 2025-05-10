#include "Point.hpp"
#include <math.h>

bool inRange(const Point& p1, const Point& p2) {
	return abs(p1.x - p2.x) == 1 && abs(p1.y - p2.y) == 1;
}