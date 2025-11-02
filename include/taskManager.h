#pragma once
#include "Task.h"
#include <vector>
#include <string>

class TaskManager {
private:
    std::vector<Task> tasks;
    bool isRecurringToday(const Task& task) const;

public:
    void loadTasks(const std::string& filename);
    void saveTasks(const std::string& filename);
    void addTask(const Task& task);
    void listAllTasks() const;
    void showTodayTasks();
    void sortByPriority();
    void searchByTitle(const std::string& keyword) const;
    std::vector<Task> getAllTasks() const;
    void markTaskCompleted(const std::string& title);
};
