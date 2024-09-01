#*************************
# 项目名称 设置编译目录
#************************
project(common)

#*************************
# 设置变量+打印工程目录
#************************
# message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

#*************************
# 添加头文件
#************************
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#*************************
# 生成动态库
#*************************
add_library(${PROJECT_NAME} SHARED common.cpp myLog.cpp) # 生成动态库
target_link_libraries(${PROJECT_NAME} glog)

#*************************
# 生成可执行文件
#************************
add_executable(${PROJECT_NAME}_test main_common_test.cpp)

#*************************
# 配置链接库
#************************
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})