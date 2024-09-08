#include "mySerial.h"
#include <iostream>
#include "myLog.h"
#include "common.h"
#include <QCoreApplication>
#include <QThread>

int main(int argc,char** argv)
{
    Common common;
    std::string log_path = common.get_log_path();
    myLog *myLog = new class myLog(log_path,"mySerial");

    LOG(INFO)<<"mySerial test start.";

    QCoreApplication app(argc,argv);
    MySerial *mySerial = new MySerial();

    QThread *thread = new QThread();
    mySerial->moveToThread(thread);

    thread->start();
    LOG(INFO)<<"mySerial start /dev/tnt0.";

    mySerial->init("1","/dev/tnt0",115200,0,8,1);
    QMetaObject::invokeMethod(mySerial,"start",Qt::QueuedConnection);

    return app.exec();
}