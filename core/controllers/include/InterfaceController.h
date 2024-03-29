#ifndef __INTERFACE_CONTROLLER_H__
#define __INTERFACE_CONTROLLER_H__

#include "impl/InterfaceServiceImpl.h"

namespace stibel_init {
namespace controller {

using namespace drogon;
using stibel_init::service::InterfaceServicePtr;
using stibel_init::service::InterfaceServiceImpl;

class InterfaceController : public HttpController<InterfaceController>
{
public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(InterfaceController::getBackground, "/api/background/get/random", Post, Options); //, "LoginFilter");
  ADD_METHOD_TO(InterfaceController::getTranslate, "/api/fanyi/translate", Post, Options);
  ADD_METHOD_TO(InterfaceController::getCurrentWeather, "/api/weather/now", Post, Options);
  ADD_METHOD_TO(InterfaceController::getFutureWeather, "/api/weather/future", Post, Options);
  ADD_METHOD_TO(InterfaceController::getBackendVersion, "/api/backend/version", Get, Options);
  METHOD_LIST_END

public:
  InterfaceController();
  ~InterfaceController();

public:
  void getBackground(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
  void getTranslate(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
  void getBackendVersion(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
  void getCurrentWeather(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
  void getFutureWeather(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);

private:
  InterfaceServicePtr srvPtr_;
};

} } // namespace stibel_init::controller

#endif //__INTERFACE_CONTROLLER_H__