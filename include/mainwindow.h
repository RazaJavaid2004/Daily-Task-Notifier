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
    void onExportClicked();
    void onMarkCompletedClicked();
    void onArchiveCompletedClicked();
    void onResetFiltersClicked();
    void resetCurrentViewBase();
    void onViewCompletedClicked();
    void onArchivedToggleChanged(int state);

private:
    Ui::MainWindow *ui;
    TaskManager taskManager;
    std::vector<Task> currentViewTasks;

    enum ViewMode { VIEW_ALL, VIEW_TODAY, VIEW_ARCHIVED };
    ViewMode currentViewMode = VIEW_ALL;
};
