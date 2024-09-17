#pragma once

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QTimer>
#include <QVariantMap>
#include "myLog.h"

class tcpClient:public QObject
{
    Q_OBJECT
public:
    tcpClient();
    ~tcpClient();

public:
    // tcp客户端初始化
    void init(const std::string& groupID, const std::string& ip, const int& port);

    // 确保可以使用反射机制进行调用
    Q_INVOKABLE bool start();//开启
    Q_INVOKABLE void stop();//关闭

    void write(const QByteArray& msg);

// 对外接口
public slots:
    void slot_write(const QString& msg);// 写入数据，调用write
    void slot_start();// 开启

// 对内接口
private slots:
    void slot_read();// 读取数据    

signals:
    void signal_openStatus(const QVariantMap& msg);// 串口打开成功的信号
    void signal_tcpClient(const QVariantMap& msg);// 

private:
    std::string groupID_;
    std::string ip_;
    int port_;
    QTcpSocket *tcpSocket_ = nullptr;
    bool isConnected_ = false;// 是否连接成功
    QByteArray readBuffer_;
};