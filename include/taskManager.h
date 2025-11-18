#pragma once
#include "Task.h"
#include <vector>
#include <string>
using namespace std;

class TaskManager {
private:
    vector<Task> tasks;
    bool isRecurringToday(const Task& task) const;

public:
    void loadTasks(const string& filename);
    void saveTasks(const string& filename);
    void addTask(const Task& task);
    void listAllTasks() const;
    void showTodayTasks();
    void sortByPriority();
    void searchByTitle(const string& keyword) const;
    vector<Task> getAllTasks() const;
    bool markTaskCompleted(const string& title);
    string getDataFilePath() const;
    string getArchivedFilePath() const;
    void overwriteTasks(const vector<Task>& updatedTasks);
};
