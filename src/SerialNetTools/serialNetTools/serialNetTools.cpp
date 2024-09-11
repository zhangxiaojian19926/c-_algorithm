#include "serialNetTools.h"
#include "mainwindow.h"
#include "mySerial.h"
#include <qnamespace.h>
#include <qobject.h>

/**
 * serialNetTools 类的构造函数
 */
serialNetTools::serialNetTools(int argc, char **argv)
    : argc_(argc), argv(argv)
{
    std::cout << "Hello world!" << std::endl;
}

/**
* 析构函数 ~serialNetTools()
*/
serialNetTools::~serialNetTools()
{
    std::cout << "de!" << std::endl;
}

// 初始化
int serialNetTools::init()
{
    app = new QApplication(argc_, argv);
    mainWindow = new MainWindow(argc_, argv);
    mainWindow->show();

    // mySerial 初始化
    QObject::connect(mainWindow, &MainWindow::signal_switch, 
                        this, &serialNetTools::slot_switch, Qt::QueuedConnection);

    switchMap["mySerial"] = [this](const QVariantMap& msg){switch_mySerial(msg);};
    mySerial_thread = new QThread();
    mySerial = new MySerial();
    mySerial->moveToThread(mySerial_thread);

    QObject::connect(mySerial, &MySerial::signal_openStatus, 
                        mainWindow, &MainWindow::slot_module_status, Qt::QueuedConnection);

    QObject::connect(mySerial, &MySerial::signal_serial,
                        mainWindow, &MainWindow::slot_send_textEdit, Qt::QueuedConnection);

    QObject::connect(mainWindow, &MainWindow::signal_serialSend,
                        mySerial, &MySerial::slot_start, Qt::QueuedConnection);

    mySerial_thread->start();

    return app->exec();
}

// 串口 开关
void serialNetTools::switch_mySerial(const QVariantMap &msg)
{
    bool state = msg.value("switch").toBool();
    if (state == true) {
        string serialName = msg.value("serialName").toString().toStdString();
        int baudRate = msg.value("baudRate").toInt();
        int checkData = msg.value("checkData").toInt();
        int dataBits = msg.value("dataBit").toInt();
        int stopBits = msg.value("stopBit").toInt();
        mySerial->init("1",serialName, baudRate, checkData, dataBits, stopBits);

        std::cout << msg.value("serialName").toString().toStdString() << msg.value("baudRate").toInt() << msg.value("checkData").toInt() << msg.value("dataBit").toInt() << msg.value("stopBit").toInt() << std::endl;
        QMetaObject::invokeMethod(mySerial, "start", Qt::QueuedConnection);
    } else {
        LOG(INFO) << "mySerial close";
        QMetaObject::invokeMethod(mySerial, "stop", Qt::QueuedConnection);
    }
}

/**
 * 开关
 */
void serialNetTools::slot_switch(const QVariantMap &msg)
{
    QString type = msg["type"].toString();
    if (switchMap.contains(type))
    {
        switchMap[type](msg);
    }
}
