#include "myTcpServer.h"
#include "myLog.h"
#include <qglobal.h>
#include <qobject.h>
#include <qtcpsocket.h>

tcpServer::tcpServer(){
    LOG(INFO) << "tcpserver create";
}

tcpServer::~tcpServer(){
    stop();
    LOG(INFO) << "tcpserver delete";
}

// 初始化参数
void tcpServer::init(const std::string& ip, const int& port){
    ip_ = ip;
    port_ = port;
}

bool tcpServer::start(){
    stop();
    QVariantMap msg;
    tcpServer_ = new QTcpServer(this);
    if (tcpServer_->listen(QHostAddress::Any, port_)) {
        LOG(INFO) << "tcpserver listen success" << port_;
        isConnected_ = true;
    } else {
        LOG(INFO) << "tcpserver listen failed" << port_;
        isConnected_ = false;
    }

    // 发送信号，告诉qt_ui的状态
    msg["type"] = "tcpServer";
    msg["state"] = isConnected_;
    msg["ip"] = QString::fromStdString(ip_);
    msg["port"] = port_;
    emit signal_openStatus(msg);

    if (isConnected_ == true) {
        tcpSocket_ = new QTcpSocket(this);
        connect(tcpServer_, &QTcpServer::newConnection, [=]{
            tcpSocket_ = tcpServer_->nextPendingConnection();
            connect(tcpSocket_, &QTcpSocket::readyRead, this, &tcpServer::slot_read);
        });

        // 客户端断开连接
        connect(tcpSocket_, &QTcpSocket::disconnected, [=]{
            stop();
            isConnected_ = false;
        }); 
    }

    return isConnected_;
}

void tcpServer::stop(){
    if (tcpSocket_ != nullptr) {
        tcpSocket_->close();
        tcpSocket_->disconnect();
        delete tcpSocket_;
        tcpSocket_ = nullptr;
    }

    if (tcpServer_ != nullptr) {
        tcpServer_->close();
        tcpServer_->disconnect();
        delete tcpServer_;
        tcpServer_ = nullptr;
    }
}

void tcpServer::slot_start(){
    start();
}

// 写数据
void tcpServer::write(const QByteArray& msg){
    if (tcpServer_ != nullptr && tcpSocket_!= nullptr 
        && tcpSocket_->state() == QAbstractSocket::ConnectedState) {
        tcpSocket_->write(msg);
    }
}

// 外部写数据，数据需要转换成16进制进行传输
void tcpServer::slot_write(const QString& msg){
    LOG(INFO) << "write: " << msg.toStdString();
    QByteArray data = msg.toUtf8();
    write(data);
}

// 接受数据，socket连接上之后就立马开始接受数据
void tcpServer::slot_read(){
    readBuffer_.clear();
    readBuffer_ = tcpSocket_->readAll();
    LOG(INFO) << "tcp server read: " << QString::fromUtf8(readBuffer_).toStdString();

    // 建立连接开始接收数据
    QVariantMap msg;
    msg["type"] = "tcpServer";
    msg["data"] = readBuffer_;
    emit signal_tcpServer(msg); // 发送数据到qt_ui，展示在界面上
}
