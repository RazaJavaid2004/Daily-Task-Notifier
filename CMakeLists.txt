cmake_minimum_required(VERSION 3.16)

project(DailyTaskNotifier VERSION 1.0 LANGUAGES CXX)

# Enable Qt features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt libraries
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/task.cpp
    src/taskManager.cpp
)

# Header files
set(HEADERS
    include/mainwindow.h
    include/task.h
    include/taskManager.h
)

# UI files (now inside /src)
set(UIS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.ui
)

# Create executable
qt_add_executable(DailyTaskNotifier
    MANUAL_FINALIZATION
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

# Include headers
target_include_directories(DailyTaskNotifier PRIVATE include)

# Link Qt libraries
target_link_libraries(DailyTaskNotifier PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Finalize for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DailyTaskNotifier)
endif()