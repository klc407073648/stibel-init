#include "RedisDbManager.h"
#include "StiBel/Common/Config/ConfigFile.h"
#include "StiBel/Common/Config/ConfigLoader.h"
#include "StiBel/Util/Util.h"
#include <memory>
#include <stdio.h>
#include <vector>

using namespace StiBel::Common::Config;

namespace stibel_init {
namespace common {

RedisDbManager *RedisDbManager::getInstance()
{
    static RedisDbManager redis;
    return &redis;
}

RedisDbManager::RedisDbManager()
{
}

RedisDbManager::~RedisDbManager()
{
}

void RedisDbManager::load(const std::string& fileName)
{
    ConfigFile configFile(fileName, "config数据");
    StiBel::Common::Config::ConfigLoader loader(configFile);
    const YAML::Node &value = loader.yamlValue();

    std::map<std::string, std::map<std::string, std::string>> m_configMap;
    std::map<std::string, std::string> m_map;

    //数据库的参数
    m_map["host"]=value["ip"].as<std::string>() + ":" +value["port"].as<std::string>();
    m_map["type"]="redis";
	m_map["passwd"]=value["passwd"].as<std::string>();
	m_map["timeout"]="100";
	m_map["name"]=fileName;
    m_map["pool"]=value["pool"].as<std::string>();
    m_configMap[fileName]=m_map;
    redisMgr_.emplace(fileName,new RedisManager(m_configMap));

    //for test
    // redisMgr_[fileName]->get(fileName)->cmd("SET %s %s", "name", "Jason");
    // redisMgr_[fileName]->get(fileName)->cmd("SET %s %s", "num", "123456");
    // redisMgr_[fileName]->get(fileName)->cmd("SET %s %s", "address", "NJ");
}



std::shared_ptr<RedisManager> RedisDbManager::get(const std::string& fileName)
{
    auto iter = redisMgr_.find(fileName);

    if(iter!=redisMgr_.end())
    {
        return iter->second;
    }

    return nullptr;
}

}} // namespace stibel_init::common