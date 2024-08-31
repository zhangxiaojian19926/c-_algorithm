#include "mainwindow.h"
#include "rosNode.h"
#include "ui_mainwindow.h"
#include <qglobal.h>
#include <qobject.h>
#include <qpushbutton.h>

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , rosNode_(argc, argv)
{
    ui->setupUi(this);
    rosNode_.init();// 初始化ROS节点
    connect(ui->pushButton_send, &QPushButton::clicked, this, &MainWindow::slot_btn_send);// 连接按钮clicked信号和槽函数slot_btn_send
    connect(this, &MainWindow::signal_send, this, &MainWindow::slot_send_textEdit); // 连接信号signal_send和槽函数slot_send_text
    connect(this, &MainWindow::signal_rosPub, &rosNode_, &RosNode::slot_putStrMsg); // 连接信号signal_rosPub和槽函数slot_putStrMsg
    connect(&rosNode_, &RosNode::signal_strMsg, this, &MainWindow::slot_send_textEdit); // 连接信号signal_strMsg和槽函数slot_send_textEdit
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_send_textEdit(const QString &str)
{
    ui->textEdit_input->append(str); // 在文本框中显示接收到的字符串
}

void MainWindow::slot_btn_send()
{
    QString str = ui->lineEdit_input->text();
    qDebug() << "slot_btn_send: " << str; // 打印接收到的字符串
    // emit signal_send(str);
    emit signal_rosPub(str);// 发送信号
}

