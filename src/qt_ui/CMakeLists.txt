#*************************
# 声明cmake版本号
#*************************
cmake_minimum_required(VERSION 3.16)

#*************************
# 项目名称 设置编译目录
#************************
project(qt_ui)

#*************************
# 设置编译类型
#************************
# set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

#*************************
# 指定C++标准 
#************************
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 确保编译器支持所选标准

#************************
# 设置优化等级
#************************
set(CMAKE_CXX_FLAGS "-w")# 忽略警告信息
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb ${CMAKE_CXX_FLAGS}")# 设置DEBUG模式的编译选项
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -ggdb ${CMAKE_CXX_FLAGS}")# 设置RELEASE模式的编译选项

#*************************
# 设置变量+打印工程目录
#************************
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

#*************************
# 添加头文件
#************************
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#*************************
# 导入qt库
#************************
find_package(Qt5 COMPONENTS Core Widgets)

set(CMAKE_PREFIX_PATH /opt/ros/melodic/share/catkin/cmake/)
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs sensor_msgs) 

include_directories(${catkin_INCLUDE_DIRS})

#*************************
# 添加库文件
#*************************
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.ui) # 生成ui文件
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qrc) # 生成资源文件
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h) # 生成头文件
# file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.cpp) 
set(QT_SOURCES mainwindow.cpp rosNode.cpp) # 生成源文件


QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})# 生成头文件
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})# 生成资源文件
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})# 生成头文件


#*************************
# 打印消息
#*************************
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "QT_FORMS_HPP: ${QT_FORMS_HPP}")
message(STATUS "QT_RESOURCES_CPP: ${QT_RESOURCES_CPP}")
message(STATUS "QT_MOC_HPP: ${QT_MOC_HPP}")
message(STATUS "QT_SOURCES: ${QT_SOURCES}")

#*************************
# 生成动态库 qt动态库
#*************************
add_library(${PROJECT_NAME} SHARED ${QT_SOURCES} ${QT_FORMS_HPP} ${QT_RESOURCES_CPP} ${QT_MOC_HPP}) # 生成动态库
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

#*************************
# 生成可执行文件
#************************
add_executable(${PROJECT_NAME}_test main.cpp)

#*************************
# 配置链接库
#************************
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})