#pragma once
/*
Една задача се характеризира с:
    - описание (символен низ, който може да има произволна дължина);
    - приоритет (цяло положително число, по-голямата стойност означава по-голям приоритет);
    - статус (булева стойност, дали задачата вече е свършена или не);
    - продължителност (положително число в минути).

Трябва да вземете предвид следните изисквания:
    - описанието на задачата е нещо, което се задава при създаването ѝ и повече не трябва да може да се променя;
    - една задача винаги се създава като незавършена. По-късно може да бъде обявена за завършена, но не се допуска отменяне на тази промяна, т.е. веднъж завършена, задачата не може отново да бъде върната в статус незавършена;
    - стойността на максималния възможен приоритет е зададена за всички задачи. Тя трябва да е част от класа, еднаква за всички обекти и непроменима.

За класа Task:
    - дефинирайте подходящи конструктори и нужните методи за осигуряване на коректен жизнен цикъл;
    - дефинирайте метод (или по избор оператор) за запис в текстов поток;
    - дефинирайте конструктор, който създава обект по данни от текстов поток (съгласно формата, който сте използвали за запис в предната функция);
    - дефинирайте подходящи методи за достъп до членовете.
*/
#include <iostream>

class Task {

public:
    Task(const char* description, uint32_t priority, uint16_t duration);
    Task(std::istream& is = std::cin);

    Task(const Task& other);
    Task& operator=(const Task& other);

    ~Task() noexcept;

    const char* getDescription() const { return description; }
    uint32_t getPriority() const { return priority; }
    bool getStatus() const { return status; }
    uint16_t getDuration() const { return duration; }

    bool finish();
    void print();

    static bool serialize(const Task& task , std::ostream& os);

private:
    char* copyString(const char* what);
    char* readString(std::istream& is);

private:
    const char* description;
    uint32_t priority;
    bool status;
    uint16_t duration;

    static const int MAX_PRIORITY;
};