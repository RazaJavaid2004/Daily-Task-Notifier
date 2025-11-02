/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *headerLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QHBoxLayout *searchLayout;
    QLineEdit *searchBar;
    QPushButton *searchButton;
    QGroupBox *filtersGroup;
    QHBoxLayout *taskDetailsLayout;
    QLineEdit *categoryInput;
    QPushButton *filterCategoryButton;
    QSpinBox *priorityInput;
    QPushButton *filterPriorityButton;
    QDateEdit *dueDateInput;
    QPushButton *filterDateButton;
    QLineEdit *recurrenceInput;
    QPushButton *filterRecurrenceButton;
    QPushButton *combinedFilterButton;
    QPushButton *sortByDateButton;
    QPushButton *sortByPriorityButton;
    QHBoxLayout *mainContentRow;
    QVBoxLayout *taskListColumn;
    QListWidget *taskList;
    QHBoxLayout *viewControls;
    QPushButton *viewTodayButton;
    QCheckBox *viewCompletedCheckBox;
    QGroupBox *actionsGroup;
    QVBoxLayout *actionsLayout;
    QPushButton *addTaskButton;
    QPushButton *exportButton;
    QPushButton *markCompletedButton;
    QPushButton *archiveCompletedButton;
    QPushButton *resetFiltersButton;
    QMenuBar *menubar;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1160, 640);
        MainWindow->setMinimumSize(QSize(1160, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        headerLayout = new QVBoxLayout();
        headerLayout->setObjectName("headerLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignHCenter);

        headerLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(centralwidget);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setAlignment(Qt::AlignHCenter);

        headerLayout->addWidget(subtitleLabel);


        verticalLayout->addLayout(headerLayout);

        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        searchBar = new QLineEdit(centralwidget);
        searchBar->setObjectName("searchBar");
        searchBar->setMinimumSize(QSize(300, 32));

        searchLayout->addWidget(searchBar);

        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");
        searchButton->setMinimumSize(QSize(100, 32));

        searchLayout->addWidget(searchButton);


        verticalLayout->addLayout(searchLayout);

        filtersGroup = new QGroupBox(centralwidget);
        filtersGroup->setObjectName("filtersGroup");
        taskDetailsLayout = new QHBoxLayout(filtersGroup);
        taskDetailsLayout->setSpacing(8);
        taskDetailsLayout->setObjectName("taskDetailsLayout");
        categoryInput = new QLineEdit(filtersGroup);
        categoryInput->setObjectName("categoryInput");
        categoryInput->setMinimumSize(QSize(140, 32));

        taskDetailsLayout->addWidget(categoryInput);

        filterCategoryButton = new QPushButton(filtersGroup);
        filterCategoryButton->setObjectName("filterCategoryButton");
        filterCategoryButton->setMinimumSize(QSize(140, 32));

        taskDetailsLayout->addWidget(filterCategoryButton);

        priorityInput = new QSpinBox(filtersGroup);
        priorityInput->setObjectName("priorityInput");
        priorityInput->setMinimum(1);
        priorityInput->setMaximum(5);
        priorityInput->setMinimumSize(QSize(120, 32));

        taskDetailsLayout->addWidget(priorityInput);

        filterPriorityButton = new QPushButton(filtersGroup);
        filterPriorityButton->setObjectName("filterPriorityButton");
        filterPriorityButton->setMinimumSize(QSize(140, 32));

        taskDetailsLayout->addWidget(filterPriorityButton);

        dueDateInput = new QDateEdit(filtersGroup);
        dueDateInput->setObjectName("dueDateInput");
        dueDateInput->setCalendarPopup(true);
        dueDateInput->setMinimumSize(QSize(140, 32));

        taskDetailsLayout->addWidget(dueDateInput);

        filterDateButton = new QPushButton(filtersGroup);
        filterDateButton->setObjectName("filterDateButton");
        filterDateButton->setMinimumSize(QSize(140, 32));

        taskDetailsLayout->addWidget(filterDateButton);

        recurrenceInput = new QLineEdit(filtersGroup);
        recurrenceInput->setObjectName("recurrenceInput");
        recurrenceInput->setMinimumSize(QSize(140, 32));

        taskDetailsLayout->addWidget(recurrenceInput);

        filterRecurrenceButton = new QPushButton(filtersGroup);
        filterRecurrenceButton->setObjectName("filterRecurrenceButton");
        filterRecurrenceButton->setMinimumSize(QSize(140, 32));

        taskDetailsLayout->addWidget(filterRecurrenceButton);


        verticalLayout->addWidget(filtersGroup);

        combinedFilterButton = new QPushButton(centralwidget);
        combinedFilterButton->setObjectName("combinedFilterButton");

        verticalLayout->addWidget(combinedFilterButton);

        sortByDateButton = new QPushButton(centralwidget);
        sortByDateButton->setObjectName("sortByDateButton");

        verticalLayout->addWidget(sortByDateButton);

        sortByPriorityButton = new QPushButton(centralwidget);
        sortByPriorityButton->setObjectName("sortByPriorityButton");

        verticalLayout->addWidget(sortByPriorityButton);

        mainContentRow = new QHBoxLayout();
        mainContentRow->setSpacing(12);
        mainContentRow->setObjectName("mainContentRow");
        taskListColumn = new QVBoxLayout();
        taskListColumn->setObjectName("taskListColumn");
        taskList = new QListWidget(centralwidget);
        taskList->setObjectName("taskList");

        taskListColumn->addWidget(taskList);

        viewControls = new QHBoxLayout();
        viewControls->setObjectName("viewControls");
        viewTodayButton = new QPushButton(centralwidget);
        viewTodayButton->setObjectName("viewTodayButton");
        viewTodayButton->setMinimumSize(QSize(120, 34));

        viewControls->addWidget(viewTodayButton);

        viewCompletedCheckBox = new QCheckBox(centralwidget);
        viewCompletedCheckBox->setObjectName("viewCompletedCheckBox");

        viewControls->addWidget(viewCompletedCheckBox);


        taskListColumn->addLayout(viewControls);


        mainContentRow->addLayout(taskListColumn);

        actionsGroup = new QGroupBox(centralwidget);
        actionsGroup->setObjectName("actionsGroup");
        actionsLayout = new QVBoxLayout(actionsGroup);
        actionsLayout->setObjectName("actionsLayout");
        addTaskButton = new QPushButton(actionsGroup);
        addTaskButton->setObjectName("addTaskButton");
        addTaskButton->setMinimumSize(QSize(160, 36));

        actionsLayout->addWidget(addTaskButton);

        exportButton = new QPushButton(actionsGroup);
        exportButton->setObjectName("exportButton");
        exportButton->setMinimumSize(QSize(150, 34));

        actionsLayout->addWidget(exportButton);

        markCompletedButton = new QPushButton(actionsGroup);
        markCompletedButton->setObjectName("markCompletedButton");
        markCompletedButton->setMinimumSize(QSize(160, 36));

        actionsLayout->addWidget(markCompletedButton);

        archiveCompletedButton = new QPushButton(actionsGroup);
        archiveCompletedButton->setObjectName("archiveCompletedButton");
        archiveCompletedButton->setMinimumSize(QSize(150, 34));

        actionsLayout->addWidget(archiveCompletedButton);

        resetFiltersButton = new QPushButton(actionsGroup);
        resetFiltersButton->setObjectName("resetFiltersButton");
        resetFiltersButton->setMinimumSize(QSize(220, 36));

        actionsLayout->addWidget(resetFiltersButton);


        mainContentRow->addWidget(actionsGroup);


        verticalLayout->addLayout(mainContentRow);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", " Daily Task Notifier", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\227\223\357\270\217 Daily Task Notifier", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("MainWindow", "Organize, filter, and prioritize your daily tasks", nullptr));
        searchBar->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search tasks (title, category, notes)...", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        filtersGroup->setTitle(QCoreApplication::translate("MainWindow", "Filters", nullptr));
        categoryInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "e.g., Work", nullptr));
        filterCategoryButton->setText(QCoreApplication::translate("MainWindow", "Filter by Category", nullptr));
        priorityInput->setPrefix(QCoreApplication::translate("MainWindow", "Priority: ", nullptr));
        filterPriorityButton->setText(QCoreApplication::translate("MainWindow", "Filter by Priority", nullptr));
        filterDateButton->setText(QCoreApplication::translate("MainWindow", "Filter by Date", nullptr));
        recurrenceInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "e.g. Daily", nullptr));
        filterRecurrenceButton->setText(QCoreApplication::translate("MainWindow", "Filter by Recurrence", nullptr));
        combinedFilterButton->setText(QCoreApplication::translate("MainWindow", "Apply Combined Filters", nullptr));
        sortByDateButton->setText(QCoreApplication::translate("MainWindow", "Sort by Due Date", nullptr));
        sortByPriorityButton->setText(QCoreApplication::translate("MainWindow", "Sort by Priority", nullptr));
        viewTodayButton->setText(QCoreApplication::translate("MainWindow", "View Today", nullptr));
        viewCompletedCheckBox->setText(QCoreApplication::translate("MainWindow", "View Completed Tasks", nullptr));
        actionsGroup->setTitle(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        addTaskButton->setText(QCoreApplication::translate("MainWindow", "Add Task", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Export Current View", nullptr));
        markCompletedButton->setText(QCoreApplication::translate("MainWindow", "Mark Selected as Completed", nullptr));
        archiveCompletedButton->setText(QCoreApplication::translate("MainWindow", "Archive Completed Tasks", nullptr));
        resetFiltersButton->setText(QCoreApplication::translate("MainWindow", "Reset Filters", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
