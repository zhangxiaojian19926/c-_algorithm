#*************************
# 项目名称 设置编译目录
#************************
project(serialNetTools)

#*************************
# 设置变量+打印工程目录
#************************
# message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

#******************************************
# 添加头文件  外部已经添加，内部可以不哟个添加
#******************************************
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#*************************
# 生成动态库
#*************************
add_library(${PROJECT_NAME} SHARED serialNetTools.cpp) # 生成动态库
# add_library(${PROJECT_NAME} serialNetTools.cpp) # 生成静态库

#*************************
# 生成可执行文件
#************************
add_executable(${PROJECT_NAME}_test main_test.cpp)

#*************************
# 配置链接库
#************************
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})