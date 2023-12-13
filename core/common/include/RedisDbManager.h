/**
 * @file RedisDbManager.h
 * @brief 描述信息
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_RedisDbManager_H__
#define __STIBEL_RedisDbManager_H__

#include<array>
#include<map>
#include<string>
#include "StiBel/Data/Redis/Redis.h"
#include <Poco/Timer.h>
#include "Interface.h"
#include <drogon/drogon.h>

using namespace StiBel::Data::Redis;
using drogon_model::stibel_init::Interface;

namespace stibel_init {
namespace common {

class RedisDbManager
{
public:
    static RedisDbManager* getInstance();
    std::shared_ptr<RedisManager> get(const std::string& fileName);
    void load(const std::string& fileName);
public:
    void onRedisUpdateInterfaceTimer(Poco::Timer& t)
    {
        std::cout << "On onRedisUpdateInterfaceTimer Callback"<<std::endl;
        if( redisMgr_.size() == 0)
        {
            std::cout << "No Redis Instance do nothing"<<std::endl;
        }
        
        //从MySQL更新数据到Redis
        auto iter = redisMgr_.begin();
        try
        {
            Mapper<Interface> interfaceMapper_ = drogon::orm::Mapper<Interface>(drogon::app().getDbClient());
            auto interfaces = interfaceMapper_.findAll();
            for (auto &interface : interfaces)
            {
                std::string name = interface.getValueOfName();
                int isDelete = interface.getValueOfIsdelete();

                // 接口未被删除
                if (isDelete == 0)
                {
                    // std::cout << "name:" << name <<std::endl;
                    // std::cout << "interface:" << interface.toJson().toStyledString() <<std::endl;
                    redisMgr_[iter->first]->get(iter->first)->cmd("SET %s %s", name.c_str(),(interface.toJson().toStyledString()).c_str());
                }
            }
        }
        catch (const DrogonDbException &e)
        {
            std::cout << "onRedisUpdateInterfaceTimer DrogonDbException"<<std::endl;
        }
    }

private:
    RedisDbManager();
    ~RedisDbManager();

private:
    std::map<std::string, std::shared_ptr<RedisManager>> redisMgr_;
};
} } // namespace stibel_init::common

# endif