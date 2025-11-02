#include "TaskManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <QDir>
#include <QCoreApplication>

void TaskManager::loadTasks(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, category, dateStr, priorityStr, recurrenceType, completedStr;
        int priority;

        std::getline(iss, title, '|');
        std::getline(iss, category, '|');
        std::getline(iss, dateStr, '|');
        std::getline(iss, priorityStr, '|');
        std::getline(iss, recurrenceType, '|');
        std::getline(iss, completedStr, '|');

        priority = std::stoi(priorityStr);
        bool completed = (completedStr == "1");

        std::tm date = {};
        std::istringstream dateStream(dateStr);
        dateStream >> std::get_time(&date, "%Y-%m-%d");

        tasks.emplace_back(title, category, date, priority, recurrenceType, completed);
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

    QString rootPath = QCoreApplication::applicationDirPath(); // build/debug folder
    QDir projectRoot(rootPath);
    projectRoot.cdUp();
    projectRoot.cdUp();
    QString filePath = projectRoot.filePath("data/tasks.txt");

    std::ofstream file(filePath.toStdString(), std::ios::app);

    if (file.is_open()) {
        file << task.toString() << "\n";
        file.close();
    } else {
        std::cerr << "❌ Failed to open tasks.txt at: " << filePath.toStdString() << "\n";
    }
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

    std::cout << "📅 Today's Tasks:\n";
    std::cout << "------------------\n";

    int count = 0;
    for (const auto& task : tasks) {
        if (isToday(task.dueDate) || isRecurringToday(task)) {
            std::cout << "🔸 " << task.toString() << std::endl;
            count++;
        }
    }

    if (count == 0) {
        std::cout << "🎉 No tasks for today. Enjoy your free time!\n";
    } else {
        std::cout << "\n✅ Total tasks for today: " << count << "\n";
        std::cout << "💡 Tip: Stay focused, one task at a time.\n";
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

    std::string loweredKeyword = keyword;
    std::transform(loweredKeyword.begin(), loweredKeyword.end(), loweredKeyword.begin(), ::tolower);

    for (const auto& task : tasks) {
        std::string loweredTitle = task.title;
        std::transform(loweredTitle.begin(), loweredTitle.end(), loweredTitle.begin(), ::tolower);

        if (loweredTitle.find(loweredKeyword) != std::string::npos) {
            std::cout << task.toString() << std::endl;
        }
    }
}

std::vector<Task> TaskManager::getAllTasks() const {
    return tasks;
}

void TaskManager::markTaskCompleted(const std::string& title)
{
    for (Task& task : tasks) {
        if (task.getTitle() == title) {
            task.setCompleted(true);
            break;
        }
    }
}
