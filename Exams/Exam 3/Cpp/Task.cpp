#include "task.hpp"
#pragma warning(disable: 4996)
Task::Task(const char* description, uint32_t priority, uint16_t duration) 
	: description(copyString(description)), status(false)
{ 
	if (priority > MAX_PRIORITY) {
		delete[] description;
		throw std::invalid_argument("Invalid priority level!");
	}
	if (duration / 60 > 23) {
		delete[] description;
		throw std::invalid_argument("Invalid duration!");
	}

	this->priority = priority;
	this->duration = duration;
}
Task::Task(std::istream& is) 
	: description(copyString(readString(is))), status(false){
	is >> priority;
	if (!is || priority > MAX_PRIORITY) {
		delete[] description;
		throw "bad file!";
	}
	is >> duration;
	if(!is || duration / 60 > 23) {
		delete[] description;
		throw "bad file!";
	}
}

Task::Task(const Task& other)
	: description(copyString(other.description)),
	  status(other.status), priority(other.priority), duration(other.duration)
{ }
Task& Task::operator=(const Task& other) {
	if (this == &other) return *this;

	priority = other.priority;
	duration = other.duration;
	status = other.status;

	return *this;
}


Task::~Task() noexcept {
	delete[] description;
}

bool Task::finish() {
	if (status) return false;
	status = true;

	return true;
}
char* Task::copyString(const char* what) {
	if (!what || !*what) throw std::invalid_argument("invalid string!");

	char* temp = new char[strlen(what) + 1];
	return strcpy(temp, what);
}
char* Task::readString(std::istream& is) {
	static char buff[1024]{};
	if (!is) return buff;

	is.getline(buff, sizeof(buff), ',');
	return buff;
}
void Task::print() {
	std::cout << description << ' ' << priority << ' ' << duration;
}

bool Task::serialize(const Task& task, std::ostream& os) {
	if (!os) return false;

	os << task.description << ',';
	if(!os) return false;
	os << task.priority << ' ';
	if (!os) return false;
	os << task.duration;

	return os.good();
}

const int Task::MAX_PRIORITY{ 6 };