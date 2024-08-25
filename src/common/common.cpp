#include "common.h"
#include <cstddef>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


Common::Common()
{
    cout<< "create commont" <<endl;
}

Common::~Common()
{
    cout<< "delete commont" <<endl;
}

void Common::create_multilevel_dir(const std::string& dir_path)
{
    // 创建多级目录
    int ret = mkdir(dir_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (ret!= 0) {
        cout << "Failed to create directory: " << dir_path << endl;
    }
}

string Common::get_cur_path()
{
    // 获取当前程序的路径
    char *current_path;
    current_path = getcwd(NULL, 0);
    string str_current_path(current_path, strlen(current_path));
    free(current_path);// 释放内存
    return str_current_path.c_str();
}

string Common::get_log_path()
{
    // 获取当前程序的路径
    string path = get_cur_path();
    // 去掉程序名，只保留路径
    size_t pos = path.find_last_of("/");
    if (pos!= string::npos) {
        path = path.substr(0, pos);
    }

    // 拼接日志路径
    path = path + "/log";
    if(access(path.c_str(), F_OK)!= 0)
    {
        cout << "log path not exist!" << endl;
        create_multilevel_dir(path);
    }

    return path;
}