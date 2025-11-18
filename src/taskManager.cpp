#include "TaskManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <QDir>
#include <QCoreApplication>
using namespace std;

void TaskManager::loadTasks(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string title, category, dateStr, priorityStr, recurrenceType, completedStr;
        int priority;

        getline(iss, title, '|');
        getline(iss, category, '|');
        getline(iss, dateStr, '|');
        getline(iss, priorityStr, '|');
        getline(iss, recurrenceType, '|');
        getline(iss, completedStr, '|');

        priority = stoi(priorityStr);
        bool completed = (completedStr == "1");

        tm date = {};
        istringstream dateStream(dateStr);
        dateStream >> get_time(&date, "%Y-%m-%d");

        tasks.emplace_back(title, category, date, priority, recurrenceType, completed);
    }
}

void TaskManager::saveTasks(const string& filename) {
    ofstream file(getDataFilePath());
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

    ofstream file(filePath.toStdString(), ios::app);

    if (file.is_open()) {
        file << task.toString() << "\n";
        file.close();
    } else {
        cerr << "❌ Failed to open tasks.txt at: " << filePath.toStdString() << "\n";
    }
}

void TaskManager::listAllTasks() const {
    for (const auto& task : tasks) {
        cout << task.toString() << endl;
    }
}

bool isToday(const tm& date) {
    time_t now = time(nullptr);
    tm* today = localtime(&now);
    return (date.tm_year == today->tm_year &&
            date.tm_mon == today->tm_mon &&
            date.tm_mday == today->tm_mday);
}

void TaskManager::showTodayTasks() {
    sortByPriority();

    cout << "📅 Today's Tasks:\n";
    cout << "------------------\n";

    int count = 0;
    for (const auto& task : tasks) {
        if (isToday(task.dueDate) || isRecurringToday(task)) {
            cout << "🔸 " << task.toString() << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "🎉 No tasks for today. Enjoy your free time!\n";
    } else {
        cout << "\n✅ Total tasks for today: " << count << "\n";
        cout << "💡 Tip: Stay focused, one task at a time.\n";
    }
}

bool compareByPriority(const Task& a, const Task& b) {
    return a.priority < b.priority;
}

void TaskManager::sortByPriority() {
    sort(tasks.begin(), tasks.end(), compareByPriority);
}

bool TaskManager::isRecurringToday(const Task& task) const {
    if (task.recurrenceType == "none") return false;

    time_t now = time(nullptr);
    tm* today = localtime(&now);
    tm due = task.dueDate;

    if (task.recurrenceType == "weekly") {
        return (due.tm_wday == today->tm_wday);
    } else if (task.recurrenceType == "monthly") {
        return (due.tm_mday == today->tm_mday);
    }
    return false;
}

void TaskManager::searchByTitle(const string& keyword) const {
    cout << "Search Results for \"" << keyword << "\":\n";

    string loweredKeyword = keyword;
    transform(loweredKeyword.begin(), loweredKeyword.end(), loweredKeyword.begin(), ::tolower);

    for (const auto& task : tasks) {
        string loweredTitle = task.title;
        transform(loweredTitle.begin(), loweredTitle.end(), loweredTitle.begin(), ::tolower);

        if (loweredTitle.find(loweredKeyword) != string::npos) {
            cout << task.toString() << endl;
        }
    }
}

vector<Task> TaskManager::getAllTasks() const {
    return tasks;
}

bool TaskManager::markTaskCompleted(const string& title) {
    for (Task& task : tasks) {
        if (task.getTitle() == title) {
            task.setCompleted(true);
            return true;
        }
    }
    return false;
}

string TaskManager::getDataFilePath() const {
    QString rootPath = QCoreApplication::applicationDirPath();
    QDir projectRoot(rootPath);
    projectRoot.cdUp();
    projectRoot.cdUp();
    QString filePath = projectRoot.filePath("data/tasks.txt");
    return filePath.toStdString();
}

string TaskManager::getArchivedFilePath() const {
    QString rootPath = QCoreApplication::applicationDirPath();
    QDir projectRoot(rootPath);
    projectRoot.cdUp();
    projectRoot.cdUp();
    QString filePath = projectRoot.filePath("data/archived_tasks.txt");
    return filePath.toStdString();
}

void TaskManager::overwriteTasks(const vector<Task>& updatedTasks) {
    tasks = updatedTasks;
    ofstream file(getDataFilePath());
    for (const auto& task : tasks) {
        file << task.toString() << "\n";
    }
}
