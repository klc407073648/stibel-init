#include "UserController.h"
#include "UserConstant.h"
#include "HttpResponseUtils.h"
#include "FunStat.h"

using namespace stibel_init::common;
using namespace stibel_init::exception;
using namespace stibel_init::utils;

// Add definition of your processing function here
namespace drogon
{
	/*
    void printHttpRequestDetails(const HttpRequest &req)
    {
		
        LOG_INFO << "HttpRequest Body: {";
        LOG_INFO << "Method:" << req.getMethodString();
        LOG_INFO << "Headers:" << unordered_map2string(req.getHeaders());
        LOG_INFO << "Cookies:" << unordered_map2string(req.getCookies());
        LOG_INFO << "Query string:" << req.getQuery();
        LOG_INFO << "Body:" << req.getBody();
        LOG_INFO << "Path:" << req.getPath();
        LOG_INFO << "Version:" << req.getVersionString();
        LOG_INFO << "Parameters:" << unordered_map2string(req.getParameters());
        LOG_INFO << "LocalAddr:" << req.getLocalAddr().toIpPort();
        LOG_INFO << "PeerAddr:" << req.getPeerAddr().toIpPort();
        LOG_INFO << "}";
		
    }*/
    /**
     * @brief This template is used to convert a request object to a custom
     * type object. Users must specialize the template for a particular type.
     */
    template <>
    inline User fromRequest(const HttpRequest &req)
    {
        auto user = User(*req.getJsonObject());
        return user;
    }
}

namespace stibel_init {
namespace controller {

UserController::UserController() : srvPtr_(new UserServiceImpl())
{
    LOG_DEBUG << "UserController constructor!";
}

UserController::~UserController()
{
    LOG_DEBUG << "UserController destructor!";
}

void UserController::userRegister(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, User &&reqUser)
{
#undef FUN_NAME
#define FUN_NAME "UserController_userRegister"
    MAKE_FUN_STAT(0)
    try
    {
        std::string checkPassword = ((*(request->getJsonObject()))["checkPassword"]).asString();
        std::string userAccount = reqUser.getValueOfUseraccount();
        std::string userPassword = reqUser.getValueOfUserpassword();
        if (userAccount.size() == 0 || userPassword.size() == 0 || checkPassword.size() == 0)
        {
            MAKE_FUN_STAT(1)
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::ACCOUNT_OR_PWD_OR_VERI_PWD_OR_PLANT_CODE_EMPTY());
        }

        MAKE_FUN_STAT(2)
        long id = srvPtr_->userRegister(userAccount, userPassword, checkPassword);
        callNormalResponse(std::move(callback), id);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(3)
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::userLogin(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, User &&reqUser)
{
#undef FUN_NAME
#define FUN_NAME "UserController_userLogin"
    MAKE_FUN_STAT(0)
    try
    {
        std::string userAccount = reqUser.getValueOfUseraccount();
        std::string userPassword = reqUser.getValueOfUserpassword();
        if (userAccount.size() == 0 || userPassword.size() == 0)
        {
            MAKE_FUN_STAT(1)
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::ACCOUNT_OR_PWD_EMPTY());
        }

        MAKE_FUN_STAT(2)
        auto user = srvPtr_->userLogin(userAccount, userPassword, request);
        callNormalResponse(std::move(callback), user.toJson());
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(3)
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::userLogout(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
#undef FUN_NAME
#define FUN_NAME "UserController_userLogout"
    MAKE_FUN_STAT(0)
    try
    {
        if (request == nullptr)
        {
            MAKE_FUN_STAT(1)
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::REQUEST_EMPTY());
        }

        MAKE_FUN_STAT(2)
        long result = srvPtr_->userLogout(request);
        callNormalResponse(std::move(callback), result);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(2)
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::searchUsers(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
#undef FUN_NAME
#define FUN_NAME "UserController_searchUsers"
    MAKE_FUN_STAT(0)
    try
    {
        if (!srvPtr_->isAdmin(request))
        {
            MAKE_FUN_STAT(1)
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::NO_QUERY_PERMISSION());
        }

        MAKE_FUN_STAT(2)
        std::string username = request->getParameter("username");
        std::vector<User> userList = srvPtr_->userSearch(username);
        Json::Value userListJsonValue;
        for (auto &user : userList)
        {
            MAKE_FUN_STAT(3)
            userListJsonValue.append(user.toJson());
        }

        MAKE_FUN_STAT(4)
        callNormalResponse(std::move(callback), userListJsonValue);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(5)
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::getCurrentUser(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
#undef FUN_NAME
#define FUN_NAME "UserController_getCurrentUser"
    MAKE_FUN_STAT(0)
    try
    {
        bool isFind = request->getSession()->find(USER_LOGIN_STATE);
        if (!isFind)
        {
            MAKE_FUN_STAT(1)
            throw BusinessException(ErrorCode::NO_LOGIN());
        }

        MAKE_FUN_STAT(2)
        User curentUser = request->getSession()->get<User>(USER_LOGIN_STATE);
        long userId = curentUser.getValueOfId();
        User user = srvPtr_->userCurrent(userId);
        callNormalResponse(std::move(callback), user.toJson());
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(3)
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::deleteUsers(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, User &&reqUser)
{
#undef FUN_NAME
#define FUN_NAME "UserController_deleteUsers"
    MAKE_FUN_STAT(0)
    try
    {
        if (!srvPtr_->isAdmin(request))
        {
            MAKE_FUN_STAT(1)
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::NO_DELETE_PERMISSION());
        }

        auto id = (reqUser.getId() != nullptr) ? reqUser.getValueOfId() : -1;
        if (id <= 0)
        {
            MAKE_FUN_STAT(2)
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ID_ILLEGAL());
        }

        MAKE_FUN_STAT(3)
        bool ret = srvPtr_->userDelete(id);
        callNormalResponse(std::move(callback), ret);
    }
    catch (BusinessException &e)
    {
        MAKE_FUN_STAT(3)
        callErrorResponse(std::move(callback), e);
    }
}

} } // namespace stibel_init::controller