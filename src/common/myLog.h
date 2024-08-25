#pragma once
#define GLOG_EXPORT
#define GLOG_NO_EXPORT

#include "glog/logging.h"
#include <string>
#include <iostream>

class myLog
{
    public:
        myLog(const std::string& log_path, const std::string& log_file_name);
        ~myLog();

        /**
         * 获取 myLog 类的实例（单例模式）。
         * 该函数返回 myLog 类的静态实例的地址，确保整个程序中只有一个 myLog 对象。
         * 首次调用该函数时，myLog 类的静态实例将被创建。
         *
         * @return myLog*，指向 myLog 实例的指针。
         */
        // static myLog* getInstance()
        // {
        //     static myLog instance;
        //     return &instance;
        // }

        void setLogPath(const std::string& path);
        void setLogLevel(const std::string& level);

        void info(const std::string& msg);
    
    private:    
        std::string m_log_path; 
        std::string m_log_file_name;
};


