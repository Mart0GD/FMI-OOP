
//tests
#include "tests_spells.hpp"
#include "tests_player.hpp"
#include "tests_weapon.hpp"
#include "tests_enemy.hpp"
#include "tests_player_spells.hpp"
#include "tests_operators.hpp"
#include "tests_GameManager.hpp"
#include "tests_inheritance.hpp"

int getMenuChoice();

int main() {
    srand(time(NULL));
    int choice;
    bool running = true;

    while (running) {
        choice = getMenuChoice();

        switch (choice) {
        case 1:
            // Run all tests
            weapon_test::valid();
            weapon_test::invalid();
            std::cout << "\n-----------------------------\n" << std::endl;
            player_test::basicTests();
            std::cout << "\n-----------------------------\n" << std::endl;
            enemy_test::valid();
            enemy_test::invalid();
            std::cout << "\n-----------------------------\n" << std::endl;
            spells_tests::runAllTests();
            break;
        case 2:
            // Run Weapon tests
            weapon_test::valid();
            weapon_test::invalid();
            break;
        case 3:
            // Run Player basic tests
            player_test::basicTests();
            break;
        case 4:
            // Run Enemy basic tests
            enemy_test::valid();
            enemy_test::invalid();
            break;
        case 5:
            spells_tests::runAllTests();
            break;
        case 6:
            PlayerSpellTest::runAllTests();
            break;
        case 7:
            operators_tests::runAll();
            break;
        case 8:
            GameManager_test::run();
            break;
        case 9:
            Inheritance_tests::CharacterTests();
        case 0:
            running = false;
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice! Try again.\n";
            break;
        }
    }
}

int getMenuChoice() {
    int choice;
    std::cout << "\n=== Elden Thing Class System Tests ===\n"
        << "1. Run all tests\n"
        << "2. Run Weapon tests\n"
        << "3. Run Player basic tests\n"
        << "4. Run Enemy basic tests\n"
        << "5. Run Spell basic tests\n"
        << "6. Run Spell-Player basic tests\n"
        << "7. Run Operators tests\n"
        << "8. Simulate a game\n"
        << "9. Run Inheritance tests\n"
        << "0. Exit\n"
        << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}