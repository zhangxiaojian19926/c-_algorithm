#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qglobal.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <string>
#include "myLog.h"

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    string log_path = common_log_.get_log_path();
    qDebug() << "log_path: " << log_path.c_str();
    myLog *myLog = new class myLog(log_path, "main");

    LOG(INFO) << "MainWindow Hello world!";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_send_textEdit(const QString &str)
{
    // ui->textEdit_input->append(str); // 在文本框中显示接收到的字符串
}

void MainWindow::slot_btn_send()
{
    // QString str = ui->lineEdit_input->text();
    // qDebug() << "slot_btn_send: " << str; // 打印接收到的字符串
}

