#pragma once
#include "BoolArray.hpp"

class BoolArray;

class BoolProxy {

public:
	BoolProxy(int index, const BoolArray* owner);

	BoolProxy(const BoolProxy& other);
	BoolProxy& operator=(const BoolProxy& other);

	BoolProxy& operator=(int32_t element);

	operator bool() const;

private:
	int index;
	const BoolArray* owner;
};