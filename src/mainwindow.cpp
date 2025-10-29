#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(ui->viewTodayButton, &QPushButton::clicked, this, &MainWindow::onViewTodayClicked);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTaskClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSearchClicked()
{
    ui->taskList->clear();
    ui->taskList->addItem("🔍 Search clicked");
}

void MainWindow::onViewTodayClicked()
{
    ui->taskList->clear();
    ui->taskList->addItem("📅 View Today clicked");
}

void MainWindow::onAddTaskClicked()
{
    QString input = ui->searchBar->text().trimmed();

    if (input.isEmpty()) {
        ui->taskList->addItem("⚠️ Please enter a task.");
        return;
    }

    QString input = ui->searchBar->text().trimmed();
    QString category = ui->categoryInput->text().trimmed();
    QDate date = ui->dueDateInput->date();
    int priority = ui->priorityInput->value();
    QString reminder = ui->reminderInput->text().trimmed();

    if (input.isEmpty()) {
        ui->taskList->addItem("⚠️ Please enter a task.");
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
        reminder.toStdString()
        );

    taskManager.addTask(newTask);
    ui->taskList->addItem("✅ Task added: " + input);
    ui->searchBar->clear();
    ui->categoryInput->clear();
    ui->reminderInput->clear();

    Task newTask(title, category, dueDate, priority, reminder);
    taskManager.addTask(newTask);

    ui->taskList->addItem("✅ Task added: " + input);
    ui->searchBar->clear();
}
