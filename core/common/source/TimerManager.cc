#include "TimerManager.h"

namespace stibel_init {
namespace common {

TimerManager *TimerManager::getInstance()
{
    static TimerManager timer;
    return &timer;
}

TimerManager::TimerManager()
{
}

TimerManager::~TimerManager()
{
}

void TimerManager::load(const std::string& name, int periodicInterval, int startInterval = 0)
{
    timerMgr_.emplace(name,new Poco::Timer(startInterval, periodicInterval));
    timerMgr_[name]->start(Poco::TimerCallback<TestTimerExample>(te, &TestTimerExample::onTimer));
}

void TimerManager::load(const std::string& name, int periodicInterval, const Poco::AbstractTimerCallback& cb, int startInterval = 0)
{
    timerMgr_.emplace(name,new Poco::Timer(startInterval, periodicInterval));
    timerMgr_[name]->start(cb);
}

void TimerManager::loadRedis(const std::string& name, int periodicInterval, int startInterval)
{
    timerMgr_.emplace(name,new Poco::Timer(startInterval, periodicInterval));
    timerMgr_[name]->start(Poco::TimerCallback<RedisDbManager>(*(RedisDbManager::getInstance()), &RedisDbManager::onRedisUpdateInterfaceTimer));
}

std::shared_ptr<Poco::Timer> TimerManager::get(const std::string& name)
{
    auto iter = timerMgr_.find(name);

    if(iter!=timerMgr_.end())
    {
        return iter->second;
    }

    return nullptr;
}

}} // namespace stibel_init::common