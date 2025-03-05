#pragma once
#include "Vector3D.h"

struct Box {
	Vector3D min;
	Vector3D max;
};


Vector3D GetCenter(const Box& box);
Vector3D GetCenter(const Box& box);
bool IntersectBox(const Box& B1, const Box& B2);