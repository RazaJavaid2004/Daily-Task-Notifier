#pragma once

#include <QMainWindow>
#include "taskManager.h"
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchClicked();
    void onViewTodayClicked();
    void onAddTaskClicked();
    void onFilterByPriorityClicked();
    void onFilterByCategoryClicked();
    void onFilterByDateClicked();
    void onFilterByRecurrenceClicked();
    void onCombinedFilterClicked();
    void onSortByDateClicked();
    void onSortByPriorityClicked();
    void onViewAllClicked();

private:
    Ui::MainWindow *ui;
    TaskManager taskManager;
    std::vector<Task> currentViewTasks;
};
