#*************************
# 项目名称 设置编译目录
#************************
project(serialNetTools)

#*************************
# 添加头文件
#************************
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#*************************
# 生成可执行文件
#************************
add_executable(${PROJECT_NAME}_test main_test.cpp)

#*************************
# 配置链接库
#************************
# target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})