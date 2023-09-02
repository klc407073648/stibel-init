#ifndef __TestChannel_SERVICE_IMPL_H__
#define __TestChannel_SERVICE_IMPL_H__

#include "inner/TestChannelService.h"
#include "Interface.h"
#include <drogon/drogon.h>
#include <map>

namespace stibel_init {
namespace service {

using drogon_model::stibel_init::Interface;

class TestChannelServiceImpl : public TestChannelService
{
public:
  TestChannelServiceImpl();
  ~TestChannelServiceImpl();
  std::string testChannel(const HttpRequestPtr &request) override;

private:
private:
};

} } // namespace stibel_init::service

#endif //__TestChannel_SERVICE_IMPL_H__