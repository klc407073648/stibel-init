/**
 * @file InterfaceDescription.h
 * @brief 描述信息
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_INTERFACEDESCRIPTION_H__
#define __STIBEL_INTERFACEDESCRIPTION_H__

#include "Description.h"

namespace stibel_init {
namespace utils {

using stibel_init::common::Description;

class InterfaceDescription : public Description
{
public:
    InterfaceDescription(const std::string &zh, const std::string &en, const std::string &lang = "en_US")
        : Description::Description(zh, en, lang), desc_("Interface Description")
    {
    }

public:
    DEFINE_STATIC_DESCRIPTION(InterfaceDescription, NO_EXIST, "接口不存在", "Interface does not exist")
    DEFINE_STATIC_DESCRIPTION(InterfaceDescription, PARSE_URL_ERROR, "解析接口url信息错误", "Parsing interface URL information error")
    DEFINE_STATIC_DESCRIPTION(InterfaceDescription, STATUS_ERROR, "接口状态异常", "Interface status is abnormal")
    DEFINE_STATIC_DESCRIPTION(InterfaceDescription, GET_INFO_ERROR, "获取接口表信息失败", "Failed to obtain interface table information")

private:
    std::string desc_; // 描述
};

} } // namespace stibel_init::utils

#endif // __STIBEL_INTERFACEDESCRIPTION_H__