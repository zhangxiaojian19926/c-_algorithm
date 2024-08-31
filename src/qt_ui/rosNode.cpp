#include "rosNode.h"
#include "ros/init.h"
#include "ros/node_handle.h"
#include "ros/rate.h"
#include <QCoreApplication>
#include <qcoreapplication.h>
#include <qobjectdefs.h>

RosNode::RosNode(int argc, char **argv)
    :init_argc_(argc), init_argv_(argv) // 初始化参数个数和参数
{

}

RosNode::~RosNode()
{
    if(ros::isStarted())
    {
        ros::shutdown(); // 关闭ROS节点
        ros::waitForShutdown(); // 等待ROS节点关闭
    }

    wait();
}

/**
* 初始化ROS节点
*/
bool RosNode::init()
{
    // 初始化ROS节点
    ros::init(init_argc_, init_argv_, "qt_ui");
    // 确认rosck是否跑起来
    if (!ros::master::check()) {
        ROS_ERROR("Failed to initialize ROS."); // 没有跑起来则认为初始化失败
        return false;
    }

    ros::start();
    ros::NodeHandle nh;
    // ros::start();

    // 发送和订阅
    pub_str_msg = nh.advertise<std_msgs::String>("/str_msg", 10); // 发布者
    sub_str_msg = nh.subscribe("/str_msg", 10, &RosNode::callback_strMsg, this); // 订阅者

    start();
    return true;
}


/**
 * @brief 启动并运行一个 ROS 节点，确保事件循环和 ROS 通信正常
 *
 * @return 无
 */
void RosNode::run()
{
    ros::start();
    ros::NodeHandle nh; //新建一个ros节点句柄

    ros::Rate rate(10); // 每秒循环10次
    while (ros::ok()) 
    {
        QCoreApplication::processEvents(); // 确保qt事件循环正常运行
        ros::spinOnce(); // 处理ROS的回调函数
        rate.sleep(); // 休眠，等待下一次循环
    }

    Q_EMIT signal_rosShutdown(); // 发送信号，通知节点已完成运行
}


// 订阅者回调函数
void RosNode::callback_strMsg(const std_msgs::StringConstPtr& msg)
{
    // Q_EMIT 发送信号，通知订阅者收到消息
    Q_EMIT signal_strMsg(QString::fromStdString(msg->data)); // 发送信号，通知订阅者收到消息
}


void RosNode::slot_putStrMsg(const QString& msg)
{
    // 发布消息
    std_msgs::String str_msg;
    str_msg.data = msg.toStdString();
    pub_str_msg.publish(str_msg);
}