#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "rosNode.h"

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
    void slot_btn_send();
    void slot_send_textEdit(const QString &);//接收信号

signals:
    void signal_send(const QString &);//发送信号
    void signal_rosPub(const QString &);//发送信号

private:
    Ui::MainWindow *ui;
    RosNode rosNode_;// 声明一个RosNode对象
};
#endif // MAINWINDOW_H
