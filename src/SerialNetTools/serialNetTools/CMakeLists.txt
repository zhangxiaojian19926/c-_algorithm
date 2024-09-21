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
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


#*************************
# 导入qt库
#*************************
find_package(Qt5 COMPONENTS Core SerialPort Widgets Network Concurrent REQUIRED)

# #导入ROS
# find_package(catkin REQUIRED COMPONENTS
#        roscpp
#        rospy
#        std_msgs
#        sensor_msgs
#        )

# include_directories(${catkin_INCLUDE_DIRS})

#*************************
# 添加文件
#*************************
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h) # 生成头文件
set(QT_SOURCES serialNetTools.cpp) # 生成源文件


QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})# 生成头文件

#导入ROS
find_package(catkin REQUIRED COMPONENTS
       roscpp
       rospy
       std_msgs
       sensor_msgs
       )

include_directories(${catkin_INCLUDE_DIRS})

#*************************
# 生成动态库
#*************************
add_library(${PROJECT_NAME} SHARED ${QT_SOURCES}
                                    ${QT_MOC_HPP}) # 生成动态库
# 链接动态库
target_link_libraries(${PROJECT_NAME} 
                        Qt5::Core 
                        Qt5::SerialPort 
                        Qt5::Widgets 
                        Qt5::Network 
                        Qt5::Concurrent
                        rosNode
                        mySerial
                        qt_ui
                        myTcp
                        ${catkin_LIBRARIES}
                        )

#*************************
# 生成可执行文件
#************************
add_executable(${PROJECT_NAME}_main main.cpp)

#*************************
# 配置链接库
#************************
target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME})