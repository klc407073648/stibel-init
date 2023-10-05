#include <drogon/drogon.h>
#include "FunStat.h"
using namespace drogon;

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
    stibel_init::common::FunStat::getInstance()->init();
    // 设置文件输出
    // setFileOutput();

    // 加载项目配置文件
    app().loadConfigFile("../conf/config.json").run();

    // 支持跨域请求
    supportCrossOrigin();
}
