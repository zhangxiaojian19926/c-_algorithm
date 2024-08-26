#include "rosNode.h"
#include <QCoreApplication>

RosNode::RosNode(int argc, char **argv)
    :init_argc_(argc), init_argv_(argv)
{

}

RosNode::~RosNode()
{
    if(ros::isInitialized())
    {

    }
}

/**
* 初始化ROS节点
*/
bool RosNode::init()
{
    
}
