#include<iostream>
#include<fstream>

int main3() {
	std::ifstream file("Template_for_task_3.txt");

	int index = file.tellg();
	if (!file.is_open()) {
		std::cerr << "Cannot open file!";
	}
	file.clear();
	file.seekg(0, std::ios::end);
	std::cout << file.tellg();


	file.seekg(index, std::ios::beg);
	file.close();
	return 0;
}