#include <iostream>
#include <string>
#include "serialNetTools.h"
#include "common.h"
#include "myLog.h"

int main(int argc, char *argv[])
{
    Common common;
    std::string log_path = common.get_log_path();
    myLog *myLog_1 = new myLog(log_path, "serialNetTools"); 
    serialNetTools mySerialTools(argc, argv);
    LOG(INFO)<< "serialNetTools start";
    int ret = mySerialTools.init();


    delete myLog_1;
    return ret;
}