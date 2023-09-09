/**
 * @file HttpResponseUtils.h
 * @brief Http响应工具类，封装正常和异常的返回结果
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_HTTPRESPONSE_UTILS_H__
#define __STIBEL_HTTPRESPONSE_UTILS_H__

#include "ResultUtils.h"
#include "Response2json.h"
#include "BusinessException.h"

namespace stibel_init {
namespace utils {

using namespace stibel_init::exception;
using namespace stibel_init::common;

// template <class T>
// class HttpResponseUtils
// {
// public:
static void callErrorResponse(std::function<void(const HttpResponsePtr &)> &&callback, BusinessException &e)
{
    auto base = ResultUtils<long>::error(e.getCode(), e.getMessage(), e.getDescription());
    auto json = Response2json<long>::rep2json(base);

    LOG_ERROR << "[callErrorResponse] callFunName:" << __builtin_FUNCTION() << ", error response:" << json.toStyledString();
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

template <class T>
static void callNormalResponse(std::function<void(const HttpResponsePtr &)> &&callback, T value)
{
    auto base = ResultUtils<decltype(value)>::success(value);
    auto json = Response2json<decltype(value)>::rep2json(base);

    LOG_INFO << "[callNormalResponse] callFunName:" << __builtin_FUNCTION() << ", normal response:" << json.toStyledString();
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
// };

} } // namespace stibel_init::utils

#endif // __STIBEL_HTTPRESPONSE_UTILS_H__