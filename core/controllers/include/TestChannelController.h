#ifndef __TestChannel_CONTROLLER_H__
#define __TestChannel_CONTROLLER_H__

#include "inner/impl/TestChannelServiceImpl.h"
#include <drogon/drogon.h>

using namespace drogon;
using stibel_init::service::TestChannelServicePtr;
using namespace stibel_init::service;

namespace stibel_init {
namespace controller {

class TestChannelController : public drogon::HttpController<TestChannelController>
{
public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(TestChannelController::testChannel, "/api/testchannel", Post, Options);
  METHOD_LIST_END

public:
  TestChannelController();
  ~TestChannelController();

public:
  void testChannel(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);

private:
  TestChannelServicePtr srvPtr_;
};

} } // namespace stibel_init::controller

#endif //__TestChannel_CONTROLLER_H__
