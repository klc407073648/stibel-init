/**
 * @file ErrorCode.h
 * @brief 错误码
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_ERROR_CODE_H__
#define __STIBEL_ERROR_CODE_H__

#include <string>

enum ERROR_CODE
{
    SUCCESS = 0,
    PARAMS_ERROR = 40000,
    NULL_ERROR = 40001,
    NO_LOGIN = 40100,
    NO_AUTH = 40101,
    SYSTEM_ERROR = 50000,
};

#define DEFINE_STATIC_ERROR_CODE(fun_name, error_code, message, description)  ErrorCode ErrorCode::fun_name() \
    { \
        return ErrorCode(ERROR_CODE::error_code, message, description); \
    }

//常成员函数，待处理
class ErrorCode
{

public:
    ErrorCode(int code, const std::string &message, const std::string &description)
        : code_(code), message_(message), description_(description)
    {
    }

    int getCode(){return code_;}

    const std::string &getMessage(){return message_;}

    const std::string &getDescription(){return description_;}

public:
    //定义返回错误码
    static ErrorCode SUCCESS();
    static ErrorCode PARAMS_ERROR();
    static ErrorCode NULL_ERROR();
    static ErrorCode NO_LOGIN();
    static ErrorCode NO_AUTH();
    static ErrorCode SYSTEM_ERROR();

private:
    int code_;                //状态码
    std::string message_;     //状态码信息
    std::string description_; //状态码描述
};

#endif // __STIBEL_ERROR_CODE_H__