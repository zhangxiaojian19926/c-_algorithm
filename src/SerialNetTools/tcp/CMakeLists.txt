#*************************
# 项目名称
#************************
project(myTcp)

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")

#*************************
# 添加头文件
#************************
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

#************************
# 导入QT库
#************************
find_package(Qt5 COMPONENTS Network Core REQUIRED)

#************************
# 添加源文件
#************************
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h)
set(QT_SOURCES myTcpClient.cpp myTcpServer.cpp)

#三个用于处理Qt特定资源和代码生成的命令
# QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS}) #从 .ui 文件自动生成用户界面类的头文件和源文件
# QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})#将 .qrc 资源文件转换成可编译的C++源文件
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC}) #.h 文件（包含Qt对象的头文件）自动生成moc（元对象编译器）文件，这些文件是Qt信号和槽机制所必需的

#*************************
# 生成动态库，直接调用
#************************
add_library(${PROJECT_NAME} SHARED ${QT_SOURCES} 
                                   ${QT_MOC_HPP})
                                   
target_link_libraries(${PROJECT_NAME} 
                      Qt5::Core
                      Qt5::Network
                      common
                     )

#*************************
# 生成可执行文件
#************************
# add_executable(${PROJECT_NAME}_test main_test.cpp)

# target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})             