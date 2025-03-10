#include<iostream>
#include<fstream>

int main3() {
	std::ifstream file("Template_for_task_3.txt");

	if (!file.is_open()) {
		std::cerr << "Cannot open file!";
	}

	file.seekg(0, std::ios::end);
	std::cout << file.tellg();
	file.seekg(0);
	file.close();
	return 0;
}