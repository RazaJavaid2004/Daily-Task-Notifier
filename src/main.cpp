#include "TaskManager.h"
#include <iostream>

int main() {
    TaskManager manager;
    manager.loadTasks("data/tasks.txt");

    int choice;
    std::string keyword;

    do {
        std::cout << "\n=====================================\n";
        std::cout << "     🗓️ Daily Task Notifier\n";
        std::cout << "=====================================\n";
        std::cout << "1. View all tasks\n";
        std::cout << "2. View today's tasks\n";
        std::cout << "3. Search by title\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                manager.listAllTasks();
                break;
            case 2:
                manager.showTodayTasks();
                break;
            case 3:
                std::cout << "Enter keyword to search: ";
                std::cin.ignore();
                std::getline(std::cin, keyword);
                manager.searchByTitle(keyword);
                break;
            case 4:
                std::cout << "Goodbye, Raza!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}