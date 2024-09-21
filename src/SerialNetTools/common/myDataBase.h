#pragma  once

#include <map>
#include <string>
#include <iostream>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>
#include "myLog.h"
#include "common.h"
#include <fstream>

class myDataBase{
public:
    myDataBase();
    ~myDataBase();

public:
    bool setYamlNode(const std::string& yaml_file_name);
    template<typename T>
    T getYamlValue(const std::string& group, const std::string& key) // 拿到对应key
    {
        // 不能沿用config_
        YAML::Node config = YAML::LoadFile(yaml_file_path_); // 加载yaml文件
        if (!config.IsNull()) {
            T data = config[group][key].as<T>(); // 将数据转出成指定的类型
            return data;
        }
    }

    bool writeToYaml(const std::string& filename, 
                     const std::map<std::string, std::map<std::string, std::string>> &data);

    bool UpdateYamlFile(const std::string& filename, const std::string& group,
                        const std::string& key, const std::string& value);

    std::string getYamlPath() const;

private:
    std::string yaml_file_path_; 
    YAML::Node config_;        
};