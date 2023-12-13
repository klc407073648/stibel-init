/**
 * @file TimerManager.h
 * @brief 描述信息
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_TimerManager_H__
#define __STIBEL_TimerManager_H__

#include<array>
#include<map>
#include<string>
#include <memory>
#include <iostream>
#include <Poco/Timer.h>
#include <Poco/Thread.h>
#include <Poco/Timestamp.h>
#include "RedisDbManager.h"
#include <chrono>

namespace stibel_init {
namespace common {

class TestTimerExample
{
public:
    void onTimer(Poco::Timer& t)
    {
        std::cout << "On Timer Callback"<<std::endl;
    }
};

// class TimerCallbackManager
// {
// public:
//     static TimerCallbackManager* getInstance();
//     std::shared_ptr<Poco::Timer> get(const std::string& name);
//     void registerCallBack(const std::string& name, int periodicInterval, int startInterval = 0);//统一注册回调函数

// private:
//     TimerCallbackManager();
//     ~TimerCallbackManager();

// private:
//     std::map<std::string, std::shared_ptr<Poco::TimerCallback>> timerMgr_;
// };


class TimerManager
{
public:
    static TimerManager* getInstance();
    std::shared_ptr<Poco::Timer> get(const std::string& name);
    void load(const std::string& name, int periodicInterval, int startInterval = 0);
    void load(const std::string& name, int periodicInterval, const Poco::AbstractTimerCallback& cb, int startInterval = 0);//模板类不能这样传递
    void loadRedis(const std::string& name, int periodicInterval, int startInterval = 0);
private:
    TimerManager();
    ~TimerManager();

private:
    std::map<std::string, std::shared_ptr<Poco::Timer>> timerMgr_;
    TestTimerExample te;
};
} } // namespace stibel_init::common

# endif