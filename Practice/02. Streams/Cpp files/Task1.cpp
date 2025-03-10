#include<iostream>
#include<fstream>

int main1() {

	std::ifstream file("Task1.cpp");
	if (!file.good()){
		std::cerr << "Cannot open file!" << std::endl;
	}

	char c = ' ';
	while (file.peek() != EOF){
		file.get(c);
		std::cout << c;
	}

	file.close();
	return 0;
}