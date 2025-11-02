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

    Task(const std::string& title,
               const std::string& category,
               const std::tm& dueDate,
               int priority,
               const std::string& recurrenceType,
               bool isCompleted = false);

    std::string toString() const;

    std::string getTitle() const;
    int getPriority() const;
    std::tm getDueDate() const;
    bool isCompleted;
    bool getCompleted() const;
    void setCompleted(bool completed);
};
