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

// 错误码宏定义
#define DEFINE_STATIC_DESCRIPTION(class_name, fun_name, zh, en) \
    std::string class_name::fun_name()                          \
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

class UserDescription : public Description
{
public:
    UserDescription(const std::string &zh, const std::string &en, const std::string &lang = "en_US")
        : Description::Description(zh, en, lang)
    {
    }

public:
    static std::string PARA_EMPTY();
    static std::string REQUEST_EMPTY();
    static std::string ACCOUNT_OR_PWD_OR_VERI_PWD_OR_PLANT_CODE_EMPTY();
    static std::string ACCOUNT_OR_PWD_EMPTY();

    static std::string USER_ACCOUNT_OR_PWD_EMPTY();
    static std::string USER_ACCOUNT_LESS_THAN_4();
    static std::string USER_PWD_LESS_THAN_8();
    static std::string USER_ACCOUNT_HAS_SPEC_CHARACTER();
    static std::string PLANT_CODE_GREATER_THAN_5();
    static std::string USER_PWD_OR_VERI_PWD_LESS_THAN_8();
    static std::string USER_PWD_AND_VERI_PWD_DIFF();
    static std::string USER_ID_ILLEGAL();

    static std::string NO_QUERY_PERMISSION();
    static std::string NO_DELETE_PERMISSION();

    static std::string USER_ACCOUNT_EXIST();
    static std::string USER_ACCOUNT_NO_EXIST();
    static std::string INSERT_DATA_FAIL();
    static std::string GET_CURRENT_USER_FAIL();
    static std::string DELETE_SPEC_USER_FAIL();

private:
    std::string zh_;   // 中文描述
    std::string en_;   // 英文描述
    std::string lang_; // 语言类型
};

#endif // __STIBEL_DESCRIPTION_H__