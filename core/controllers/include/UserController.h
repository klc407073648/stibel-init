#ifndef __USER_CONTROLLER_H__
#define __USER_CONTROLLER_H__

#include "impl/UserServiceImpl.h"
#include "User.h"
#include "UserDescription.h"
#include <drogon/drogon.h>

namespace stibel_init {
namespace controller {

using namespace drogon;
using stibel_init::service::UserServicePtr;
using stibel_init::service::UserServiceImpl;
using stibel_init::utils::UserDescription;

class UserController : public drogon::HttpController<UserController>
{
public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(UserController::userRegister, "/api/user/register", Post, Options);
  ADD_METHOD_TO(UserController::userLogin, "/api/user/login", Post, Options);
  ADD_METHOD_TO(UserController::userLogout, "/api/user/logout", Post, Options);
  ADD_METHOD_TO(UserController::searchUsers, "/api/user/search", Get, Options);
  ADD_METHOD_TO(UserController::getCurrentUser, "/api/user/current", Get, Options);
  ADD_METHOD_TO(UserController::deleteUsers, "/api/user/delete", Post, Options);
  METHOD_LIST_END

public:
  UserController();
  ~UserController();
  
public:
  void userRegister(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, User &&reqUser);
  void userLogin(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, User &&reqUser);
  void userLogout(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
  void searchUsers(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
  void getCurrentUser(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
  void deleteUsers(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, User &&reqUser);

private:
  UserServicePtr srvPtr_;
};

} } // namespace stibel_init::controller

#endif //__USER_CONTROLLER_H__
