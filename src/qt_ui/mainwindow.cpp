#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_send, &QPushButton::clicked, this, &MainWindow::slot_btn_send);// 连接按钮clicked信号和槽函数slot_btn_send

    connect(this, &MainWindow::signal_send, this, &MainWindow::slot_send_text); // 连接信号signal_send和槽函数slot_send_text

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_send_text(const QString &str)
{
    ui->textEdit_input->append(str); // 在文本框中显示接收到的字符串
}

void MainWindow::slot_btn_send()
{
    QString str = ui->lineEdit_input->text();
    emit signal_send(str);
}

