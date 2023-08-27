/**
 * @file BusinessException.h
 * @brief 业务异常类
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_BUSINESS_EXCEPTION_H__
#define __STIBEL_BUSINESS_EXCEPTION_H__

#include "ErrorCode.h"
#include <exception>
#include <functional>

namespace stibel_init {
namespace exception {

class BusinessException : public std::exception
{
public:
    BusinessException(const std::string &message, int code, const std::string &description)
        : message_(message), code_(code), description_(description)
    {
    }

    BusinessException(ErrorCode errorCode)
        : message_(errorCode.getMessage()), code_(errorCode.getCode()), description_(errorCode.getDescription())
    {
    }

    BusinessException(ErrorCode errorCode, const std::string &description)
        : message_(errorCode.getMessage()), code_(errorCode.getCode()), description_(description)
    {
    }
    
    BusinessException() = delete;

public:
    int getCode() { return code_; }
    const std::string &getDescription() { return description_; }
    const std::string &getMessage() { return message_; }
    const char *what() const noexcept override { return message_.data(); }

private:
    int code_;
    std::string message_;
    std::string description_;
};

} } // namespace stibel_init::exception

#endif // __STIBEL_BUSINESS_EXCEPTION_H__
