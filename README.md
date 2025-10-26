# 🗓️ Daily Task Notifier (C++ Desktop App)

A lightweight desktop application that displays your routine tasks for the day upon computer startup. Built in C++ to demonstrate practical applications of core data structures and algorithms.

---

## 📌 Project Overview

- **Language**: C++
- **Purpose**: Help users remember daily routine tasks by showing them at system startup
- **Scope**: Console-based app with file I/O, task filtering, and priority sorting
- **Status**: Phase 2 completed ✅

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

| Structure | Purpose |
|-----------|---------|
| `class Task` | Encapsulates task details (title, date, priority, etc.) |
| `std::vector<Task>` | Stores all tasks dynamically |
| `std::map` *(planned)* | Group tasks by date or category |
| `std::priority_queue` *(planned)* | Sort tasks by urgency |
| `std::ifstream` / `std::ofstream` | File I/O for persistent storage |

---

## ⚙️ Algorithms Implemented

| Algorithm | Purpose |
|-----------|---------|
| Date parsing | Converts string to `std::tm` for comparison |
| Task serialization | Converts task to string format for saving |
| File parsing | Reads tasks from `tasks.txt` and loads into memory |

---

## 🧪 Features Completed (Phase 1 & 2)

- [x] Finalized project scope and DSA plan
- [x] Designed `Task` class with serialization
- [x] Implemented `TaskManager` with:
  - Task loading from file
  - Task saving to file
  - Task creation and listing
- [x] Sample task added and persisted

---

## 📦 Sample Task Format (`tasks.txt`)

```

Title|Category|YYYY-MM-DD|Priority|Recurring
Water Plants|Personal|2025-10-27|2|1
Finish DSA Assignment|Academic|2025-10-27|1|0

```

---

## 🚀 Next Phase: Algorithms & Sorting

- Filter tasks for today using system date
- Sort tasks by priority
- Add recurrence logic (weekly/monthly)
- Implement search by title or date

---

## 👨‍💻 Author

**Muhammad Raza**  

---