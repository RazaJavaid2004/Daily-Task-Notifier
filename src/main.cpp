#include "TaskManager.h"
#include <iostream>

int main() {
    TaskManager manager;
    manager.loadTasks("data/tasks.txt");

    manager.sortByPriority();
    manager.showTodayTasks();

    std::cout << "\nSearch for 'Review':\n";
    manager.searchByTitle("Review");

    return 0;
}