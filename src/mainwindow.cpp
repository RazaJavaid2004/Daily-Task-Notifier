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
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::onExportClicked);
    connect(ui->markCompletedButton, &QPushButton::clicked, this, &MainWindow::onMarkCompletedClicked);
    connect(ui->archiveCompletedButton, &QPushButton::clicked, this, &MainWindow::onArchiveCompletedClicked);
    connect(ui->resetFiltersButton, &QPushButton::clicked, this, &MainWindow::onResetFiltersClicked);
    connect(ui->viewArchivedButton, &QPushButton::clicked, this, &MainWindow::onViewArchivedClicked);

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
    currentViewMode = VIEW_TODAY;

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

            QString priorityColor;
            switch (task.getPriority()) {
            case 1: priorityColor = "🔴"; break;
            case 2: priorityColor = "🟠"; break;
            case 3: priorityColor = "🟡"; break;
            case 4: priorityColor = "🟢"; break;
            case 5: priorityColor = "🔵"; break;
            default: priorityColor = "⚪"; break;
            }

            QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                                  .arg(priorityColor)
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

    resetCurrentViewBase();

    int selectedPriority = ui->priorityInput->value();
    bool found = false;
    std::vector<Task> filteredTasks;

    for (const Task& task : currentViewTasks) {
        if (task.getPriority() == selectedPriority) {
            filteredTasks.push_back(task);

            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
            QString recurrenceLabel;

            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString priorityColor;
            switch (task.getPriority()) {
            case 1: priorityColor = "🔴"; break;
            case 2: priorityColor = "🟠"; break;
            case 3: priorityColor = "🟡"; break;
            case 4: priorityColor = "🟢"; break;
            case 5: priorityColor = "🔵"; break;
            default: priorityColor = "⚪"; break;
            }

            QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                                  .arg(priorityColor)
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    currentViewTasks = filteredTasks;

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

    resetCurrentViewBase();

    bool found = false;
    std::vector<Task> filteredTasks;

    for (const Task& task : currentViewTasks) {
        QString category = QString::fromStdString(task.category).toLower();
        if (category == categoryFilter) {
            filteredTasks.push_back(task);

            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
            QString recurrenceLabel;

            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString priorityColor;
            switch (task.getPriority()) {
            case 1: priorityColor = "🔴"; break;
            case 2: priorityColor = "🟠"; break;
            case 3: priorityColor = "🟡"; break;
            case 4: priorityColor = "🟢"; break;
            case 5: priorityColor = "🔵"; break;
            default: priorityColor = "⚪"; break;
            }

            QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                                  .arg(priorityColor)
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    currentViewTasks = filteredTasks;

    if (!found) {
        ui->taskList->addItem("📂 No tasks found in category: " + categoryFilter);
    }
}

void MainWindow::onFilterByDateClicked()
{
    ui->taskList->clear();
    resetCurrentViewBase();

    QDate selectedDate = ui->dueDateInput->date();
    bool found = false;
    std::vector<Task> filteredTasks;

    for (const Task& task : currentViewTasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        if (dueDate == selectedDate) {
            filteredTasks.push_back(task);

            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
            QString recurrenceLabel;
            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString priorityColor;
            switch (task.getPriority()) {
            case 1: priorityColor = "🔴"; break;
            case 2: priorityColor = "🟠"; break;
            case 3: priorityColor = "🟡"; break;
            case 4: priorityColor = "🟢"; break;
            case 5: priorityColor = "🔵"; break;
            default: priorityColor = "⚪"; break;
            }

            QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                                  .arg(priorityColor)
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);
            ui->taskList->addItem(display);
            found = true;
        }
    }

    currentViewTasks = filteredTasks;

    if (!found) {
        ui->taskList->addItem("📅 No tasks due on selected date.");
    }
}

void MainWindow::onFilterByRecurrenceClicked()
{
    ui->taskList->clear();
    resetCurrentViewBase();

    QString recurrenceFilter = ui->recurrenceInput->text().trimmed().toLower();

    if (recurrenceFilter != "none" && recurrenceFilter != "daily" &&
        recurrenceFilter != "weekly" && recurrenceFilter != "monthly") {
        ui->taskList->addItem("⚠️ Invalid recurrence type. Use: none, daily, weekly, or monthly.");
        return;
    }

    bool found = false;
    std::vector<Task> filteredTasks;

    for (const Task& task : currentViewTasks) {
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        if (recurrence == recurrenceFilter) {
            filteredTasks.push_back(task);

            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            QString recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);

            QString priorityColor;
            switch (task.getPriority()) {
            case 1: priorityColor = "🔴"; break;
            case 2: priorityColor = "🟠"; break;
            case 3: priorityColor = "🟡"; break;
            case 4: priorityColor = "🟢"; break;
            case 5: priorityColor = "🔵"; break;
            default: priorityColor = "⚪"; break;
            }

            QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                                  .arg(priorityColor)
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    currentViewTasks = filteredTasks;

    if (!found) {
        ui->taskList->addItem("🔁 No tasks with recurrence: " + recurrenceFilter);
    }
}

void MainWindow::onCombinedFilterClicked()
{
    std::vector<Task> filteredTasks;
    ui->taskList->clear();
    resetCurrentViewBase();

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
            filteredTasks.push_back(task);

            QString recurrenceLabel;
            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString priorityColor;
            switch (task.getPriority()) {
            case 1: priorityColor = "🔴"; break;
            case 2: priorityColor = "🟠"; break;
            case 3: priorityColor = "🟡"; break;
            case 4: priorityColor = "🟢"; break;
            case 5: priorityColor = "🔵"; break;
            default: priorityColor = "⚪"; break;
            }

            QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                                  .arg(priorityColor)
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
            found = true;
        }
    }

    currentViewTasks = filteredTasks;

    if (!found) {
        ui->taskList->addItem("🧭 No tasks match all filters.");
    }
}

void MainWindow::onSortByDateClicked()
{
    ui->taskList->clear();
    resetCurrentViewBase();

    std::vector<Task> tasks = currentViewTasks;
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return std::mktime(const_cast<std::tm*>(&a.dueDate)) < std::mktime(const_cast<std::tm*>(&b.dueDate));
    });
    currentViewTasks = tasks;

    for (const Task& task : currentViewTasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        QString recurrenceLabel;

        if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
            recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
        }

        QString priorityColor;
        switch (task.getPriority()) {
        case 1: priorityColor = "🔴"; break;
        case 2: priorityColor = "🟠"; break;
        case 3: priorityColor = "🟡"; break;
        case 4: priorityColor = "🟢"; break;
        case 5: priorityColor = "🔵"; break;
        default: priorityColor = "⚪"; break;
        }

        QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                              .arg(priorityColor)
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
    resetCurrentViewBase();

    std::vector<Task> tasks = currentViewTasks;
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.getPriority() < b.getPriority();
    });
    currentViewTasks = tasks;

    for (const Task& task : currentViewTasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        QString recurrenceLabel;

        if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
            recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
        }

        QString priorityColor;
        switch (task.getPriority()) {
        case 1: priorityColor = "🔴"; break;
        case 2: priorityColor = "🟠"; break;
        case 3: priorityColor = "🟡"; break;
        case 4: priorityColor = "🟢"; break;
        case 5: priorityColor = "🔵"; break;
        default: priorityColor = "⚪"; break;
        }

        QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                              .arg(priorityColor)
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
    currentViewMode = VIEW_ALL;
    currentViewTasks = taskManager.getAllTasks();

    for (const Task& task : currentViewTasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
        QString recurrenceLabel;

        if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
            recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
        }

        QString priorityColor;
        switch (task.getPriority()) {
        case 1: priorityColor = "🔴"; break;
        case 2: priorityColor = "🟠"; break;
        case 3: priorityColor = "🟡"; break;
        case 4: priorityColor = "🟢"; break;
        case 5: priorityColor = "🔵"; break;
        default: priorityColor = "⚪"; break;
        }

        QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                              .arg(priorityColor)
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

void MainWindow::onExportClicked()
{
    QString rootPath = QCoreApplication::applicationDirPath();
    QDir projectRoot(rootPath);
    projectRoot.cdUp(); projectRoot.cdUp();
    QString filePath = projectRoot.filePath("data/exported_tasks.txt");

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->taskList->addItem("❌ Failed to export tasks.");
        return;
    }

    QTextStream out(&file);
    for (const Task& task : currentViewTasks) {
        QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
        out << QString::fromStdString(task.getTitle()) << "|"
            << (task.category.empty() ? "Uncategorized" : QString::fromStdString(task.category))
            << dueDate.toString("yyyy-MM-dd") << "|"
            << task.getPriority() << "|"
            << QString::fromStdString(task.recurrenceType) << "\n";
    }

    file.close();
    ui->taskList->addItem("✅ Exported current view to exported_tasks.txt");
}

void MainWindow::onMarkCompletedClicked()
{
    QListWidgetItem* selectedItem = ui->taskList->currentItem();
    if (!selectedItem) {
        ui->taskList->addItem("⚠️ Please select a task to mark as completed.");
        return;
    }

    QString selectedText = selectedItem->text();
    bool found = false;

    for (const Task& task : currentViewTasks) {
        QString title = QString::fromStdString(task.getTitle());
        if (selectedText.contains(title)) {
            taskManager.markTaskCompleted(task.getTitle());
            found = true;
            break;
        }
    }

    if (found) {
        ui->taskList->addItem("✅ Task marked as completed.");

        resetCurrentViewBase();
        ui->taskList->clear();

        if (currentViewTasks.empty()) {
            ui->taskList->addItem("📭 No tasks available.");
        } else {
            for (const Task& task : currentViewTasks) {
                QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
                QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
                QString recurrenceLabel;

                if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                    recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
                }

                QString priorityColor;
                switch (task.getPriority()) {
                case 1: priorityColor = "🔴"; break;
                case 2: priorityColor = "🟠"; break;
                case 3: priorityColor = "🟡"; break;
                case 4: priorityColor = "🟢"; break;
                case 5: priorityColor = "🔵"; break;
                default: priorityColor = "⚪"; break;
                }

                QString display = QString("%1 📌 %2 (Due: %3, Priority: %4)%5")
                                      .arg(priorityColor)
                                      .arg(QString::fromStdString(task.getTitle()))
                                      .arg(dueDate.toString("dd MMM yyyy"))
                                      .arg(task.getPriority())
                                      .arg(recurrenceLabel);

                ui->taskList->addItem(display);
            }
        }
    } else {
        ui->taskList->addItem("❌ Could not match task to mark as completed.");
    }
}

void MainWindow::onArchiveCompletedClicked()
{
    QString rootPath = QCoreApplication::applicationDirPath();
    QDir projectRoot(rootPath);
    projectRoot.cdUp(); projectRoot.cdUp();
    QString filePath = projectRoot.filePath("data/archived_tasks.txt");

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        ui->taskList->addItem("❌ Failed to archive tasks.");
        return;
    }

    QTextStream out(&file);
    std::vector<Task> remainingTasks;

    for (const Task& task : currentViewTasks) {
        if (task.getCompleted()) {
            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            out << QString::fromStdString(task.getTitle()) << "|"
                << (task.category.empty() ? "Uncategorized" : QString::fromStdString(task.category)) << "|"
                << dueDate.toString("yyyy-MM-dd") << "|"
                << task.getPriority() << "|"
                << QString::fromStdString(task.recurrenceType) << "\n";
        } else {
            remainingTasks.push_back(task);
        }
    }

    currentViewTasks = remainingTasks;
    file.close();
    ui->taskList->addItem("📦 Archived completed tasks.");
}

void MainWindow::onResetFiltersClicked()
{
    ui->searchBar->clear();
    ui->categoryInput->clear();
    ui->priorityInput->setValue(1);
    ui->dueDateInput->setDate(QDate::currentDate());
    ui->recurrenceInput->clear();

    currentViewTasks = taskManager.getAllTasks();
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

    if (currentViewTasks.empty()) {
        ui->taskList->addItem("📭 No tasks available.");
    }
}

void MainWindow::resetCurrentViewBase()
{
    currentViewTasks.clear();

    if (currentViewMode == VIEW_ALL) {
        currentViewTasks = taskManager.getAllTasks();
    } else if (currentViewMode == VIEW_TODAY) {
        QDate today = QDate::currentDate();
        int todayWeekday = today.dayOfWeek();
        int todayDayOfMonth = today.day();

        for (const Task& task : taskManager.getAllTasks()) {
            QDate dueDate(task.dueDate.tm_year + 1900, task.dueDate.tm_mon + 1, task.dueDate.tm_mday);
            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();

            bool show = false;
            if (dueDate == today) show = true;
            else if (recurrence == "daily") show = true;
            else if (recurrence == "weekly" && dueDate.dayOfWeek() == todayWeekday) show = true;
            else if (recurrence == "monthly" && dueDate.day() == todayDayOfMonth) show = true;

            if (show) currentViewTasks.push_back(task);
        }
    }
}

void MainWindow::onViewArchivedClicked()
{
    ui->taskList->clear();
    currentViewTasks.clear();
    currentViewMode = VIEW_ALL;  // Archived view is global

    for (const Task& task : taskManager.getAllTasks()) {
        if (task.getCompleted()) {
            currentViewTasks.push_back(task);

            QDate dueDate(task.getDueDate().tm_year + 1900, task.getDueDate().tm_mon + 1, task.getDueDate().tm_mday);
            QString recurrence = QString::fromStdString(task.recurrenceType).toLower();
            QString recurrenceLabel;

            if (recurrence == "weekly" || recurrence == "monthly" || recurrence == "daily") {
                recurrenceLabel = QString(" 🔁 (%1)").arg(recurrence);
            }

            QString priorityColor;
            switch (task.getPriority()) {
            case 1: priorityColor = "🔴"; break;
            case 2: priorityColor = "🟠"; break;
            case 3: priorityColor = "🟡"; break;
            case 4: priorityColor = "🟢"; break;
            case 5: priorityColor = "🔵"; break;
            default: priorityColor = "⚪"; break;
            }

            QString display = QString("✅ %1 📌 %2 (Due: %3, Priority: %4)%5")
                                  .arg(priorityColor)
                                  .arg(QString::fromStdString(task.getTitle()))
                                  .arg(dueDate.toString("dd MMM yyyy"))
                                  .arg(task.getPriority())
                                  .arg(recurrenceLabel);

            ui->taskList->addItem(display);
        }
    }

    if (currentViewTasks.empty()) {
        ui->taskList->addItem("📁 No archived tasks found.");
    }
}
