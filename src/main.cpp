#include "TaskManager.h"
#include <iostream>

int main() {
    TaskManager manager;
    manager.loadTasks("data/tasks.txt");

    // Add a sample task
    std::tm date = {};
    date.tm_year = 125; // 2025 - 1900
    date.tm_mon = 9;    // October
    date.tm_mday = 27;

    Task newTask("Finish DSA Assignment", "Academic", date, 1, false);
    manager.addTask(newTask);
    manager.saveTasks("data/tasks.txt");

    std::cout << "All Tasks:\n";
    manager.listAllTasks();

    return 0;
}