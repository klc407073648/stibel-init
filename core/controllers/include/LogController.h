#ifndef __LOG_CONTROLLER_H__
#define __LOG_CONTROLLER_H__

#include <drogon/drogon.h>
#include "impl/LogServiceImpl.h"

namespace stibel_init {
namespace controller {

using namespace drogon;
using stibel_init::service::LogServicePtr;
using stibel_init::service::LogServiceImpl;
  
class LogController : public HttpController<LogController>
{
public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(LogController::writeUserLog, "/api/log/user/{1}", Post, Options);
  METHOD_LIST_END

public:
  LogController();
  ~LogController();

public:
  void writeUserLog(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &userId);

private:
  LogServicePtr srvPtr_;
};

} } // namespace stibel_init::controller

#endif //__LOG_CONTROLLER_H__