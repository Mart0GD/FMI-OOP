#include "Schedule.hpp"

#pragma warning(disable: 4996)

Schedule::Schedule(const char* name) {
	this->name = strcpy(new char[strlen(name) + 1], name);

	tasks = new Task*[maxTasks];
	if (!tasks) {
		delete[] name;
		throw std::bad_alloc();
	}
	for (int i = 0; i < maxTasks; i++) tasks[i] = nullptr;
}

Schedule::Schedule(const Schedule& other) {
	name = strcpy(new char[strlen(name) + 1], name);

	tasks = new Task*[maxTasks];
	if (!tasks) {
		delete[] name;
		throw std::bad_alloc();
	}

	for (int i = 0; i < maxTasks; i++){
		tasks[i] = other.tasks[i];
	}
}
Schedule& Schedule::operator=(const Schedule& other) {
	if (this == &other) return *this;

	Schedule copy(other);
	*this = std::move(copy);

	return *this;
}

Schedule::Schedule(Schedule&& other) noexcept {
	name = other.name;
	tasks = other.tasks;

	other.name = nullptr;
	other.tasks = nullptr;
}
Schedule& Schedule::operator=(Schedule&& other) noexcept {
	if (this == &other) return *this;

	std::swap(name, other.name);
	std::swap(tasks, other.tasks);

	return *this;
}

Schedule::~Schedule() noexcept {
	delete[] name;
	delete[] tasks;
}

bool Schedule::add(Task& task, uint16_t hour, uint16_t minute) {
	if (hour > 23 || minute > 59) return false;

	int startTime = hour * 60 + minute;
	int endTime = startTime + task.getDuration();
	if (endTime / 60 > 23) return false; 

	bool canInsert = true;
	for (size_t i = startTime; i <= endTime; i++){
		if (!tasks[i]) continue;

		if (tasks[i]->getPriority() > task.getPriority()) {
			canInsert = false;
			break;
		}
	}
	if (!canInsert) return false;

	for (int i = startTime; i < endTime; i++){
		tasks[i] = &task; // we use refs --> if some tasks goes out of its scope we are cooked
	}

	return true;
}

bool Schedule::printTasksInHourInterval(uint16_t hour) {
	if (hour > 23) return false;

	for (int i = hour * 60; i < (hour + 1) * 60; i++){
		if (tasks[i]) {
			tasks[i]->print();
			i += tasks[i]->getDuration();
			std::cout << std::endl;
		}
	}

	return true;
}

Schedule Schedule::deserialize(std::istream& is) {
	if (!is) throw "bad file!";

	char nameBuffer[1024]{};
	is.getline(nameBuffer, sizeof(nameBuffer));
	if (!is || !*nameBuffer) throw "bad file!";

	Task** tasks = new Task * [maxTasks];

	Schedule s(nameBuffer);
	for (int i = 0; i < maxTasks; i++){
		char chr = is.get();
		if (chr == nullRead) {
			tasks[i] = nullptr;
			is.ignore(1024, '\n');
		}
		else {
			try
			{
				uint16_t duration = 0;
				is >> duration;

				tasks[i] = new Task(is);
				s.add(*tasks[i], duration / 60, duration % 60);
				is.ignore(1024, '\n');
				i += tasks[i]->getDuration();
			}
			catch (const std::exception&)
			{
				for (int ii = 0; ii < i; ii++)
				{
					delete tasks[i];
				}
				delete[] tasks;
			}
			
		}
		if (!is) {
			for (int ii = 0; ii < i; ii++)
			{
				delete tasks[i];
			}
			delete[] tasks;
			break;
		}
	}

	return s;
}
bool Schedule::serialize(const Schedule& s, std::ostream& os) {
	if (!os) throw "bad file!";

	os << s.name << '\n';
	if (!os) return false;
	
	for (int i = 0; i < maxTasks && os; i++){
		if (s.tasks[i]) {
			os << pointerRead << i << ' ';
			s.tasks[i]->serialize(*s.tasks[i], os);
			i += s.tasks[i]->getDuration();
		}
		else os << nullRead;
		if (i + 1 < maxTasks) os << '\n';
	}

	return os.good();
}

const uint32_t Schedule::maxTasks{ 24 * 60 };
const char Schedule::nullRead{'*'};
const char Schedule::pointerRead{ '&' };