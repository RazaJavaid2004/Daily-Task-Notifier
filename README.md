# 🗓️ Daily Task Notifier (C++ Desktop App)

A lightweight desktop application that displays your routine tasks for the day upon computer startup. Built in C++ to demonstrate practical applications of core data structures and algorithms.

---

## 📌 Project Overview

* **Language** : C++
* **Purpose** : Help users remember daily routine tasks by showing them at system startup
* **Scope** : Console-based app with file I/O, task filtering, recurrence logic, and priority sorting
* **Status** : Phase 4 completed ✅

---

## 📁 Project Structure

```

/DailyTaskNotifier
│
├── include/                     # Header files (interfaces)
│   ├── Task.h                   # Task class declaration
│   └── TaskManager.h            # TaskManager class declaration
│
├── src/                         # Source files (implementations)
│   ├── main.cpp                 # Entry point of the application
│   ├── Task.cpp                 # Task class implementation
│   └── TaskManager.cpp          # TaskManager implementation
│
├── data/                        # Persistent storage
│   └── tasks.txt                # Task data file (text format)
│
├── README.md                    # Project documentation

```

---

## 🧱 Data Structures Used

| Structure                             | Purpose                                                 |
| ------------------------------------- | ------------------------------------------------------- |
| `class Task`                          | Encapsulates task details (title, date, priority, etc.) |
| `std::vector<Task>`                   | Stores all tasks dynamically                            |
| `std::map` *(planned)*                | Group tasks by date or category                         |
| `std::priority_queue` *(planned)*     | Sort tasks by urgency                                   |
| `std::ifstream` / `std::ofstream`     | File I/O for persistent storage                         |

---

## ⚙️ Algorithms Implemented

| Algorithm          | Purpose                                                 |
| ------------------ | ------------------------------------------------------- |
| Date parsing       | Converts string to `std::tm` for comparison             |
| Task serialization | Converts task to string format for saving              |
| File parsing       | Reads tasks from `tasks.txt` and loads into memory     |
| Recurrence logic   | Supports `none`, `weekly`, and `monthly` recurrence    |
| Priority sorting   | Sorts tasks in ascending order of urgency              |
| Title search       | Finds tasks by keyword match (case-insensitive)        |

---

## ✅ Features Completed (Phase 1–4)

* [X] Finalized project scope and DSA plan
* [X] Designed `Task` class with serialization
* [X] Implemented `TaskManager` with:
  * Task loading from file
  * Task saving to file
  * Task creation and listing
  * Task filtering by today's date
  * Recurrence support (`weekly`, `monthly`)
  * Priority-based sorting
  * Case-insensitive keyword search by title
* [X] Startup banner and motivational message
* [X] Formatted display of today's tasks with task count
* [X] CLI menu with interactive options

---

## 📦 Sample Task Format (`tasks.txt`)

```

Title|Category|YYYY-MM-DD|Priority|RecurrenceType
Water Plants|Personal|2025-10-27|2|weekly
Finish DSA Assignment|Academic|2025-10-27|1|none
Call Mom|Personal|2025-10-28|3|none
Weekly Review|Academic|2025-10-20|2|weekly
Pay Rent|Finance|2025-10-01|1|monthly

```

---

## 🚀 Next Phase: GUI Integration

* Choose GUI framework (Qt, ImGui, etc.)
* Display task list in graphical interface
* Add search bar, filters, and task creation form
* Connect GUI elements to backend logic
* Ensure emoji rendering and startup polish

---

## 👨‍💻 Author

**Muhammad Raza**

---