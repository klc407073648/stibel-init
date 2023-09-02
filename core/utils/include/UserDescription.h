/**
 * @file UserDescription.h
 * @brief 描述信息
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_USERDESCRIPTION_H__
#define __STIBEL_USERDESCRIPTION_H__

#include "Description.h"

namespace stibel_init {
namespace utils {

using stibel_init::common::Description;

class UserDescription : public Description
{
public:
    UserDescription(const std::string &zh, const std::string &en, const std::string &lang = "en_US")
        : Description::Description(zh, en, lang), desc_("User Description")
    {
    }

public:
    DEFINE_STATIC_DESCRIPTION(UserDescription, PARA_EMPTY, "参数为空", "Parameter is empty")
    DEFINE_STATIC_DESCRIPTION(UserDescription, REQUEST_EMPTY, "请求为空", "Request is empty")
    DEFINE_STATIC_DESCRIPTION(UserDescription, ACCOUNT_OR_PWD_OR_VERI_PWD_OR_PLANT_CODE_EMPTY, "入参中账号或密码或校验密码或星球编号为空", "The account or password or verification password or planet number is empty")
    DEFINE_STATIC_DESCRIPTION(UserDescription, ACCOUNT_OR_PWD_EMPTY, "入参中账号或密码为空", "The account or password in the participation is empty")

    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_ACCOUNT_OR_PWD_EMPTY, "用户账号或密码为空", "The user account or password is empty")
    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_ACCOUNT_LESS_THAN_4, "用户账号小于4位", "User account is less than 4 digits")
    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_PWD_LESS_THAN_8, "用户密码小于8位", "User password is less than 8 digits")
    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_ACCOUNT_HAS_SPEC_CHARACTER, "用户账号中存在特殊字符", "There are special characters in the user account")
    DEFINE_STATIC_DESCRIPTION(UserDescription, PLANT_CODE_GREATER_THAN_5, "星球编号大于5位", "Planet number greater than 5 digits")
    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_PWD_OR_VERI_PWD_LESS_THAN_8, "用户密码和校验密码小于8位", "User password and verification password are less than 8 digits")
    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_PWD_AND_VERI_PWD_DIFF, "用户密码和校验密码不同", "User password and verification password are different")
    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_ID_ILLEGAL, "用户id不合法", "User ID is illegal")

    DEFINE_STATIC_DESCRIPTION(UserDescription, NO_QUERY_PERMISSION, "非管理员用户，无查询权限", "Non administrator user, no query permission")
    DEFINE_STATIC_DESCRIPTION(UserDescription, NO_DELETE_PERMISSION, "非管理员用户，无删除权限", "Non administrator user, no delete permission")

    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_ACCOUNT_EXIST, "用户账号已存在", "User account already exists")
    DEFINE_STATIC_DESCRIPTION(UserDescription, USER_ACCOUNT_NO_EXIST, "用户不存在", "User does not exist")
    DEFINE_STATIC_DESCRIPTION(UserDescription, INSERT_DATA_FAIL, "插入数据失败", "Insert data failed")
    DEFINE_STATIC_DESCRIPTION(UserDescription, GET_CURRENT_USER_FAIL, "获取当前用户失败", "Failed to obtain the current user")
    DEFINE_STATIC_DESCRIPTION(UserDescription, DELETE_SPEC_USER_FAIL, "删除指定用户失败", "Failed to delete the specified user")

private:
    std::string desc_; // 描述
};

} } // namespace stibel_init::utils

#endif // __STIBEL_USERDESCRIPTION_H__