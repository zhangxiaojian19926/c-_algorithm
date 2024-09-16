#pragma once

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QByteArray>
#include <QString>
#include <QTimer>
#include <QVariantMap>
#include <qglobal.h>
#include <qtcpsocket.h>
#include "myLog.h"

class tcpServer:public QObject
{
    Q_OBJECT
public:
    tcpServer();
    ~tcpServer();

public:
    // tcp服务器端初始化
    void init(const std::string& ip, const int& port);

    // 确保可以使用反射机制进行调用
    Q_INVOKABLE bool start();//开启
    Q_INVOKABLE void stop();//关闭

private:
    void write(const QByteArray& msg);

// 对外槽
public slots:
    void slot_write(const QString& msg);// 写入数据，调用write
    void slot_start();// 开启

private slots:
    void slot_read();// 读取数据

signals:
    void signal_tcpServer(const QVariantMap& msg); // 发送数据
    void signal_openStatus(const QVariantMap& msg);// 串口打开成功的信号

private:
    QTcpServer *tcpServer_ = nullptr;
    QTcpSocket *tcpSocket_ = nullptr;
    QByteArray readBuffer_;
    std::string ip_;
    int port_;
    bool isConnected_ = false;// 是否连接成功
};