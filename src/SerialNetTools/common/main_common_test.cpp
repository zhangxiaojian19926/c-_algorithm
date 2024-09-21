#include "common.h"
#include "myLog.h"
#include "myDataBase.h"
#include <map>

using namespace std;

int main(int argv, char** argc)
{
    Common common;
    string log_path = common.get_log_path();
    myLog *myLog = new class myLog(log_path, "common");

    LOG(INFO) << "Hello world!";

    myDataBase myDataBase;

    myDataBase.setYamlNode("test.yaml");

    // 定义一个map，用于存储数据, 第一层map的key为qt_ui，第二层map的key为tcpClient_ip, tcpClient_port, tcpServer_ip, tcpServer_port
    // 并把这个值保存在yaml文件中
    std::map<std::string, std::map<std::string, std::string>> data = {
        {"qt_ui", {
            {"tcpClient_ip", "192.168.1.3"},
            {"tcpClient_port", "9002"},
            {"tcpServer_ip", "192.168.1.3"},
            {"tcpServer_port", "9001"}
        }}
    };

    myDataBase.writeToYaml(myDataBase.getYamlPath(), data);

    std::string tcpClient_ip = myDataBase.getYamlValue<std::string>("qt_ui", "tcpClient_ip"); // 取出对一个group中tcpClient_ip的值
    int tcpClient_port = myDataBase.getYamlValue<int>("qt_ui", "tcpClient_port"); // 取出对一个group中tcpClient_port的值

    std::cout << "tcpClient_ip: " << tcpClient_ip << std::endl;
    std::cout << "tcpClient_port: " << tcpClient_port << std::endl;

    myDataBase.UpdateYamlFile(myDataBase.getYamlPath(), "qt_ui", "tcpClient_port", "9005555"); // 更新yaml文件中的值
    int tcpClient_port_1 = myDataBase.getYamlValue<int>("qt_ui", "tcpClient_port"); // 取出对一个group中tcpClient_port的值
    
    std::cout << "tcpClient_port_1: " << tcpClient_port_1 << std::endl;

    delete myLog;
    return 0;
}