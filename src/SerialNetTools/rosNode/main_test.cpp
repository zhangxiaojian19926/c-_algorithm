#include <iostream>
#include "rosNode.h"
#include <QCoreApplication>

int main(int argc,char** argv)
{
    QCoreApplication app(argc,argv);

    RosNode *rosNode = new RosNode(argc,argv);
    rosNode->init();
    //QMetaObject::invokeMethod 
    //Qt的反射机制主要通过QMetaObject类来实现。
    //Qt::QueuedConnection:可以指定信号和槽之间的连接类型 确保了跨线程调用的安全性
    //使用Q_ARG宏来传递参数，使用Q_RETURN_ARG宏来获取返回值
    bool res = QMetaObject::invokeMethod(rosNode, "start", Qt::QueuedConnection);
    std::cout<<"res: "<<res<<std::endl;


    // QThread *thread = new QThread();
    // rosNode->moveToThread(thread);
    QObject::connect(rosNode,&RosNode::signal_rosShutdown,&app,&QCoreApplication::quit);
    // QObject::connect(thread,&QThread::started,rosNode,&RosNode::run);

    // //启动线程
    // thread->start();

    int result = app.exec();

    // //清理资源
    delete rosNode;
    // thread->deleteLater();
    // sleep(1);

    return result;
}