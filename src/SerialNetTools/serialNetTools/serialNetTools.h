#pragma once

#include <QtWidgets/qapplication.h>
#include <functional>
#include <iostream>
#include "mainwindow.h"
#include "mySerial.h"
#include "myTcpClient.h"
#include "myTcpServer.h"
#include <QThread>
#include <QApplication>
#include <QHash>
#include <QVariantMap>
#include <qhash.h>
#include <qobjectdefs.h>
#include <qthread.h>

class serialNetTools:public QObject
{
    Q_OBJECT // 这个是Qt元对象系统的必须部分，启用信号、槽和属性等特性
public:
    serialNetTools(int argc, char** argv);
    ~serialNetTools();
    
    int init();

private:
    // 私有成员函数
    void switch_mySerial(const QVariantMap& msg);
    void switch_tcpClient(const QVariantMap& msg);
    void switch_tcpServer(const QVariantMap& msg);

public slots:
    void slot_switch(const QVariantMap &);

private:
    int argc_;
    char **argv;
    MainWindow *mainWindow = nullptr;
    MySerial *mySerial = nullptr;
    tcpClient *tcp_client = nullptr;
    tcpServer *tcp_server = nullptr;
    QApplication *app = nullptr;
    QThread *mySerial_thread = nullptr;
    QThread *tcp_client_thread = nullptr;
    QThread *tcp_server_thread = nullptr;
    QHash<QString, std::function<void(const QVariantMap&)>> switchMap;
};

// #endif
