#include "myDataBase.h"
#include "common.h"
#include "myLog.h"
#include <yaml-cpp/emitter.h>
#include <yaml-cpp/emittermanip.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

myDataBase::myDataBase(){

}

myDataBase::~myDataBase(){

}

// 设置yaml的文件名字 路径固定在config文件夹中
// config文件夹不存在的话，就创建，并创建yaml文件
bool myDataBase::setYamlNode(const std::string& yaml_file_name){
    Common common;
    std::string current_path = common.get_cur_path();
    int index = current_path.find_last_of("/");
    std::string yaml_path = current_path.substr(0, index) + "/config";
    if(access(yaml_path.c_str(), F_OK)!= 0)
    {
        cout << "create yaml file not exist!" << endl;
        common.create_multilevel_dir(yaml_path.c_str());
    }

    // config存在的化就加载yaml文件
    yaml_file_path_ = yaml_path + "/" + yaml_file_name;
    LOG(INFO) << "yaml file path: " << yaml_file_path_;

    // 如果yaml文件不存在的话，就创建一个空的yaml文件
    if (access(yaml_file_path_.c_str(), F_OK)!= 0) {
        cout << "yaml expception"  << endl;
        std::ofstream fout(yaml_file_path_);
        fout.close();
    }

    // 加载yaml文件
    config_ = YAML::LoadFile(yaml_file_path_);

    return true;
}

// 将数据写入到yaml文件中
bool myDataBase::writeToYaml(const std::string& yaml_path, 
                    const std::map<std::string, std::map<std::string, std::string>> &data){

    // 遍历data，将其写入yaml文件
    try {
        YAML::Emitter out;
        out<<YAML::BeginMap;
        // 遍历map
        for (const auto& outerPair : data) {
            out<<YAML::Key<<outerPair.first<<YAML::Value<<YAML::BeginMap;// yaml文件中，第一层map开始
            // 遍历第二层data
            for (const auto& innerPair : outerPair.second) {
                out<<YAML::Key<<innerPair.first<<YAML::Value<<innerPair.second;
            }
            out<<YAML::EndMap;// yaml文件中，第二层map结束

            ofstream fout(yaml_path);
            fout << out.c_str();
            fout.close();

            return true;
        }
    } catch (const std::exception& e) {
        LOG(INFO) << "Error writing to YAML file: " << e.what() << std::endl;
        return false;
    }
}

// 更新yaml文件中对应key的值
bool myDataBase::UpdateYamlFile(const std::string& yaml_path, const std::string& groupName,
                    const std::string& key, const std::string& value){
    try {
        // 尝试加载yaml文件
        cout << yaml_path << endl;
        if (config_.IsNull()) {
            config_ = YAML::LoadFile(yaml_path);
        }

        // 检查指定的参数
        if (config_[groupName]) {
            // 更新指定参数
            config_[groupName][key] = value;

            // 保存更新后的配置
            std::ofstream fout(yaml_path);
            fout << config_;
            fout.flush();
            fout.close();

            return true;
        } else {    
            LOG(INFO) << "GroupName not found in YAML file: " << groupName;
            return false;
        }
    } catch (const YAML::ParserException& e) {
        LOG(ERROR) << "Error parsing YAML file: " << e.what();
    } catch (const YAML::EmitterException& e) {
        LOG(ERROR) << "Failed to emmit YAML file: " << e.what();
    } catch (const std::exception& e) {
        LOG(ERROR) << "Error Caught: " << e.what();
    }

    return false;// 更新失败
}

// 获取yaml的目录路径
std::string myDataBase::getYamlPath() const{
    return yaml_file_path_;
}
