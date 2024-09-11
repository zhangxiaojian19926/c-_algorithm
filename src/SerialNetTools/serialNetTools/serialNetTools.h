#pragma once

#include <QtWidgets/qapplication.h>
#include <functional>
#include <iostream>
#include "mainwindow.h"
#include "mySerial.h"
#include <QThread>
#include <QApplication>
#include <QHash>
#include <QVariantMap>
#include <qhash.h>
#include <qobjectdefs.h>
#include <qthread.h>

class serialNetTools:public QObject
{
    Q_OBJECT // 这个是Qt元对象系统的必须部分，启用信号、槽和属性等特性
public:
    serialNetTools(int argc, char** argv);
    ~serialNetTools();
    
    int init();

private:
        // 私有成员函数
    void switch_mySerial(const QVariantMap& msg);

public slots:
    void slot_switch(const QVariantMap &);

private:
    int argc_;
    char **argv;
    MainWindow *mainWindow = nullptr;
    MySerial *mySerial = nullptr;
    QApplication *app = nullptr;
    QThread *mySerial_thread = nullptr;
    QHash<QString, std::function<void(const QVariantMap&)>> switchMap;
};

// #endif
