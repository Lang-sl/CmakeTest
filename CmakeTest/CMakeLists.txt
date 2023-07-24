cmake_minimum_required(VERSION 3.20)
project(CmakeTest)

# uic cmaketest.ui > ui_cmaketest.h
set(CMAKE_AUTOUIC ON)
# rcc > .h
set(CMAKE_AUTORCC ON)
# moc
set(CMAKE_AUTOMOC ON)


add_executable(${PROJECT_NAME} WIN32
"main.cpp" "CmakeTest.ui" "CmakeTest.h" "CmakeTest.cpp" "NavigationDock.h" "NavigationDock.cpp" "Config.h" "GLWidget.h" "GLWidget.cpp" "TimeThread.h" "TimeThread.cpp" "TcpClient.h" "TcpClient.cpp" "CmakeTest.qrc")

find_package(Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)

# set(Qt5_DIR D:/QT/5.15.2/msvc2019_64/lib/cmake/Qt5)
# cmake -S . -B build -D Qt5_DIR=D:/QT/5.15.2/msvc2019_64/lib/cmake/Qt5

# D:\QT\5.15.2\msvc2019_64\lib\cmake\Qt5
target_link_libraries(${PROJECT_NAME}
Qt5::Widgets
Qt5::Core
Qt5::Gui
Qt5::Network
)


set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS) #windows应用

# 自动复制依赖的动态库 D:/QT/5.15.2/msvc2019_64/bin/windeployqt