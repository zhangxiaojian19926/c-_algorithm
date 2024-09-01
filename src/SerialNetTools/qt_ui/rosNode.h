#pragma once 

#include <ros/publisher.h>
#include <ros/subscriber.h>
#include <qchar.h>
#include <qt5/QtCore/qdebug.h>
#ifndef Q_MOC_RUN
#include <ros/ros.h> //检查Q_MOC_RUN是否定义，若未定义则导入ROS头文件,当moc生成额外代码时，有可能会和ros头文件冲突
#endif

#include <QThread>
#include <QString>
#include <std_msgs/String.h> // 导入ROS消息类型

class RosNode : public QThread
{
    Q_OBJECT;// 必须有，否则编译会报错

public:
    RosNode(int argc, char **argv);
    virtual ~RosNode(); // 确保衍生类的析构函数被调用

    bool init();// 初始化ROS节点

    void run();

    void callback_strMsg(const std_msgs::StringConstPtr& msg); // 订阅者回调函数

    ros::Publisher pub_str_msg; // 发布者
    ros::Subscriber sub_str_msg;// 订阅者

Q_SIGNALS:
    void signal_rosShutdown(); // 关闭ROS节点
    void signal_strMsg(const QString&); // 订阅者回调函数

public slots:
    void slot_putStrMsg(const QString&);// 发布者回调函数

private:
    int init_argc_;// 初始化参数个数
    char **init_argv_;// 初始化参数
};