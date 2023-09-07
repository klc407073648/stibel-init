#include "UserController.h"
#include "UserConstant.h"
#include "HttpResponseUtils.h"

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
    std::string checkPassword = ((*(request->getJsonObject()))["checkPassword"]).asString();

    try
    {
        std::string userAccount = reqUser.getValueOfUseraccount();
        std::string userPassword = reqUser.getValueOfUserpassword();
        if (userAccount.size() == 0 || userPassword.size() == 0 || checkPassword.size() == 0)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::ACCOUNT_OR_PWD_OR_VERI_PWD_OR_PLANT_CODE_EMPTY());
        }

        long id = srvPtr_->userRegister(userAccount, userPassword, checkPassword);
        callNormalResponse(std::move(callback), id);
    }
    catch (BusinessException &e)
    {
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::userLogin(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, User &&reqUser)
{
    try
    {
        std::string userAccount = reqUser.getValueOfUseraccount();
        std::string userPassword = reqUser.getValueOfUserpassword();
        if (userAccount.size() == 0 || userPassword.size() == 0)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::ACCOUNT_OR_PWD_EMPTY());
        }

        auto user = srvPtr_->userLogin(userAccount, userPassword, request);
        callNormalResponse(std::move(callback), user.toJson());
    }
    catch (BusinessException &e)
    {
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::userLogout(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
    try
    {
        if (request == nullptr)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::REQUEST_EMPTY());
        }

        long result = srvPtr_->userLogout(request);
        callNormalResponse(std::move(callback), result);
    }
    catch (BusinessException &e)
    {
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::searchUsers(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
    try
    {
        if (!srvPtr_->isAdmin(request))
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::NO_QUERY_PERMISSION());
        }

        std::string username = request->getParameter("username");
        std::vector<User> userList = srvPtr_->userSearch(username);
        Json::Value userListJsonValue;
        for (auto &user : userList)
        {
            userListJsonValue.append(user.toJson());
        }

        callNormalResponse(std::move(callback), userListJsonValue);
    }
    catch (BusinessException &e)
    {
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::getCurrentUser(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
    try
    {
        bool isFind = request->getSession()->find(USER_LOGIN_STATE);
        if (!isFind)
        {
            throw BusinessException(ErrorCode::NO_LOGIN());
        }

        User curentUser = request->getSession()->get<User>(USER_LOGIN_STATE);
        long userId = curentUser.getValueOfId();
        User user = srvPtr_->userCurrent(userId);
        callNormalResponse(std::move(callback), user.toJson());
    }
    catch (BusinessException &e)
    {
        callErrorResponse(std::move(callback), e);
    }
}

void UserController::deleteUsers(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback, User &&reqUser)
{
    try
    {
        if (!srvPtr_->isAdmin(request))
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::NO_DELETE_PERMISSION());
        }

        auto id = (reqUser.getId() != nullptr) ? reqUser.getValueOfId() : -1;
        if (id <= 0)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ID_ILLEGAL());
        }

        bool ret = srvPtr_->userDelete(id);
        callNormalResponse(std::move(callback), ret);
    }
    catch (BusinessException &e)
    {
        callErrorResponse(std::move(callback), e);
    }
}

} } // namespace stibel_init::controller