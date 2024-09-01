#include "common.h"
#include "myLog.h"

using namespace std;

int main(int argv, char** argc)
{
    Common common;
    string log_path = common.get_log_path();
    myLog *myLog = new class myLog(log_path, "common");

    LOG(INFO) << "Hello world!";

    delete myLog;
    return 0;
}