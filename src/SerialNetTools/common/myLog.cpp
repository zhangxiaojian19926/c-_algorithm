#include "myLog.h"

myLog::myLog(const std::string& log_path, const std::string& log_file_name)
    :m_log_path(log_path), m_log_file_name(log_file_name)
{
    FLAGS_alsologtostderr = true; // 输出到标准输出
    FLAGS_colorlogtostderr = true; // 输出到标准错误
    FLAGS_log_prefix = true; // 不输出日志前缀
    FLAGS_logbufsecs = 0; // 禁用日志缓冲区，实时输出
    FLAGS_max_log_size = 20; // 最大日志大小为20Mb, 超过20Mb则删除最早的日志
    FLAGS_stop_logging_if_full_disk = true; // 磁盘满时停止日志记录
    FLAGS_minloglevel = google::INFO; // 设置日志级别为INFO
    FLAGS_log_dir = m_log_path; // 设置日志目录

    // 设置log文件路径
    std::string log_info = m_log_path + "/" + m_log_file_name;
    google::SetLogDestination(google::GLOG_INFO, log_info.c_str());

    // 初始化Google日志库
    const char* log_argv = {" "};
    google::InitGoogleLogging(log_argv);   // 初始化Google日志库
}

myLog::~myLog()
{
    google::ShutdownGoogleLogging();// 关闭Google日志库
}






