#include "mainwindow.h"
#include "mySerial.h"
#include <qcoreapplication.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qt5/QtCore/qthread.h>
#include "serialNetTools.h"

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
    // 删除串口相关资源
    if(mySerial_thread!= nullptr){
        mySerial_thread->deleteLater();
        mySerial_thread = nullptr;
    }

    if (mySerial != nullptr) {
        delete mySerial;
        mySerial = nullptr;
    }
    
    if (mainWindow != nullptr) {
        delete mainWindow;
        mainWindow = nullptr;
    }

    if (app!= nullptr) {
        delete app;
        app = nullptr;
    }

    // 删除tcp相关资源
    if (tcp_client_thread!= nullptr) {
        tcp_client_thread->deleteLater();
        tcp_client_thread = nullptr;
    }

    if (tcp_client != nullptr) {
        delete tcp_client;
        tcp_client = nullptr;
    }

    if (tcp_server_thread!= nullptr) {
        tcp_server_thread->deleteLater();
        tcp_server_thread = nullptr;
    }

    if (tcp_server != nullptr) {
        delete tcp_server;
        tcp_server = nullptr;
    }

    if (rosNode_thread != nullptr) {
        rosNode_thread->deleteLater();
        rosNode_thread = nullptr;
    }

    if (rosNode != nullptr) {
        delete rosNode;
        rosNode = nullptr;
    }

    std::cout << "de!" << std::endl;
}

// 初始化
int serialNetTools::init()
{
    app = new QApplication(argc_, argv);
    mainWindow = new MainWindow(argc_, argv);
    mainWindow->show();

    // 利用表来开关不同的模块
    QObject::connect(mainWindow, &MainWindow::signal_switch, 
                        this, &serialNetTools::slot_switch, Qt::QueuedConnection);

    // rosNode 初始化
    rosNode = new RosNode(argc_, argv);
    rosNode->init(); // 发送与订阅
    rosNode_thread = new QThread();
    rosNode->moveToThread(rosNode_thread);
    QObject::connect(rosNode_thread, &QThread::started, rosNode, &RosNode::run);
    QObject::connect(rosNode, &RosNode::signal_rosShutdown, 
                        app, &QCoreApplication::quit, Qt::QueuedConnection);
    QObject::connect(rosNode, &RosNode::signal_ros_strMsg, 
                    mainWindow, &MainWindow::slot_send_textEdit, Qt::QueuedConnection);
    QObject::connect(mainWindow, &MainWindow::signal_rosPub, rosNode, 
                    &RosNode::slot_ros_pubStrMsg, Qt::QueuedConnection);


    switchMap["mySerial"] = [this](const QVariantMap& msg){switch_mySerial(msg);};
    mySerial_thread = new QThread();
    mySerial = new MySerial();
    mySerial->moveToThread(mySerial_thread);
    // 串口的信号与槽的连接
    QObject::connect(mySerial, &MySerial::signal_openStatus, 
                        mainWindow, &MainWindow::slot_module_status, Qt::QueuedConnection);
    QObject::connect(mySerial, &MySerial::signal_serial,
                        mainWindow, &MainWindow::slot_send_textEdit, Qt::QueuedConnection);
    QObject::connect(mainWindow, &MainWindow::signal_serialSend,
                        mySerial, &MySerial::slot_write, Qt::QueuedConnection);


    // 创建客户端线程
    switchMap["tcpClient"] = [this](const QVariantMap& msg){switch_tcpClient(msg);};
    tcp_client_thread = new QThread();
    tcp_client = new tcpClient();
    tcp_client->moveToThread(tcp_client_thread);
    // tcp客户端的信号与槽的连接
    QObject::connect(tcp_client, &tcpClient::signal_openStatus, 
                    mainWindow, &MainWindow::slot_module_status, Qt::QueuedConnection);
    QObject::connect(tcp_client, &tcpClient::signal_tcpClient, 
                    mainWindow, &MainWindow::slot_send_textEdit, Qt::QueuedConnection);
    QObject::connect(mainWindow, &MainWindow::signal_tcpClientSend, 
                    tcp_client, &tcpClient::slot_write, Qt::QueuedConnection);

    // 创建服务器端
    switchMap["tcpServer"] = [this](const QVariantMap& msg){switch_tcpServer(msg);};
    tcp_server_thread = new QThread();
    tcp_server = new tcpServer();
    tcp_server->moveToThread(tcp_server_thread);
    // tcp客户端的信号与槽的连接
    QObject::connect(tcp_server, &tcpServer::signal_openStatus, 
                    mainWindow, &MainWindow::slot_module_status, Qt::QueuedConnection);
    QObject::connect(tcp_server, &tcpServer::signal_tcpServer, 
                    mainWindow, &MainWindow::slot_send_textEdit, Qt::QueuedConnection);
    QObject::connect(mainWindow, &::MainWindow::signal_tcpServerSend, 
                    tcp_server, &tcpServer::slot_write, Qt::QueuedConnection);

    mySerial_thread->start();
    tcp_client_thread->start();
    tcp_server_thread->start();
    rosNode_thread->start();// 开启线程
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

void serialNetTools::switch_tcpClient(const QVariantMap &msg){
    bool state = msg.value("switch").toBool();
    if (state == true) {
        string ip = msg.value("ip").toString().toStdString();
        int port = msg.value("port").toInt();
        string groudID = msg.value("groudID").toString().toStdString();
        tcp_client->init(groudID, ip, port); // 初始化客户端

        LOG(INFO) << "tcpClient open";
        QMetaObject::invokeMethod(tcp_client, "start", Qt::QueuedConnection);
    } else {
        LOG(INFO) << "tcpClient close";
        QMetaObject::invokeMethod(tcp_client, "stop", Qt::QueuedConnection);
    }
}

void serialNetTools::switch_tcpServer(const QVariantMap &msg){
    bool state = msg.value("switch").toBool();
    if (state == true) {
        string ip = msg.value("ip").toString().toStdString();
        int port = msg.value("port").toInt();
        tcp_server->init(ip, port); // 初始化客户端

        LOG(INFO) << "tcp_server open" << ip << " " + port;
        QMetaObject::invokeMethod(tcp_server, "start", Qt::QueuedConnection);
    } else {
        LOG(INFO) << "tcp_server close";
        QMetaObject::invokeMethod(tcp_server, "stop", Qt::QueuedConnection);
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
        LOG(INFO) << "type: " << type.toStdString();
        switchMap[type](msg);
    }
}
