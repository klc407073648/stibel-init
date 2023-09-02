/**
 * @file BaseResponse.h
 * @brief 基础响应类
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_BASERESPONSE_H__
#define __STIBEL_BASERESPONSE_H__

#include "ErrorCode.h"
#include <string>

namespace stibel_init {
namespace common {

using stibel_init::exception::ErrorCode;

template <class T>
class BaseResponse
{
public:
    /**
     * @brief 构造函数: 基于响应码、数据、信息和描述
     */
    BaseResponse(int code, T data, const std::string &message, const std::string &description)
        : code_(code), data_(data), message_(message), description_(description)
    {
    }

    /**
     * @brief 构造函数: 基于响应码、数据
     */
    BaseResponse(int code, T data)
        : code_(code), data_(data), message_(""), description_("")
    {
    }

    /**
     * @brief 构造函数: 基于响应码、数据、信息
     */
    BaseResponse(int code, T data, const std::string &message)
        : code_(code), data_(data), message_(message), description_("")
    {
    }

    /**
     * @brief 构造函数: 基于错误码返回对应的响应内容
     */
    BaseResponse(ErrorCode errorCode)
        : code_(errorCode.getCode()), data_(NULL), message_(errorCode.getMessage()), description_(errorCode.getDescription())
    {
    }

public:
    int getCode() { return code_; }
    const T &getData() { return data_; }
    const std::string &getMessage() { return message_; }
    const std::string &getDescription() { return description_; }

private:
    int code_;                // 响应码
    T data_;                  // 数据
    std::string message_;     // 信息
    std::string description_; // 描述
};

} }// namespace stibel_init::common

#endif // __STIBEL_BASERESPONSE_H__