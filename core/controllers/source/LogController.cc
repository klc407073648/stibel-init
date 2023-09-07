#include "LogController.h"
#include "HttpResponseUtils.h"

using namespace stibel_init::common;
using namespace stibel_init::exception;
using namespace stibel_init::utils;

namespace stibel_init {
namespace controller {

LogController::LogController() : srvPtr_(new LogServiceImpl())
{
    LOG_DEBUG << "LogController constructor!";
}

LogController::~LogController()
{
    LOG_DEBUG << "LogController destructor!";
}

void LogController::writeUserLog(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &userId)
{
    // 判断isMember再取值
    std::string content = ((*(request->getJsonObject()))["content"]).asString(); // 如果测试Postman测试无content场景会出现Segmentation fault

    try
    {
        bool res = srvPtr_->writeUserLog(atol(userId.c_str()), content);
        callNormalResponse(std::move(callback), res);
    }
    catch (BusinessException &e)
    {
        callErrorResponse(std::move(callback), e);
    }
}

} } // namespace stibel_init::controller
