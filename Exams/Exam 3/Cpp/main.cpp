#include "task.hpp"
#include "Schedule.hpp"
#include <fstream>

int main() {

	try
	{
		Task t1("Do laundry", 3, 2);
		Task t2("kill somebody", 6, 10);
		Task t3("sleep....", 1, 20);

		Schedule s("My day");

		s.add(t1, 12, 20);
		s.add(t2, 10, 00);
		s.add(t3, 10, 30);

		Task* t = s.getTaskWithMostPriorityNow(9, 59);
		s.printTasksInHourInterval(10);

		std::ofstream i("Text.txt");
		if (!i.is_open()) {
			delete t;
			throw "bad file!";
		}

		s.serialize(s, i);
		i.close();

		std::ifstream o("Text.txt", std::ios::in);
		if (!o.is_open()) {
			delete t;
			throw "bad file!";
		}

		Schedule s2 = s.deserialize(o);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	return 0;
}