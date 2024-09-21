#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <qchar.h>
#include <qobject.h>
#include <qvariant.h>
#include <QDateTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slot_send_textEdit(const QVariantMap&);
    // 按钮发送
    void slot_btn_mySerial_send();
    // 按钮开关
    void slot_btn_mySerial_open();
    // 功能模是否打开
    void slot_module_status(const QVariantMap& msg);
    // 刷新串口
    void slot_refresh_serial();

    // 打开tcpClient客户端
    void slot_btn_tcpClient_open();
    // 打开tcpServer服务器端
    void slot_btn_tcpServer_open();

    // 打开tcpClient客户端
    void slot_btn_tcpClient_send();
    // 打开tcpServer服务器端
    void slot_btn_tcpServer_send();

    // UI 发送数据到ros
    void slot_rosPub_send();

signals:
    // UI 发送串口数据
    void signal_serialSend(const QString&);
    // UI 发送Tcpclient
    void signal_tcpClientSend(const QString&);
    // UI 发送Tcpserver
    void signal_tcpServerSend(const QString&);
    // 开关
    void signal_switch(const QVariantMap&);

    // 做一个链接失败的提示
    void signal_tips(const QVariantMap&);

    // UI 发送数据到ros
    void signal_rosPub(const QString&);


private:
    Ui::MainWindow *ui;
    QString addTimerStr(const QString& msg);
};
#endif // MAINWINDOW_H
