#*************************
# 声明cmake版本号
#*************************
cmake_minimum_required(VERSION 3.16)

#*************************
# 项目名称 设置编译目录
#************************
project(my)

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
# 添加头文件
#************************
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#*************************
# 设置可执行程序输出目录
#************************
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../install)
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

#*************************
# 找到QtUi相关的东西
#************************
find_package(QtUi REQUIRED)

#*************************
# 添加头文件 QtUi
#************************
set(QtUi_INCLUDE_DIRS ${CMAKE_MODULE_PATH}/include ${QtUi_INCLUDE_DIRS})
message("QtUi_INCLUDE_DIRS: ${QtUi_INCLUDE_DIRS}")
include_directories(${QtUi_INCLUDE_DIRS})

#*************************
# 生成可执行文件
#************************
add_executable(${PROJECT_NAME}_test main.cpp)

#*************************
# 配置链接库
#************************
target_link_libraries(${PROJECT_NAME}_test common)
