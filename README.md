# 项目

## CMakeTest

### 介绍

使用vs使用Cmake构建Qt项目测试

#### 包括

`CADDemo`(Deprecated) in `src`

`GraphicsViewDemo`(now update in caxbase) in `QGraphicsViewSrc`

### 构建流程

#### 命令行

在`CmakeTest`文件夹下执行

`cmake -S . -B build -D Qt5_DIR=D:/QT/5.15.2/msvc2019_64/lib/cmake/Qt5`（注意修改路径，或者修改`CMakeLists.txt`文件中的`Qt5_DIR`路径）

生成build文件夹，继续编译执行

`cmake --build build`

得到可执行程序

## MFCTest

### 介绍

测试使用`untitledDLL`生成的依赖库以及测试在MFC程序中插入QT页面

## untitledDLL

### 介绍

生成DLL以供测试
