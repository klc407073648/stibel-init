#pragma once

#include<string>

const std::string USER_LOGIN_STATE = "userLoginState"; //session保存登录态

//用户权限
enum USER_TYPE{
    DEFAULT_ROLE = 0, //默认权限
    ADMIN_ROLE = 1 //管理员权限
};