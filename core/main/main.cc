#include <drogon/drogon.h>
#include "FunStat.h"
#include "RedisDbManager.h"
#include "TimerManager.h"

using namespace drogon;
using namespace stibel_init::common;

void setFileOutput()
{
    // 设置文件输出
    trantor::AsyncFileLogger asyncFileLogger;
    asyncFileLogger.setFileName("stibel-init", ".log", "../logs/");
    asyncFileLogger.startLogging();
    trantor::Logger::setOutputFunction(
        [&](const char *msg, const uint64_t len)
        {
            asyncFileLogger.output(msg, len);
        },
        [&]()
        { asyncFileLogger.flush(); });
    asyncFileLogger.setFileSizeLimit(100000000);
}

void supportCrossOrigin()
{
    app().registerPostHandlingAdvice([](const drogon::HttpRequestPtr &,
                                        const drogon::HttpResponsePtr &resp)
                                     {
        resp->addHeader("Access-Control-Allow-Origin", "*");
		resp->addHeader("Access-Control-Allow-Credentials", "true");
		resp->addHeader("Access-Control-Allow-Headers", "*");
		resp->addHeader("Access-Control-Allow-Methods", "*");
		resp->addHeader("Access-Control-Expose-Headers", "*"); });
}

int main()
{
     // 加载项目配置文件
    app().loadConfigFile("../conf/config.json");

    // 支持跨域请求
    supportCrossOrigin();

    //函数统计
    if(USE_FUN_STAT)
    {
        FunStat::getInstance()->init();
    }

    //Redis初始化
    RedisDbManager::getInstance()->load("../conf/redis.yml");

    //定时器初始化
    //TimerManager::getInstance()->load("testTimer",500, 1000);
    //TimerManager::getInstance()->load("redisTimer",500, Poco::TimerCallback<RedisDbManager>(RedisDbManager::getInstance(), &RedisDbManager::onRedisUpdateInterfaceTimer));
    TimerManager::getInstance()->loadRedis("redisTimer", 1 * 1000, 2000);// 1分钟定时刷新，考虑长连接
    
    // 设置文件输出
    // setFileOutput();

    app().run();

    return 0;
}
