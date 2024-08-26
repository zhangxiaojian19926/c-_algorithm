#pragma once 

#include <qt5/QtCore/qdebug.h>
#ifndef Q_MOC_RUN
#include <ros/ros.h> //检查Q_MOC_RUN是否定义，若未定义则导入ROS头文件,当moc生成额外代码时，有可能会和ros头文件冲突
#endif

#include <QThread>

class RosNode : public QThread
{
    Q_OBJECT;// 必须有，否则编译会报错

public:
    RosNode(int argc, char **argv);
    virtual ~RosNode();

    bool init();// 初始化ROS节点

    void run();
private:
    int init_argc_;// 初始化参数个数
    char **init_argv_;// 初始化参数
};