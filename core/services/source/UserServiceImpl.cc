#include "impl/UserServiceImpl.h"
#include "UserConstant.h"
#include "ErrorCode.h"
#include "Description.h"
#include "BusinessException.h"
#include <trantor/utils/Utilities.h>
#include <regex>

using namespace drogon;
using namespace stibel_init;
using namespace drogon::internal;

UserServiceImpl::UserServiceImpl()
{
    LOG_INFO << "UserServiceImpl constructor!";
}

UserServiceImpl::~UserServiceImpl()
{
    LOG_INFO << "UserServiceImpl destructor!";
}

long UserServiceImpl::userRegister(const std::string &userAccount, const std::string &userPassword, const std::string &checkPassword, const std::string &planetCode)
{
    LOG_INFO << "userAccount:" << userAccount;
    LOG_INFO << "userPassword:" << userPassword;
    LOG_INFO << "checkPassword:" << checkPassword;
    LOG_INFO << "planetCode:" << planetCode;

    /*
    校验用户的账号、密码、校验密码，是否符合要求
    1. 非空
    2. 账号长度不小于4位
    3. 密码，校验密码不小于8位
    4. 账号不能重复
    5. 账号不包含特殊字符
    6. 密码和校验密码相同
    */

    try
    {
        if (userAccount.size() == 0 || userPassword.size() == 0 || checkPassword.size() == 0 || checkPassword.size() == 0)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::PARA_EMPTY());
        }

        if (userAccount.length() < 4)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ACCOUNT_LESS_THAN_4());
        }

        if (userPassword.length() < 8 || checkPassword.length() < 8)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_PWD_OR_VERI_PWD_LESS_THAN_8());
        }

        if (planetCode.length() > 5)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::PLANT_CODE_GREATER_THAN_5());
        }

        // 特殊字符校验
        if (checkSpecialCharacter(userAccount))
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ACCOUNT_HAS_SPEC_CHARACTER());
        }

        // 密码和校验密码相同
        if (userPassword != checkPassword)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_PWD_AND_VERI_PWD_DIFF());
        }

        // 用户不能重复
        auto ret = userMapper.findBy(Criteria(User::Cols::_userAccount, CompareOperator::EQ, userAccount));

        LOG_INFO << "ret.size():" << ret.size();

        if (!ret.empty())
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ACCOUNT_EXIST());
        }

        // 星球账号不能重复
        /*
        ret = userMapper.findBy(Criteria(User::Cols::_planetCode, CompareOperator::EQ, planetCode));
        if (!ret.empty())
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), "星球账号已存在");
        }
        */

        // 2.加密
        std::string encryptPassword = encryptPwd(userPassword);
        LOG_INFO << "encryptPassword:" << encryptPassword;

        // 3.插入数据
        User user;
        user.setIphone("");
        user.setEmail("");
        user.setUserstatus(0);
        user.setUseraccount(userAccount);
        user.setUserpassword(encryptPassword);
        user.setPlanetcode(planetCode);
        userMapper.insert(user);
		
		return *(user.getId());
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(),  UserDescription::INSERT_DATA_FAIL());
    }
}
User UserServiceImpl::userLogin(const std::string &userAccount, const std::string &userPassword, const HttpRequestPtr &request)
{
    LOG_INFO << "userAccount:" << userAccount;
    LOG_INFO << "userPassword:" << userPassword;

    // 1. 校验
    if (userAccount.size() == 0 || userPassword.size() == 0)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ACCOUNT_OR_PWD_EMPTY());
    }

    if (userAccount.length() < 4)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ACCOUNT_LESS_THAN_4());
    }

    if (userPassword.length() < 8)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_PWD_LESS_THAN_8());
    }

    // 特殊字符校验
    if (checkSpecialCharacter(userAccount))
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ACCOUNT_HAS_SPEC_CHARACTER());
    }

    // 2.加密
    std::string encryptPassword = encryptPwd(userPassword);
    LOG_INFO << "encryptPassword:" << encryptPassword;

    // 查询用户是否存在
    try
    {
        auto user = userMapper.findOne(Criteria(User::Cols::_userAccount, CompareOperator::EQ, userAccount) &&
                                       Criteria(User::Cols::_userPassword, CompareOperator::EQ, encryptPassword));

        // 3. 用户脱密
        User safetyUser = getSafetyUser(user);

        // 4.记录用户登录态
        request->getSession()->insert(USER_LOGIN_STATE, safetyUser);

        return safetyUser;
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::USER_ACCOUNT_NO_EXIST());
    }
}

std::vector<User> UserServiceImpl::userSearch(const std::string &username)
{
    std::vector<User> userList;

    if (username == "")
    {
        userList = userMapper.findAll();
    }
    else
    {
        userList = userMapper.findBy(Criteria(User::Cols::_username, CompareOperator::EQ, username));
    }
    std::vector<User> safetyUserList;

    for (auto user : userList)
    {
        safetyUserList.push_back(getSafetyUser(user));
    }
    return safetyUserList;
}

User UserServiceImpl::userCurrent(long id)
{
    User safetyUser;

    try
    {
        auto user = userMapper.findOne(Criteria(User::Cols::_id, CompareOperator::EQ, id));

        // 3. 用户脱密
        safetyUser = getSafetyUser(user);
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::GET_CURRENT_USER_FAIL());
    }

    return safetyUser;
}

bool UserServiceImpl::userDelete(long id)
{
    try
    {
        long ret = userMapper.deleteBy(Criteria(User::Cols::_id, CompareOperator::EQ, id));

        if (ret != 1)
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::DELETE_SPEC_USER_FAIL());
        }
        return true;
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), UserDescription::DELETE_SPEC_USER_FAIL());
    }
}

long UserServiceImpl::userLogout(const HttpRequestPtr &request)
{
    LOG_INFO << "UserServiceImpl::userLogout in";
    request->getSession()->erase(USER_LOGIN_STATE);
    return 1;
}

User UserServiceImpl::getSafetyUser(User originUser)
{
    User safetyUser;
    safetyUser.setId(originUser.getValueOfId());
    safetyUser.setUsername(originUser.getValueOfUsername());
    safetyUser.setUseraccount(originUser.getValueOfUseraccount());
    safetyUser.setAvatarurl(originUser.getValueOfAvatarurl());
    safetyUser.setGender(originUser.getValueOfGender());
    safetyUser.setIphone(originUser.getValueOfIphone());
    safetyUser.setEmail(originUser.getValueOfEmail());
    safetyUser.setUserrole(originUser.getValueOfUserrole());
    safetyUser.setUserstatus(originUser.getValueOfUserstatus());
    safetyUser.setCreatetime(originUser.getValueOfCreatetime());
    safetyUser.setPlanetcode(originUser.getValueOfPlanetcode());
    // safetyUser.setTags(originUser.getValueOfTags());

    return safetyUser;
}

bool UserServiceImpl::checkSpecialCharacter(const std::string &str)
{
    // 特殊字符校验
    std::regex vaildPattern("[~!/@#$%^&*()\\-_=+\\|\\[{}\\];:\'\",<.>/?]+");
    std::smatch match;

    if (regex_search(str, match, vaildPattern))
    {
        return true;
    }

    return false;
}

std::string UserServiceImpl::encryptPwd(const std::string &str)
{
    return utils::getMd5(str);
}

std::vector<User> UserServiceImpl::searchUsersByTags(std::vector<std::string> tagNameList)
{
    std::vector<User> vec;//暂未实现
    return vec;
}

bool UserServiceImpl::isAdmin(const HttpRequestPtr &request)
{
	LOG_INFO << "UserServiceImpl::isAdmin in";
	
    bool isFind = request->getSession()->find(USER_LOGIN_STATE);

	LOG_INFO << "UserServiceImpl::isAdmin isFind:"<<isFind;
	std::string sessionId = request->getSession()->sessionId();
	LOG_INFO << "UserServiceImpl::isAdmin sessionId:"<<sessionId;
	
    if (isFind)
    {
        User user = request->getSession()->get<User>(USER_LOGIN_STATE);
		LOG_INFO << "UserServiceImpl::isAdmin toJson:"<<user.toJson().toStyledString();
        if (user.getValueOfUserrole() == ADMIN_ROLE)
        {
            return true;
        }
    }

    return false;
}