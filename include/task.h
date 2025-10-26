#pragma once

#include <string>
#include <ctime>

class Task {
public:
    std::string title;
    std::string category;
    std::tm dueDate;
    int priority;
    bool isRecurring;

    Task(std::string t, std::string c, std::tm d, int p, bool r);
    std::string toString() const;
};