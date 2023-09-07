#include "TestChannelController.h"
#include "HttpResponseUtils.h"

using namespace stibel_init::common;
using namespace stibel_init::exception;
using namespace stibel_init::utils;

namespace stibel_init {
namespace controller {

TestChannelController::TestChannelController() : srvPtr_(new TestChannelServiceImpl())
{
    LOG_DEBUG << "TestChannelController constructor!";
}

TestChannelController::~TestChannelController()
{
    LOG_DEBUG << "TestChannelController destructor!";
}

void TestChannelController::testChannel(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
    try
    {
        std::string res = srvPtr_->testChannel(request);
        callNormalResponse(std::move(callback), res);
    }
    catch (BusinessException &e)
    {
        callErrorResponse(std::move(callback), e);
    }
}

} } // namespace stibel_init::controller
