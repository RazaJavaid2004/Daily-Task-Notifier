#include "Task.h"
#include <sstream>
#include <iomanip>
using namespace std;

Task::Task(const string& title,
           const string& category,
           const tm& dueDate,
           int priority,
           const string& recurrenceType,
           bool isCompleted)
    : title(title),
    category(category),
    dueDate(dueDate),
    priority(priority),
    recurrenceType(recurrenceType),
    isCompleted(isCompleted) {}

string Task::toString() const {
    ostringstream oss;
    oss << title << "|"
        << category << "|"
        << put_time(&dueDate, "%Y-%m-%d") << "|"
        << priority << "|"
        << recurrenceType << "|"
        << (isCompleted ? "1" : "0");
    return oss.str();
}

string Task::getTitle() const {
    return title;
}

int Task::getPriority() const {
    return priority;
}

tm Task::getDueDate() const {
    return dueDate;
}

bool Task::getCompleted() const {
    return isCompleted;
}

void Task::setCompleted(bool completed) {
    isCompleted = completed;
}
