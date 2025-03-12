#pragma once
#ifndef EXAM_HPP
#define EXAM_HPP

#define FN_SIZE 11
#define EXAM_STR_LEN 200

struct Exam {
	char FN[FN_SIZE] = {};
	double grade;
	char subject[EXAM_STR_LEN] = {};
};

Exam* readExams(const char* fileName, int& size);
void readExam(Exam& exam, std::ifstream& file);
#endif