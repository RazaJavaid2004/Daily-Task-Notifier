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
    ui->taskList->clear();
    ui->taskList->addItem("➕ Add Task clicked");
}
