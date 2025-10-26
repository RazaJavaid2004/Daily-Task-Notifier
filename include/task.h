#pragma once
#include <string>
#include <ctime>

class Task {
public:
    std::string title;
    std::string category;
    std::tm dueDate;
    int priority;
    std::string recurrenceType;

    Task(std::string t, std::string c, std::tm d, int p, std::string r);
    std::string toString() const;
};