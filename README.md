# CMakeTest

## 介绍

vs使用Cmake构建Qt项目测试

## 构建流程

### 命令行

执行

`cmake -S . -B build -D Qt5_DIR=D:/QT/5.15.2/msvc2019_64/lib/cmake/Qt5`

生成build文件夹，继续编译执行

`cmake --build build`

得到可执行程序
