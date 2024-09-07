#include "rosNode.h"
#include <QCoreApplication>

/**
 * 构造函数
 */
RosNode::RosNode(int argc,char** argv):init_argc_(argc),init_argv_(argv)
{

}

RosNode::~RosNode()
{
    std::cout<<"~RosNode()"<<std::endl;
    if(ros::isStarted())
    {
        ros::shutdown();
        ros::waitForShutdown();
    }
    wait();
}

/**
 * ROS节点的初始化函数
 */
bool RosNode::init()
{
    ros::init(init_argc_,init_argv_,"qt_ui");
    if(!ros::master::check())
    {
        return false;
    }
    ros::start();
    ros::NodeHandle n;
    // ros::start();

    //发送和订阅
    pub_str_msg = n.advertise<std_msgs::String>("/str_msg",10);//发布消息
    sub_str_msg = n.subscribe("/str_msg",10,&RosNode::callback_strMsg,this);

    // start();
    return true;
}

void RosNode::run()
{
    ros::start();
    ros::NodeHandle n;

    ros::Rate rate(10);
    while(ros::ok())
    {
        QCoreApplication::processEvents();//确保Qt的事件循环得到处理
        ros::spinOnce();
        rate.sleep();
    }

    Q_EMIT signal_rosShutdown();

}

void RosNode::slot_ros_pubStrMsg(const QString& msg)
{
    std_msgs::String str_msg;
    str_msg.data = msg.toStdString();
    pub_str_msg.publish(str_msg);
}

/**
 * ros消息的回调函数
 */
void RosNode::callback_strMsg(const std_msgs::StringConstPtr msg)
{
    std::cout<<"msg: "<<msg->data<<std::endl;
    QVariantMap data;
    data["type"] = "rosNode";
    data["data"] = QString::fromStdString(msg->data);
    Q_EMIT signal_ros_strMsg(data);
}