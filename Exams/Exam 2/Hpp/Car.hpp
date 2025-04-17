#pragma once

/*
Car - клас, който представя кола. Една кола има марка, дата на производство, тип на багажника, мощност в конски сили и брой места за сядане. Изискванията към класа са:
    - символният низ марка да е с произволна дължина;
    - типът на багажника трябва да е една от стойностите: “Sedan”, “Kombi”, “Hatchback”, като тази стойност е константна (не може да бъде променена след създаване на обект);
    - трябва да се пази информация за общата мощност на всички живи обекти-коли. За нея също трябва да има подходящи методи за достъп;
    - имплементирайте функция за извеждане на информацията за кола в подаден като параметър текстов поток;
    - имплементирайте конструктор с параметър входен поток, който създава кола по данни, прочетени от потока.
*/
#include "Date.hpp" 


enum TrunkType {
    Unknown = -1,
    Sedan = 0,
    Kombi = 1,
    Hatchback = 2,
    COUNT
};

const char trunkTypes[3][10] = { "Sedan", "Kombi", "Hatchback" };

class Car {

public:
    Car(const char* maker, const Date& dop, TrunkType trunkType, uint32_t hp, uint32_t seats);
    Car(std::istream& is = std::cin);

    Car(const Car& other);
    Car& operator=(const Car& other);

    Car(Car&& other) noexcept;
    Car& operator=(Car&& other) noexcept;

    ~Car();

    char* getMaker() const { return maker; }
    const Date& getDateOfProduction() const { return dop; }
    const TrunkType getTrunkType() const { return trunkType; }

    static void subtractFromCombinedHP(uint32_t hp) { combinedHP -= hp; }
    static void addToCombinedHP(uint32_t hp) { combinedHP += hp; }
    static uint32_t getCombinedHP() { return combinedHP; }


    static bool serialize(const Car& car, std::ostream& os);

private:
    char* readString(std::istream& is, int delim);
    char* copyString(const char* what);
    TrunkType getTrunkType(const char* str);

private:
    char* maker;
    Date dop;
    const TrunkType trunkType;
    uint32_t hp;
    uint32_t seats;

    static uint32_t combinedHP;
};