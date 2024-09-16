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

signals:
    // UI 发送串口数据
    void signal_serialSend(const QString&);
    // 开关
    void signal_switch(const QVariantMap&);


private:
    Ui::MainWindow *ui;
    QString addTimerStr(const QString& msg);
};
#endif // MAINWINDOW_H
