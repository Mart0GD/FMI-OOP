#pragma once
#include <iostream>

class Iterator {

public:
	Iterator(uint8_t* data, int32_t index);

	Iterator& operator ++ ();
	Iterator operator ++ (int);

	bool operator * () const;
	uint8_t* operator -> () const;

	int32_t getIndex() const { return index; }

private:
	uint8_t* data;
	int32_t index;
};

bool operator == (const Iterator& i1, const Iterator& i2);
bool operator != (const Iterator& i1, const Iterator& i2);