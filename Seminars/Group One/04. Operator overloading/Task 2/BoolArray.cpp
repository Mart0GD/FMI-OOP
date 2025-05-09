#include "BoolArray.hpp"

#pragma region Ctor logic

BoolArray::BoolArray(uint32_t cap)
	: _size(cap), _allocated(0)
{
	_data = new uint8_t[cap]{};
	for (int i = 0; i < cap; ++i) _data[i] = 0;
}

BoolArray::BoolArray(const BoolArray& other)
	: BoolArray(other._size)
{
	for (int i = 0; i < other._allocated; i++) {
		if (other.getBit(i)) *this += 1;
		else *this += 0;
	}

	_allocated = other._allocated;
}
BoolArray& BoolArray::operator=(const BoolArray& other) {
	if (this == &other) return *this;
	if (other._size > _size) throw std::invalid_argument("Second array larger than first!");

	BoolArray copy(other);
	*this = std::move(copy);

	return *this;
}

BoolArray::BoolArray(BoolArray&& other) noexcept {
	_data = other._data;
	_allocated = other._allocated;
	_size = other._size;

	other._data = nullptr;
}
BoolArray& BoolArray::operator=(BoolArray&& other) noexcept {
	if (this == &other) return *this;

	std::swap(_data, other._data);
	_allocated = other._allocated;
	_size = other._size;

	return *this;
}

BoolArray::~BoolArray() noexcept {
	delete[] _data;
}

#pragma endregion

#pragma region Operator Logic

BoolArray BoolArray::operator + (int32_t element) {
	if (_allocated == _size * 8) throw std::out_of_range("Array is at max capacity!");
	BoolArray copy(*this);

	copy += element;
	return copy;
}
BoolArray& BoolArray::operator += (int32_t element) {
	if (_allocated == _size * 8) throw std::out_of_range("Array is at max capacity!");

	if (element) setBit(_allocated, true);
	else setBit(_allocated, false);

	return *this;
}

BoolArray BoolArray::operator + (const BoolArray& other) {
	if (_allocated + other._allocated >= _size) throw std::invalid_argument("Array to big!");
	BoolArray copy(*this);

	copy += other;
	return copy;
}
BoolArray& BoolArray::operator += (const BoolArray& other) {
	if (_allocated + other._allocated >= _size) throw std::invalid_argument("Array to big!");

	for (int i = 0; i < other._allocated; i++)
	{
		if (other.getBit(i)) *this += 1;
		else *this += 0;
	}

	return *this;
}

bool BoolArray::operator [] (int32_t index) const {
	if (index < 0 || index >= _size * 8) throw std::out_of_range("Index out of range!");
	return (bool)getBit(index);
}
BoolArray::BoolProxy BoolArray::operator [] (int32_t index) {
	if (index < 0 || index >= _size * 8) throw std::out_of_range("Index out of range!");
	return BoolProxy(*this, index);
}

BoolArray::operator uint32_t() const {
	
	uint32_t res = 0;
	int len = _size >= 4 ? 32 : _size * 8;
	for (int i = 0; i < len; i++)
	{
		bool bit = getBit(i);
		res |= ( bit << i);
	}

	return res;
}

bool operator < (const BoolArray& arr1, const BoolArray& arr2) {

	int i1 = 0;
	int i2 = 0;

	while (i1 < arr1.size() * 8 && i2 < arr2.size() * 8) {
		bool d1 = arr1[i1];
		bool d2 = arr2[i2];

		i1++;i2++;
		if (d1 == d2) continue;

		if (d1 == 1 && d2 == 0) return false;
		else return true;
	}

	return i1 == arr1.size() && i2 < arr2.size() ? true : false;
}
bool operator <= (const BoolArray& arr1, const BoolArray& arr2) {
	return arr1 < arr2 || arr1 == arr2;
}

bool operator > (const BoolArray& arr1, const BoolArray& arr2) {
	return !(arr1 < arr2);
}
bool operator >= (const BoolArray& arr1, const BoolArray& arr2) {
	return (arr1 > arr2) || arr1 == arr2;
}

bool operator == (const BoolArray& arr1, const BoolArray& arr2) {
	if (arr1.size() != arr2.size()) return false;

	for (int i = 0; i < arr1.size() * 8; i++){
		if (arr1[i] != arr2[i]) return false;
	}

	return true;
}
bool operator != (const BoolArray& arr1, const BoolArray& arr2) {
	return !(arr1 == arr2);
}

std::ostream& operator<<(std::ostream& os, const BoolArray& arr) {
	for (int i = 0; i < arr._size * 8; i++){
		os << arr[i] << ' ';
	}

	return os;
}
std::istream& operator>>(std::istream& is, BoolArray& arr) {

	char buffer[1024]{};
	int iter = 0;

	is.getline(buffer, 1024);
	int len = strlen(buffer);
	for (int i = 0; i < len / 2; i++){
		char temp = buffer[i];
		buffer[i] = buffer[len - 1 - i];
		buffer[len - 1 - i] = temp;
	}

	while (buffer[iter]) {
		if (buffer[iter] >= '0' && buffer[iter] <= '9') {
			if (buffer[iter] - '0') arr += 1;
			else arr._allocated++;
		}
		iter++;
	}

	return is;
}

#pragma endregion

#pragma region Logic

bool BoolArray::getBit(int position) const {
	if (position < 0 || position / 8 > _size) throw std::out_of_range("Index out of range!");

	int element = _data[position / 8];
	bool value = _data[position / 8] & (1 << (position % 8));
	return value;
}
void BoolArray::setBit(int position, bool value) {
	if (position < 0 || position > _size * 8) throw std::out_of_range("Index out of range!");
	
	if(value) _data[position / 8] |= (1 << (position % 8));
	else _data[position / 8] &= (0 << (position % 8));
	++_allocated;
}

#pragma endregion

#pragma region Proxy

BoolArray::BoolProxy::BoolProxy(BoolArray& owner, int32_t pos)
	: owner{ owner }, pos{ pos } {
}

BoolArray::BoolProxy::operator bool() const {
	return owner.getBit(pos);
}
BoolArray::BoolProxy& BoolArray::BoolProxy::operator = (bool what) {
	if (what) owner.setBit(pos, true);
	else owner.setBit(pos, false);

	return *this;
}
BoolArray::BoolProxy& BoolArray::BoolProxy::operator = (const BoolProxy& other) {
	return *this = (bool)other;
}

#pragma endregion 

#pragma region Iterator

BoolArray::Iterator BoolArray::Iterator::operator++() {
	++index;
	return *this;
}
BoolArray::Iterator& BoolArray::Iterator::operator++(int) {
	BoolArray::Iterator copy(*this);
	++(*this);
	return copy;
}

bool BoolArray::Iterator::operator==(const Iterator& other) const {
	return index == other.index;
}
bool BoolArray::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}

bool BoolArray::Iterator::operator*() const {
	return owner.getBit(index);
}
BoolArray::BoolProxy BoolArray::Iterator::operator*() {
	return BoolProxy(owner, index);
}

BoolArray::Iterator BoolArray::begin() {
	return Iterator(*this, 0);
}

BoolArray::Iterator BoolArray::end() {
	return Iterator(*this, _size * 8);
}

#pragma endregion

