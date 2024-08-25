#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slot_btn_send();

    void slot_send_text(const QString &);//接收信号

signals:
    void signal_send(const QString &);//发送信号

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
