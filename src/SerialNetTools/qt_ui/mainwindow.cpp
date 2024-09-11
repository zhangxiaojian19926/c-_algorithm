#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdatetime.h>
#include <qglobal.h>
#include <qlocale.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qserialportinfo.h>
#include <qt5/QtCore/qchar.h>
#include <string>
#include "myLog.h"

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 打开串口
    connect(ui->pushButton_serialOpen, &QPushButton::clicked, 
                this, &MainWindow::slot_btn_mySerial_open);
    // 发送数据给串口显示框
    connect(ui->pushButton_serialSend, &QPushButton::clicked, 
                this, &MainWindow::slot_btn_mySerial_send);   

    //加载串口列表
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    foreach(const QSerialPortInfo &info, list){
        ui->comboBox_serialName->addItem("/dev/" + info.portName());
        LOG(INFO) << ("/dev/" + info.portName()).toStdString();
    }

    LOG(INFO) << "UI is open!";

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 显示接收数据
void MainWindow::slot_send_textEdit(const QVariantMap& msg)
{
    if (!msg.contains("type")) {
        return;
    }

    if (!msg.contains("data")) {
        return;
    }

    QString type = msg["type"].toString();
    QString data = msg["data"].toString();

    QString str = addTimerStr("mySerial receive: ");
    str += data;
    ui->textEdit_recv->append(str);// 显示到文本框
}

// 时间添加
QString MainWindow::addTimerStr(const QString& msg)
{
    QDateTime now = QDateTime::currentDateTime();
    QString str = now.toString("yyyy-MM-dd hh:mm:ss");
    str += "  " + msg;
    return str;
}

// 按钮发送
void MainWindow::slot_btn_mySerial_send()
{
    QString send_msg = ui->lineEdit_serialInput->text();
    emit signal_serialSend(send_msg);// 发送出去，给到串口
    QString str = addTimerStr("mySerial send: ");
    str += send_msg;
    ui->textEdit_send->append(str);// 显示到文本框
}

// 按钮开关
void MainWindow::slot_btn_mySerial_open()
{
    QString serialName = ui->comboBox_serialName->currentText();
    int baudRate = ui->lineEdit_baudRate->text().toInt();
    QString checkData = ui->comboBox_checkData->currentText();
    QString dataBit = ui->comboBox_dataBit->currentText();
    QString stopBit = ui->comboBox_stopBit->currentText();

    // 串口奇偶校验
    int check_num = -1;
    if (checkData == "NoParity") {
        check_num = 0;
    } else if (checkData == "EvenParity") {
        check_num = 2;
    } else if (checkData == "OddParity") {
        check_num = 3;
    } else if (checkData == "SpaceParity") {
        check_num = 4;
    } else if (checkData == "MarkParity") {
        check_num = 5;
    } else {
        check_num = -1;
    }

    // 封装成qmap
    QVariantMap data;
    data["type"] = "mySerial";
    data["serialName"] = serialName;
    data["baudRate"] = baudRate;
    data["checkData"] = check_num;
    data["dataBit"] = dataBit;
    data["stopBit"] = stopBit;

    // 打开关闭按钮并设置其颜色
    if (ui->pushButton_serialOpen->text() == "打开") {
        data["switch"] = true;
        ui->pushButton_serialOpen->setText("关闭");
        ui->pushButton_serialOpen->setStyleSheet("background-color: green;");
    } else {
        data["switch"] = false;
        ui->pushButton_serialOpen->setText("打开");
        ui->pushButton_serialOpen->setStyleSheet("background-color: { }");
    }

    ui->pushButton_serialOpen->setEnabled(true); // 打开，可以操作

    // 发送给串口
    emit signal_switch(data);
}

// 各个模块的状态
void MainWindow::slot_module_status(const QVariantMap& msg)
{
    if (!msg.contains("type")) {
        return;
    } 

    if (!msg.contains("state")) {
        return;
    }

    QString type = msg["type"].toString();
    bool state = msg["state"].toBool();
    
    if (type == "mySerial") {
        if (!state) {
            LOG(INFO) << "mySerial is not open!";
            ui->pushButton_serialOpen->setText("打开");
            ui->pushButton_serialOpen->setStyleSheet("background-color: { }");

            QDateTime now = QDateTime::currentDateTime();
            QString str = addTimerStr("mySerial");
            str += " is not open!";
            ui->textEdit_send->append(str);// 显示到文本框
        } else {
            LOG(INFO) << "mySerial is open!";
            ui->pushButton_serialOpen->setText("关闭");
            ui->pushButton_serialOpen->setStyleSheet("background-color: green;");
        }        

        ui->pushButton_serialOpen->setEnabled(true); // 开启
    }
}
