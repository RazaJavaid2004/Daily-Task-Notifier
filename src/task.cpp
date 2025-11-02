#include "Task.h"
#include <sstream>
#include <iomanip>

Task::Task(const std::string& title,
           const std::string& category,
           const std::tm& dueDate,
           int priority,
           const std::string& recurrenceType,
           bool isCompleted)
    : title(title),
    category(category),
    dueDate(dueDate),
    priority(priority),
    recurrenceType(recurrenceType),
    isCompleted(isCompleted) {}

std::string Task::toString() const {
    std::ostringstream oss;
    oss << title << "|"
        << category << "|"
        << std::put_time(&dueDate, "%Y-%m-%d") << "|"
        << priority << "|"
        << recurrenceType << "|"
        << (isCompleted ? "1" : "0");
    return oss.str();
}

std::string Task::getTitle() const {
    return title;
}

int Task::getPriority() const {
    return priority;
}

std::tm Task::getDueDate() const {
    return dueDate;
}

bool Task::getCompleted() const {
    return isCompleted;
}

void Task::setCompleted(bool completed) {
    isCompleted = completed;
}
