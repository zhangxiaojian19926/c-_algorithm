#*************************
# 项目名称 设置编译目录
#************************
project(qt_ui)

#*************************
# 设置变量+打印工程目录
#************************
# message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

#*********************************
# 找到日志库 common 添加日志库的链接
#*********************************
# find_library(LOG_LIB_DIR NAMES common PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib)
# link_libraries(${LOG_LIB_DIR})

#*************************
# 添加qt库文件 qt编译环境导入
#*************************
find_package(Qt5 COMPONENTS Core SerialPort Widgets)
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.ui) # 生成ui文件
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qrc) # 生成资源文件
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h) # 生成头文件
set(QT_SOURCES mainwindow.cpp) # 生成源文件

QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})# 生成头文件
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})# 生成资源文件
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})# 生成头文件


#*************************
# 打印消息
#*************************
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "QT_FORMS_HPP: ${QT_FORMS_HPP}")
# message(STATUS "QT_RESOURCES_CPP: ${QT_RESOURCES_CPP}")
# message(STATUS "QT_MOC_HPP: ${QT_MOC_HPP}")
# message(STATUS "QT_SOURCES: ${QT_SOURCES}")
# message(STATUS "LOG_LIB_DIR: ${LOG_LIB_DIR}")
# message(STATUS "catkin_LIBRARIES: ${catkin_LIBRARIES}")

#*************************
# 生成动态库 qt动态库
#*************************
add_library(${PROJECT_NAME} SHARED ${QT_SOURCES} 
                                   ${QT_FORMS_HPP} 
                                   ${QT_RESOURCES_CPP} 
                                   ${QT_MOC_HPP}
                                   ) # 生成动态库

target_link_libraries(${PROJECT_NAME} 
                      Qt5::Core Qt5::Widgets Qt5::SerialPort
                      ${catkin_LIBRARIES} 
                      common
                      )

#*************************
# 生成可执行文件
#************************
add_executable(${PROJECT_NAME}_test main.cpp)

#*************************
# 配置链接库
#************************
target_link_libraries(${PROJECT_NAME}_test 
                      ${PROJECT_NAME}
                     )

#*************************
# 项目和库安装
#*************************
#特定库绝对路径
set_target_properties(${PROJECT_NAME}_test PROPERTIES
  INSTALL_RPATH ${MY_CMAKE_INSTALL_PREFIX}/lib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH ${MY_CMAKE_INSTALL_PREFIX}/lib)

#相对路径
set_target_properties(${PROJECT_NAME}_test PROPERTIES
  INSTALL_RPATH "$ORIGIN/../lib")
set_target_properties(${PROJECT_NAME} PROPERTIES
  INSTALL_RPATH "$ORIGIN/../lib")

# 安装目标
install(
  TARGETS ${PROJECT_NAME}_test ${PROJECT_NAME} common
  EXPORT FindQtUi
  RUNTIME DESTINATION ${MY_CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${MY_CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${MY_CMAKE_INSTALL_PREFIX}/lib
  )

#头文件安装
install(FILES mainwindow.h ../common/myLog.h ../common/common.h
  DESTINATION ${MY_CMAKE_INSTALL_PREFIX}/include)

# 安装导出
install(EXPORT FindQtUi
  DESTINATION ${MY_CMAKE_INSTALL_PREFIX}
  FILE FindQtUi.cmake)