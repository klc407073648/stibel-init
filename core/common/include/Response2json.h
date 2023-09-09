/**
 * @file Response2json.h
 * @brief 响应转换类，对结果转换为json格式
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_RESPONSE_2_JSON_H__
#define __STIBEL_RESPONSE_2_JSON_H__


namespace stibel_init {
namespace common {

/**
 * @brief Response2json 模板类
 *
 * @tparam T
 */
template <class T>
class Response2json
{
public:
    static Json::Value rep2json(BaseResponse<T> rep)
    {
        Json::Value ret;
        ret["code"] = rep.getCode();
        ret["data"] = static_cast<T>(rep.getData());
        ret["message"] = rep.getMessage();
        ret["description"] = rep.getDescription();
        return ret;
    }
};

/**
 * @brief Response2json 模板类 long类型转换全特化处理
 *
 * @tparam T
 */
template <>
class Response2json<long> 
{
public:
    static Json::Value rep2json(BaseResponse<long> rep)
    {
        Json::Value ret;
        ret["code"] = rep.getCode();
        ret["data"] = static_cast<Json::Int64>(rep.getData());
        ret["message"] = rep.getMessage();
        ret["description"] = rep.getDescription();
        return ret;
    }
};

} } // namespace stibel_init::common

#endif // __STIBEL_RESPONSE_2_JSON_H__