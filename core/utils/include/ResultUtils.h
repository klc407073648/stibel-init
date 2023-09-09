/**
 * @file ResultUtils.h
 * @brief 结果工具类，对基础响应进行封装
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_RESULT_UTILS_H__
#define __STIBEL_RESULT_UTILS_H__

#include "BaseResponse.h"

namespace stibel_init {
namespace utils {

using stibel_init::common::BaseResponse;
using stibel_init::exception::ErrorCode;

template <class T>
class ResultUtils
{
public:
    /**
     * 成功
     * @param data
     * @return
     * @param <T>
     */
    static BaseResponse<T> success(T data)
    {
        return BaseResponse<T>(0, data, "ok");
    }

    /**
     * 失败
     * @param errorCode
     * @return
     */
    static BaseResponse<T> error(ErrorCode errorCode)
    {
        return BaseResponse<T>(errorCode);
    }

    /**
     * 失败
     * @param errorCode
     * @return
     */
    static BaseResponse<T> error(ErrorCode errorCode, const std::string &message, const std::string &description)
    {
        return BaseResponse<T>(errorCode.getCode(), NULL, message, description);
    }

    /**
     * 失败
     * @param errorCode
     * @return
     */
    static BaseResponse<T> error(int errorCode, const std::string &message, const std::string &description)
    {
        return BaseResponse<T>(errorCode, NULL, message, description);
    }

    /**
     * 失败
     * @param errorCode
     * @return
     */
    static BaseResponse<T> error(ErrorCode errorCode, const std::string &description)
    {
        return BaseResponse<T>(errorCode.getCode(), NULL, errorCode.getMessage(), description);
    }
};

} } // namespace stibel_init::utils

#endif // __STIBEL_RESULT_UTILS_H__
