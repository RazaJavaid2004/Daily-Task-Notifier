#pragma once
#include <string>
#include <ctime>
using namespace std;

class Task {
public:
    string title;
    string category;
    tm dueDate;
    int priority;
    string recurrenceType;
    bool isCompleted;

    Task(const string& title,
               const string& category,
               const tm& dueDate,
               int priority,
               const string& recurrenceType,
               bool isCompleted = false);

    string toString() const;

    string getTitle() const;
    int getPriority() const;
    tm getDueDate() const;
    bool getCompleted() const;
    void setCompleted(bool completed);
};
