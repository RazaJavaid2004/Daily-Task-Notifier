#include "TaskManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

void TaskManager::loadTasks(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, category, dateStr;
        int priority;
        std::string recurrenceType;

        std::getline(iss, title, '|');
        std::getline(iss, category, '|');
        std::getline(iss, dateStr, '|');
        std::string priorityStr;
        std::getline(iss, priorityStr, '|');
        std::getline(iss, recurrenceType, '|');

        priority = std::stoi(priorityStr);

        std::tm date = {};
        std::istringstream dateStream(dateStr);
        dateStream >> std::get_time(&date, "%Y-%m-%d");

        tasks.emplace_back(title, category, date, priority, recurrenceType);
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

bool isToday(const std::tm& date) {
    std::time_t now = std::time(nullptr);
    std::tm* today = std::localtime(&now);
    return (date.tm_year == today->tm_year &&
            date.tm_mon == today->tm_mon &&
            date.tm_mday == today->tm_mday);
}

void TaskManager::showTodayTasks() {
    sortByPriority();
    std::cout << "Today's Tasks:\n";
    for (const auto& task : tasks) {
        if (isToday(task.dueDate) || isRecurringToday(task)) {
            std::cout << task.toString() << std::endl;
        }
    }
}

bool compareByPriority(const Task& a, const Task& b) {
    return a.priority < b.priority;
}

void TaskManager::sortByPriority() {
    std::sort(tasks.begin(), tasks.end(), compareByPriority);
}

bool TaskManager::isRecurringToday(const Task& task) const {
    if (task.recurrenceType == "none") return false;

    std::time_t now = std::time(nullptr);
    std::tm* today = std::localtime(&now);
    std::tm due = task.dueDate;

    if (task.recurrenceType == "weekly") {
        return (due.tm_wday == today->tm_wday);
    } else if (task.recurrenceType == "monthly") {
        return (due.tm_mday == today->tm_mday);
    }
    return false;
}

void TaskManager::searchByTitle(const std::string& keyword) const {
    std::cout << "Search Results for \"" << keyword << "\":\n";
    for (const auto& task : tasks) {
        if (task.title.find(keyword) != std::string::npos) {
            std::cout << task.toString() << std::endl;
        }
    }
}