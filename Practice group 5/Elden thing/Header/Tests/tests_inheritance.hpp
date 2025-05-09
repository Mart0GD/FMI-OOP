#pragma once
#include "Character.hpp"

namespace Inheritance_tests {
	void CharacterTests() {
		CharacterConfig config{ "pesho", 100, 150, 40, 100, 40, 20, 20, 30, 20 };
		CharacterConfig config2{ "gosho", 120, 100, 20, 90, 50, 10, 25, 20, 45 };

		Character someone = Character(config);

		Character anotherOne = Character(config2);

		anotherOne = someone;
	}
}