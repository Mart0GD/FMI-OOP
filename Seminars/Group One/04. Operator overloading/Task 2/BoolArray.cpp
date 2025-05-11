#include "BoolArray.hpp"


BoolArray::BoolArray() 
	: _count(0), cap(INITIAL_CAP) 
{
	data = new uint8_t[cap]{};
}

BoolArray::BoolArray(const BoolArray& other) 
	: _count(other._count), cap(other.cap)
{
	data = new uint8_t[cap]{};
}
BoolArray& BoolArray::operator=(const BoolArray& other) {
	if (this == &other) return *this;

	if (cap < other._count) {
		clear();
		data = new uint8_t[other.cap]{};
	}

	for (int i = 0; i < other._count; i++) 
		data[i] = other.data[i];
	
	_count = other._count;
	cap = other.cap;

	return *this;
}
BoolArray& BoolArray::operator=(uint32_t element) {
	int size = sizeof(uint32_t) * 8;

	clear();
	data = new uint8_t[size]{};

	cap = INITIAL_CAP;
	_count = 0;

	for (int i = 0; i < size; i++) {
		bool el = (element & (1 << i));
		(*this)[_count++] = el;
	}

	return *this;
}

BoolArray::~BoolArray() {
	delete[] data;
}

void BoolArray::clear() {
	delete[] data;
}
bool BoolArray::resize() {
	uint8_t* old = data;

	data = new(std::nothrow) uint8_t[cap * 2]{};
	if (!data) {
		data = old;
		return false;
	}

	for (int i = 0; i < cap; i++)
		data[i] = old[i];

	delete[] old;
	cap *= 2;
	return true;
}

bool BoolArray::operator[](int32_t index) const {
	if (index >= cap * 8) throw std::out_of_range("invalid index");

	return data[index / 8] & (1 << (index % 8));
}
BoolProxy BoolArray::operator[](int32_t index) {
	if (index >= cap * 8) throw std::out_of_range("invalid index");

	return BoolProxy(index, this);
}

BoolArray& BoolArray::operator+=(bool element) {
	if (_count + 1 >= cap * 8) {
		if (!resize()) {
			clear();
			throw std::bad_alloc();
		}
	}
		

	(*this)[_count++] = element;
}
BoolArray operator+(const BoolArray& arr, bool element) {
	BoolArray copy(arr);

	copy += element;
	return copy;
}

BoolArray& BoolArray::operator+=(const BoolArray& other) {
	while (_count + other._count >= cap * 8)
	{
		if (!resize()) {
			clear();
			throw std::bad_alloc();
		}
	}

	for (int i = 0; i < other._count; i++)
		(*this)[_count++] = other[i];
}
BoolArray operator+(const BoolArray& arr1, const BoolArray& arr2) {
	BoolArray copy(arr1);

	copy += arr2;
	return copy;
}

bool operator<(const BoolArray& arr1, const BoolArray& arr2) {
	int len1 = arr1.count();
	int len2 = arr2.count();

	int less = len1 < len2 ? len1 : len2;
	for (size_t i = 0; i < len1; i++){
		if (arr1[i] == arr2[i]) continue;

		if (arr1[i] < arr2[i]) return true;
		return false;
	}

	return len1 < len2 ? true : false;
}
bool operator<=(const BoolArray& arr1, const BoolArray& arr2) {
	return arr1 < arr2 || arr1 == arr2;
}

bool operator>(const BoolArray& arr1, const BoolArray& arr2) {
	return !(arr1 < arr2);
}
bool operator>=(const BoolArray& arr1, const BoolArray& arr2) {
	return arr1 > arr2 || arr1 == arr2;
}

bool operator==(const BoolArray& arr1, const BoolArray& arr2) {
	if (arr1.count() != arr2.count()) return false;

	int len = arr1.count();
	for (int i = 0; i < len; ++i)
		if (arr1[i] != arr2[i]) return false;

	return true;
}
bool operator!=(const BoolArray& arr1, const BoolArray& arr2) {
	return !(arr1 == arr2);
}

BoolArray::operator uint32_t() {
	
	uint32_t num = 0;
	int len = sizeof(uint32_t) * 8;
	for (int i = 0; i < len; i++)
		num |= ((*this)[i] << i);

	return num;
}

std::ostream& operator << (std::ostream& os, const BoolArray& arr) {
	if (!os) throw std::invalid_argument("bad stream!");

	for (int i = 0; i < arr.count() && os; i++) {
		os << arr[i];
		if(i + 1 != arr.count()) os << ' ';
	}

	return os;
}
std::istream& operator >> (std::istream& is, BoolArray& arr) {
	if (!is) throw std::invalid_argument("bad stream!");

	char buffer[1024]; int iter = 0;
	is.getline(buffer, sizeof(buffer));

	do
	{
		if (buffer[iter] == '0' || buffer[iter] == '1')
			arr[arr._count++] = buffer[iter] - '0';

	} while (buffer[iter] != '\0' && ++iter);

	return is;
}

// TODO
// memory leak in previous task
// not parsing numbers in input!!