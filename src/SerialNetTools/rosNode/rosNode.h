#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h> //通过检查Q_MOC_RUN宏，确保只有在MOC没有运行时才包含ROS的头文件。这样，当MOC生成额外的代码时，它不会尝试处理ROS的头文件，从而避免潜在的冲突
#endif

#include <QThread>
#include <QString>
#include <std_msgs/String.h>
#include <QVariantMap>
// #include "myLog.h"


class RosNode : public QThread
{
    Q_OBJECT //这个宏是Qt元对象系统的必需部分，它启用了信号、槽和属性等特性

public:
    RosNode(int argc,char** argv);
    virtual ~RosNode(); //虚析构函数，确保派生类的析构函数被调用
    bool init();
    void run() override;

    void callback_strMsg(const std_msgs::StringConstPtr msg);

    ros::Publisher pub_str_msg;
    ros::Subscriber sub_str_msg;

Q_SIGNALS:
    void signal_rosShutdown();
    void signal_ros_strMsg(const QVariantMap&);

public slots:
    void slot_ros_pubStrMsg(const QString&);

private:
    int init_argc_;
    char** init_argv_;
};