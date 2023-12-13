#include "InterfaceController.h"
#include "HttpResponseUtils.h"
#include "FunStat.h"

using namespace stibel_init::common;
using namespace stibel_init::exception;
using namespace stibel_init::utils;

namespace stibel_init {
namespace controller {

InterfaceController::InterfaceController() : srvPtr_(new InterfaceServiceImpl())
{
    LOG_DEBUG << "InterfaceController constructor!";
}

InterfaceController::~InterfaceController()
{
    LOG_DEBUG << "InterfaceController destructor!";
}

void InterfaceController::getBackground(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
#undef FUN_NAME
#define FUN_NAME "InterfaceController_getBackground"
    MAKE_FUN_STAT(0)
    try
    {
        MAKE_FUN_STAT(1)
        std::string url = srvPtr_->getBackground(request);
        callNormalResponse(std::move(callback), url);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(2)
        callErrorResponse(std::move(callback), e);
    }
}

void InterfaceController::getTranslate(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
#undef FUN_NAME
#define FUN_NAME "InterfaceController_getTranslate"
    MAKE_FUN_STAT(0)
    try
    {
        MAKE_FUN_STAT(1)
        std::string translalteRes = srvPtr_->getTranslate(request);
        callNormalResponse(std::move(callback), translalteRes);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(2)
        callErrorResponse(std::move(callback), e);
    }
}

void InterfaceController::getBackendVersion(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
#undef FUN_NAME
#define FUN_NAME "InterfaceController_getBackendVersion"
    MAKE_FUN_STAT(0)
    try
    {
        MAKE_FUN_STAT(1)
        std::string version = srvPtr_->getBackendVersion(request);
        callNormalResponse(std::move(callback), version);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(2)
        callErrorResponse(std::move(callback), e);
    }
}

void InterfaceController::getCurrentWeather(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
#undef FUN_NAME
#define FUN_NAME "InterfaceController_getCurrentWeather"
    MAKE_FUN_STAT(0)
    try
    {
        MAKE_FUN_STAT(1)
        std::string weatherInfo = srvPtr_->getCurrentWeather(request);
        callNormalResponse(std::move(callback), weatherInfo);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(2)
        callErrorResponse(std::move(callback), e);
    }
}

void InterfaceController::getFutureWeather(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
#undef FUN_NAME
#define FUN_NAME "InterfaceController_getFutureWeather"
    MAKE_FUN_STAT(0)
    try
    {
        MAKE_FUN_STAT(1)
        std::string weatherInfo = srvPtr_->getFutureWeather(request);
        callNormalResponse(std::move(callback), weatherInfo);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(2)
        callErrorResponse(std::move(callback), e);
    }
}

} } // namespace stibel_init::controller
