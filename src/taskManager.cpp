#include "TaskManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

void TaskManager::loadTasks(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, category, dateStr;
        int priority;
        bool recurring;

        std::getline(iss, title, '|');
        std::getline(iss, category, '|');
        std::getline(iss, dateStr, '|');
        iss >> priority;
        iss.ignore();
        iss >> recurring;

        std::tm date = {};
        std::istringstream dateStream(dateStr);
        dateStream >> std::get_time(&date, "%Y-%m-%d");

        tasks.emplace_back(title, category, date, priority, recurring);
    }
}

void TaskManager::saveTasks(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& task : tasks) {
        file << task.toString() << "\n";
    }
}

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
}

void TaskManager::listAllTasks() const {
    for (const auto& task : tasks) {
        std::cout << task.toString() << std::endl;
    }
}