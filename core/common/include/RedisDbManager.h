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

using namespace StiBel::Data::Redis;

namespace stibel_init {
namespace common {

class RedisDbManager
{
public:
    static RedisDbManager* getInstance();
    std::shared_ptr<RedisManager> get(const std::string& fileName);
    void load(const std::string& fileName);

private:
    RedisDbManager();
    ~RedisDbManager();

private:
    std::map<std::string, std::shared_ptr<RedisManager>> redisMgr_;
};
} } // namespace stibel_init::common

# endif