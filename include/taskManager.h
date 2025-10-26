#pragma once

#include "Task.h"
#include <vector>
#include <string>

class TaskManager {
private:
    std::vector<Task> tasks;

public:
    void loadTasks(const std::string& filename);
    void saveTasks(const std::string& filename);
    void addTask(const Task& task);
    void listAllTasks() const;
};