/**
 * @file Description.h
 * @brief 描述信息
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_DESCRIPTION_H__
#define __STIBEL_DESCRIPTION_H__

#include <string>

namespace stibel_init {
namespace common {

// 获取描述信息宏定义
#define DEFINE_STATIC_DESCRIPTION(class_name, fun_name, zh, en) \
    static std::string class_name::fun_name()                   \
    {                                                           \
        return class_name(zh, en).getMessage();                 \
    }

class Description
{
public:
    Description(const std::string &zh, const std::string &en, const std::string &lang = "en_US")
        : zh_(zh), en_(en), lang_(lang)
    {
    }

public:
    const std::string &getMessage() { return lang_ == "en_US" ? en_ : zh_; }
    const std::string &getLang() { return lang_; }

private:
    std::string zh_;   // 中文描述
    std::string en_;   // 英文描述
    std::string lang_; // 语言类型
};

} } // namespace stibel_init::common

#endif // __STIBEL_DESCRIPTION_H__