cmake_minimum_required(VERSION 3.20)
project(CADDemo)

# uic cmaketest.ui > ui_cmaketest.h
set(CMAKE_AUTOUIC ON)
# rcc > .h
set(CMAKE_AUTORCC ON)
# moc
set(CMAKE_AUTOMOC ON)


file(GLOB SRC_LIST ./*.cpp ./*.qrc ./*.h ./*.ui)

aux_source_directory(./ SRC_LIST)
set(APP_NAME_1 CADDemo)
# set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})
add_executable(${APP_NAME_1} WIN32 ${SRC_LIST})

find_package(Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)

set(Qt5_DIR D:/QT/5.15.2/msvc2019_64/lib/cmake/Qt5)
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