#include "Task.h"
#include <sstream>
#include <iomanip>

Task::Task(std::string t, std::string c, std::tm d, int p, bool r)
    : title(t), category(c), dueDate(d), priority(p), isRecurring(r) {}

std::string Task::toString() const {
    std::ostringstream oss;
    oss << title << "|" << category << "|"
        << std::put_time(&dueDate, "%Y-%m-%d") << "|"
        << priority << "|" << isRecurring;
    return oss.str();
}