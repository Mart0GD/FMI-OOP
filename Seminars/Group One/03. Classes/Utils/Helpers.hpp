#ifndef HELPERS_H
#define HELPER_H

#include "Car.hpp"

static bool conatins(Person** cars, std::size_t cnt, Person* owner) {
	for (int i = 0; i < cnt; i++){
		if (cars[i] == owner) return true;
	}
	return false;
}

#endif HELPER_H