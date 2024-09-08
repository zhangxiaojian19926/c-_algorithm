#pragma once

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QVariantMap>
#include "myLog.h"

using namespace std;

class MySerial : public QObject
{
    Q_OBJECT
public:
    MySerial();
    ~MySerial();

public:
    Q_INVOKABLE bool start();
    Q_INVOKABLE void stop();
    void init(const string& groupID,const string& serialName,const int& baudRate,
                const int& checkData,const int& dataBit,const int& stopBit);

public slots:
    void slot_read();
    void slot_write(const QString& msg);
    void slot_start();

signals:
    void signal_serial(const QVariantMap& msg);
    void signal_openStatus(const QVariantMap& msg);

private:
    string groupID_; //ID
    string serialName_ = "COM1";//
    int baudRate_ = 115200;
    int checkData_ = 0;
    int dataBit_ = 8;
    int stopBit_ = 1;

    QSerialPort *serialPort_ = nullptr;

};