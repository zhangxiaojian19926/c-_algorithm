#include "myTcpClient.h"
#include "myLog.h"
#include <QtWidgets/qstyle.h>
#include <qchar.h>
#include <qglobal.h>
#include <qt5/QtCore/qchar.h>
#include <qtcpsocket.h>


tcpClient::tcpClient(){
    LOG(INFO) << "open tcpClient" ;
}

tcpClient::~tcpClient(){
    if (tcpSocket_ != nullptr) {
        tcpSocket_->close();
        if (tcpSocket_->state() == QAbstractSocket::ConnectedState) {
            tcpSocket_->disconnected(); // 断开链接
        }
        
        delete tcpSocket_;
        tcpSocket_ = nullptr;
    }
    LOG(INFO) << "close tcpClient" ;
}

// 初始化函数
void tcpClient::init(const std::string& groupID, const std::string& ip, const int& port)
{
    groupID_ = groupID;
    ip_ = ip;
    port_ = port;
}

// 打开
void tcpClient::slot_start(){
    start();
}

// 开启tcp 客户端
bool tcpClient::start(){
    // 如果已经连接，则断开连接。
    // 并删除之前的tcpSocket_
    if (tcpSocket_ != nullptr) {
        tcpSocket_->close();
        if (tcpSocket_->state() == QAbstractSocket::ConnectedState) {
            tcpSocket_->disconnected(); // 断开链接
        }
        
        delete tcpSocket_;
        tcpSocket_ = nullptr;
    }

    tcpSocket_ = new QTcpSocket();

    // connect 信号与槽
    connect(tcpSocket_, &QTcpSocket::connected, [=]{
        // isConnected_ = true;
        connect(tcpSocket_, &QTcpSocket::readyRead, 
                this, &tcpClient::slot_read);
    });
    
    connect(tcpSocket_, &QAbstractSocket::disconnected, [=]{
        isConnected_ = false;});

    tcpSocket_->connectToHost(QString::fromStdString(ip_), port_);

    QVariantMap msg;
    // 连接等待1s
    if (tcpSocket_->waitForConnected(1000)) {

        isConnected_ = true;
    } else {
        isConnected_ = false;
        stop();
    }

    msg["type"] = "tcpClient";
    msg["state"] = isConnected_;
    msg["groupID"] = QString::fromStdString(groupID_);
    msg["ip"] = QString::fromStdString(ip_);
    emit signal_openStatus(msg);

    return isConnected_;
}

// 关闭
void tcpClient::stop(){
    // 关闭
    if (tcpSocket_ != nullptr) {
        tcpSocket_->close();
        if (tcpSocket_->state() == QAbstractSocket::ConnectedState) {
            tcpSocket_->disconnectFromHost(); // 断开链接
        }
        
        delete tcpSocket_;
        tcpSocket_ = nullptr;
    }
}

// 读取信息的槽
void tcpClient::slot_read(){
    readBuffer_.clear();//接受一次清一次
    readBuffer_ = tcpSocket_->readAll();
    LOG(INFO) << "read: " << QString::fromUtf8(readBuffer_).toStdString();

    QVariantMap msg;
    msg["type"] = "tcpClient";
    msg["data"] = readBuffer_;
    emit signal_tcpClient(msg); // 显示在qt_ui 上
}

// 写入信息的槽，对外
void tcpClient::slot_write(const QString& msg)
{
    QByteArray data = msg.toUtf8();
    LOG(INFO) << "write: " << msg.toUtf8().toStdString();
    write(data);// 发送数据到服务器
}

void tcpClient::write(const QByteArray& msg)
{
    if (isConnected_ && tcpSocket_!= nullptr 
        && tcpSocket_->state() == QAbstractSocket::ConnectedState) {
        
        tcpSocket_->write(msg.toHex());// 转换成16进制发送
    } else {
        LOG(ERROR) << "tcpClient is not connected";
    }
}






