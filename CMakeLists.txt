#*************************
# 声明cmake版本号
#*************************
cmake_minimum_required(VERSION 3.16)

#*************************
# 项目名称 设置编译目录
#************************
project(serial_Net_Tools)

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
# 设置可执行程序输出目录
#************************
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(MY_CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install) # 设置安装目录

#*************************
# 添加QT依赖
#************************
set(Qt5_DIR "/opt/Qt5.12.12/5.12.12/gcc_64/lib/cmake/Qt5")


#*************************
# 添加头文件
#************************
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/SerialNetTools/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/SerialNetTools/qt_ui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/SerialNetTools/serialNetTools)
include_directories(${PROJECT_SOURCE_DIR}/src/serialNetTools/rosNode)
include_directories(${PROJECT_SOURCE_DIR}/src/serialNetTools/mySerial)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/build/devel/include) # 包含编译生成的头文件


#*************************
# 底层cmake添加
#************************
add_subdirectory(src)