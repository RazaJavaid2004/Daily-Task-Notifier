#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(ui->viewTodayButton, &QPushButton::clicked, this, &MainWindow::onViewTodayClicked);
    connect(ui->viewAllButton, &QPushButton::clicked, this, &MainWindow::onViewAllClicked);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTaskClicked);
    connect(ui->filterPriorityButton, &QPushButton::clicked, this, &MainWindow::onFilterByPriorityClicked);
    connect(ui->filterCategoryButton, &QPushButton::clicked, this, &MainWindow::onFilterByCategoryClicked);
    connect(ui->combinedFilterButton, &QPushButton::clicked, this, &MainWindow::onCombinedFilterClicked);
    connect(ui->filterDateButton, &QPushButton::clicked, this, &MainWindow::onFilterByDateClicked);
    connect(ui->filterRecurrenceButton, &QPushButton::clicked, this, &MainWindow::onFilterByRecurrenceClicked);
    connect(ui->sortByDateButton, &QPushButton::clicked, this, &MainWindow::onSortByDateClicked);
    connect(ui->sortByPriorityButton, &QPushButton::clicked, this, &MainWindow::onSortByPriorityClicked);

    // Resolve path to tasks.txt
    QString rootPath = QCoreApplication::applicationDirPath();
    QDir projectRoot(rootPath);
    projectRoot.cdUp(); projectRoot.cdUp();
    QString filePath = projectRoot.filePath("data/tasks.txt");

    // Load tasks and initialize view
    taskManager.loadTasks(filePath.toStdString());
    currentViewTasks = taskManager.getAllTasks();

    // Display each task manually with recurrence awareness
    ui->taskList->clear();
    for (const Task& task : currentViewTasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        QString recurrenceLabel;

        if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
            recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
        }

        QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                              .arg(QString::fromStdString(task.getTitle()))
                              .arg(dueDate.toString("dd MMM yyyy"))
                              .arg(task.getPriority())
                              .arg(recurrenceLabel);

        ui->taskList->addItem(display);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSearchClicked()
{
    ui->taskList->clear();

    QString keyword = ui->searchBar->text().trimmed().toLower();

    if (keyword.isEmpty()) {
        ui->taskList->addItem("⚠️ Please enter a search keyword.");
        return;
    }

    bool found = false;

    for (const Task& task : currentViewTasks) {
        QString title = QString::fromStdString(task.getTitle()).toLower();
        QString category = QString::fromStdString(task.category).toLower();

        if (title.contains(keyword) || category.contains(keyword)) {
            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
            QString recurrenceLabel;

            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    if (!found) {
        ui->taskList->addItem("🔎 No matching tasks found.");
    }
}

void MainWindow::onViewTodayClicked()
{
    ui->taskList->clear();
    currentViewTasks.clear();

    QDate today = QDate::currentDate();
    int todayWeekday = today.dayOfWeek();
    int todayDayOfMonth = today.day();

    for (const Task& task : taskManager.getAllTasks()) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();

        bool show = false;

        if (dueDate == today) {
            show = true;
        } else if (recurrence == "daily") {
            show = true;
        } else if (recurrence == "weekly" && dueDate.dayOfWeek() == todayWeekday) {
            show = true;
        } else if (recurrence == "monthly" && dueDate.day() == todayDayOfMonth) {
            show = true;
        }

        if (show) {
            currentViewTasks.push_back(task);

            QString recurrenceLabel;
            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
        }
    }

    if (currentViewTasks.empty()) {
        ui->taskList->addItem("📭 No tasks due today.");
    }
}

void MainWindow::onAddTaskClicked()
{
    QString input = ui->searchBar->text().trimmed();
    QString category = ui->categoryInput->text().trimmed();
    QDate date = ui->dueDateInput->date();
    int priority = ui->priorityInput->value();
    QString recurrence = ui->recurrenceInput->text().trimmed().toLower();

    if (input.isEmpty()) {
        ui->taskList->addItem("⚠️ Please enter a task.");
        return;
    }

    if (recurrence != "none" && recurrence != "weekly" && recurrence != "monthly" && recurrence != "daily") {
        ui->taskList->addItem("⚠️ Invalid recurrence type. Use: none, daily, weekly, or monthly.");
        return;
    }

    std::tm dueDate = {};
    dueDate.tm_year = date.year() - 1900;
    dueDate.tm_mon = date.month() - 1;
    dueDate.tm_mday = date.day();

    Task newTask(
        input.toStdString(),
        category.toStdString(),
        dueDate,
        priority,
        recurrence.toStdString()
        );

    taskManager.addTask(newTask);
    ui->taskList->addItem("✅ Task added: " + input);
    ui->searchBar->clear();
    ui->categoryInput->clear();
    ui->recurrenceInput->clear();
}

void MainWindow::onFilterByPriorityClicked()
{
    ui->taskList->clear();

    int selectedPriority = ui->priorityInput->value();
    bool found = false;

    for (const Task& task : currentViewTasks) {
        if (task.getPriority() == selectedPriority) {
            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
            QString recurrenceLabel;

            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    if (!found) {
        ui->taskList->addItem("🎯 No tasks with priority " + QString::number(selectedPriority));
    }
}

void MainWindow::onFilterByCategoryClicked()
{
    ui->taskList->clear();

    QString categoryFilter = ui->categoryInput->text().trimmed().toLower();

    if (categoryFilter.isEmpty()) {
        ui->taskList->addItem("⚠️ Please enter a category to filter.");
        return;
    }

    bool found = false;

    for (const Task& task : currentViewTasks) {
        QString category = QString::fromStdString(task.category).toLower();

        if (category == categoryFilter) {
            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
            QString recurrenceLabel;

            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    if (!found) {
        ui->taskList->addItem("📂 No tasks found in category: " + categoryFilter);
    }
}



void MainWindow::onFilterByDateClicked()
{
    ui->taskList->clear();
    QDate selectedDate = ui->dueDateInput->date();
    bool found = false;

    for (const Task& task : currentViewTasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        if (dueDate == selectedDate) {
            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
            QString recurrenceLabel;
            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    if (!found) {
        ui->taskList->addItem("📅 No tasks due on selected date.");
    }
}

void MainWindow::onFilterByRecurrenceClicked()
{
    ui->taskList->clear();
    QString recurrenceFilter = ui->recurrenceInput->text().trimmed().toLower();

    if (recurrenceFilter != "none" && recurrenceFilter != "daily" &&
        recurrenceFilter != "weekly" && recurrenceFilter != "monthly") {
        ui->taskList->addItem("⚠️ Invalid recurrence type. Use: none, daily, weekly, or monthly.");
        return;
    }

    bool found = false;

    for (const Task& task : currentViewTasks) {
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        if (recurrence == recurrenceFilter) {
            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            QString recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);

            QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    if (!found) {
        ui->taskList->addItem("🔁 No tasks with recurrence: " + recurrenceFilter);
    }
}

void MainWindow::onCombinedFilterClicked()
{
    ui->taskList->clear();

    QString keyword = ui->searchBar->text().trimmed().toLower();
    QString categoryFilter = ui->categoryInput->text().trimmed().toLower();
    int priorityFilter = ui->priorityInput->value();
    QDate selectedDate = ui->dueDateInput->date();
    QString recurrenceFilter = ui->recurrenceInput->text().trimmed().toLower();

    bool found = false;

    for (const Task& task : currentViewTasks) {
        QString title = QString::fromStdString(task.getTitle()).toLower();
        QString category = QString::fromStdString(task.category).toLower();
        int priority = task.getPriority();
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();

        bool matchesKeyword = keyword.isEmpty() || title.contains(keyword) || category.contains(keyword);
        bool matchesCategory = categoryFilter.isEmpty() || category == categoryFilter;
        bool matchesPriority = priority == priorityFilter;
        bool matchesDate = !selectedDate.isValid() || dueDate == selectedDate;
        bool matchesRecurrence = recurrenceFilter.isEmpty() || recurrence == recurrenceFilter;

        if (matchesKeyword && matchesCategory && matchesPriority && matchesDate && matchesRecurrence) {
            QString recurrenceLabel;
            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(priority)
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    if (!found) {
        ui->taskList->addItem("🧭 No tasks match all filters.");
    }
}

void MainWindow::onSortByDateClicked()
{
    ui->taskList->clear();

    std::vector<Task> tasks = currentViewTasks;
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return std::mktime(const_cast<std::tm*>(&a.dueDate)) < std::mktime(const_cast<std::tm*>(&b.dueDate));
    });

    for (const Task& task : tasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        QString recurrenceLabel;

        if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
            recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
        }

        QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                              .arg(QString::fromStdString(task.getTitle()))
                              .arg(dueDate.toString("dd MMM yyyy"))
                              .arg(task.getPriority())
                              .arg(recurrenceLabel);

        ui->taskList->addItem(display);
    }
}

void MainWindow::onSortByPriorityClicked()
{
    ui->taskList->clear();

    std::vector<Task> tasks = currentViewTasks;
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.getPriority() < b.getPriority(); // 5 = highest, 1 = lowest
    });

    for (const Task& task : tasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        QString recurrenceLabel;

        if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
            recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
        }

        QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                              .arg(QString::fromStdString(task.getTitle()))
                              .arg(dueDate.toString("dd MMM yyyy"))
                              .arg(task.getPriority())
                              .arg(recurrenceLabel);

        ui->taskList->addItem(display);
    }
}

void MainWindow::onViewAllClicked()
{
    ui->taskList->clear();
    currentViewTasks = taskManager.getAllTasks();

    for (const Task& task : currentViewTasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        QString recurrenceLabel;

        if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
            recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
        }

        QString display = QString("📌 %1 (Due: %2, Priority: %3)%4")
                              .arg(QString::fromStdString(task.getTitle()))
                              .arg(dueDate.toString("dd MMM yyyy"))
                              .arg(task.getPriority())
                              .arg(recurrenceLabel);

        ui->taskList->addItem(display);
    }

    if (currentViewTasks.empty()) {
        ui->taskList->addItem("📭 No tasks available.");
    }
}
