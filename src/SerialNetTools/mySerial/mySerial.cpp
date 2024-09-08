#include "mySerial.h"

/**
 * 构造函数
 */
MySerial::MySerial()
{

}

/**
 * 串口模块初始化参数
 */
void MySerial::init(const string& groupID,const string& serialName,const int& baudRate,
                const int& checkData,const int& dataBit,const int& stopBit)
{
    groupID_    = groupID;
    serialName_ = serialName;
    baudRate_   = baudRate;
    checkData_  = checkData;
    dataBit_    = dataBit;
    stopBit_    = stopBit;
}

/**
 * 析构函数
 */
MySerial::~MySerial()
{
    if(serialPort_ != nullptr)
    {
        serialPort_->flush();//清空缓冲区
        serialPort_->close();
        serialPort_->deleteLater();
        serialPort_ = nullptr;
    }
}

/**
 * 读取串口数据
 */
void MySerial::slot_read()
{
    if(serialPort_->bytesAvailable()>0)
    {
        QByteArray serial_data;
        serial_data = serialPort_->readAll();

        LOG(INFO)<<"serial_data: "<<QString::fromUtf8(serial_data).toStdString();

        QVariantMap data;
        data["type"] = "mySerial";
        data["data"] = serial_data;
        emit signal_serial(data);
    }
}

/**
 * 写入串口数据
 */
void MySerial::slot_write(const QString& msg)
{
    if(serialPort_ != nullptr)
    {
        QByteArray data = msg.toUtf8();
        serialPort_->write(data);
    }
}

/**
 * 开启串口
 */
void MySerial::slot_start()
{
    start();
}

/**
 * 尝试打开串口
 */
bool MySerial::start()
{
    if(serialPort_ != nullptr)
    {
        serialPort_->flush();//清空缓冲区
        serialPort_->close();
        serialPort_->deleteLater();
        serialPort_ = nullptr;
    }

    serialPort_ = new QSerialPort();
    //1、设置串口名称
    serialPort_->setPortName(QString::fromStdString(serialName_));
    //2、设置波特率
    serialPort_->setBaudRate(baudRate_);
    //3、设置校验位
    switch(checkData_)
    {
        case 0:serialPort_->setParity(QSerialPort::NoParity);break;
        case 2:serialPort_->setParity(QSerialPort::EvenParity);break;
        case 3:serialPort_->setParity(QSerialPort::OddParity);break;
        case 4:serialPort_->setParity(QSerialPort::SpaceParity);break;
        case 5:serialPort_->setParity(QSerialPort::MarkParity);break;
        case -1:serialPort_->setParity(QSerialPort::UnknownParity);break;
        default: break;
    }
    //4、设置数据位
    switch(dataBit_)
    {
        case 5:serialPort_->setDataBits(QSerialPort::Data5);break;
        case 6:serialPort_->setDataBits(QSerialPort::Data6);break;
        case 7:serialPort_->setDataBits(QSerialPort::Data7);break;
        case 8:serialPort_->setDataBits(QSerialPort::Data8);break;
        case -1:serialPort_->setDataBits(QSerialPort::UnknownDataBits);break;
        default: break;
    }
    //5、设置停止位
    switch(stopBit_)
    {
        case 1:serialPort_->setStopBits(QSerialPort::OneStop);break;
        case 2:serialPort_->setStopBits(QSerialPort::TwoStop);break;
        case 3:serialPort_->setStopBits(QSerialPort::OneAndHalfStop);break;
        case -1:serialPort_->setStopBits(QSerialPort::UnknownStopBits);break;
        default: break;
    }
    //6、设置控制流
    serialPort_->setFlowControl(QSerialPort::NoFlowControl);
    //7、打开串口
    bool open_state = serialPort_->open(QIODevice::ReadWrite);
    if(open_state)
    {
        //建立读取串口数据的连接
        QObject::connect(serialPort_,&QSerialPort::readyRead,this,&MySerial::slot_read);
        QVariantMap  stateMap;
        stateMap["type"] = "mySerial";
        stateMap["state"] = true;
        std::cout << "串口打开成功" << std::endl;
        emit signal_openStatus(stateMap);
        return true;
    }
    else
    {
        stop();
        QVariantMap  stateMap;
        stateMap["type"] = "mySerial";
        stateMap["state"] = false;
        std::cout << "串口打开失败" << std::endl;
        emit signal_openStatus(stateMap);
        return false;
    }

}

/**
 * 关闭串口
 */
void MySerial::stop()
{
    if(serialPort_ != nullptr)
    {
        serialPort_->flush();//清空缓冲区
        serialPort_->close();
        serialPort_->deleteLater();
        serialPort_ = nullptr;
    }
}