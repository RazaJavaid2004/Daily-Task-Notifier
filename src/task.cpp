#include "Task.h"
#include <sstream>
#include <iomanip>

Task::Task(std::string t, std::string c, std::tm d, int p, std::string r)
    : title(t), category(c), dueDate(d), priority(p), recurrenceType(r) {}

std::string Task::toString() const {
    std::ostringstream oss;
    oss << title << "|" << category << "|"
        << std::put_time(&dueDate, "%Y-%m-%d") << "|"
        << priority << "|" << recurrenceType;
    return oss.str();
}