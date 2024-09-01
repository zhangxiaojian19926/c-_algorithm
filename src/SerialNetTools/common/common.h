#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <unistd.h>

using namespace std;

class Common
{
    public:
        Common();
        ~Common();

        void create_multilevel_dir(const std::string& dir_path);
        string get_cur_path();
        string get_log_path();
};