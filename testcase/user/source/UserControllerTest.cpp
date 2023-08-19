#include <iostream>
#include "HttpTest.h"
#include "UserControllerTest.h"
#include <Poco/Net/HTTPRequest.h>

using namespace Poco;
using namespace Poco::Net;

/*  用户注册  */

/*
Given: 入参校验 userAccount/userPassword/checkPassword 为空
When: 用户注册
Then: 报错 入参中账号或密码或校验密码或星球编号为空
*/
TEST_F(UserControllerTest, Given_userAccount_Or_userPassword_Or_checkPassword_Null_When_Register_Then_fail)
{
    //userAccount 为空
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/user/json/req/register/Given_userAccount_Null_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_Input_Exist_Null_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_userAccount_Null req and resp not same.";

    //userPassword为空
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/user/json/req/register/Given_userPassword_Null_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_Input_Exist_Null_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_userPassword_Null req and resp not same.";


    //checkPassword为空
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/user/json/req/register/Given_checkPassword_Null_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_Input_Exist_Null_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_checkPassword_Null req and resp not same.";
}

// 用户的账号、密码、校验密码长度校验
/*
账号长度
Given: userAccount 填写为 ad 
When: 用户注册
Then: 报错 账号长度应该不小于 4 位
*/
TEST_F(UserControllerTest, Given_userAccount_is_ad_When_Register_Then_check_fail)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/user/json/req/register/Given_userAccount_Length_Less_than_4_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_userAccount_Length_Less_than_4_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_userAccount_Length_Less_than_4 req and resp not same.";
}

/*
密码长度校验
Given: userPassword 填写为 1234567
When: 用户注册
Then: 报错 密码应该不小于8 位
*/
TEST_F(UserControllerTest, Given_userPassword_is_1234567_When_Register_Then_check_fail)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json",
                      "../testcase/user/json/req/register/Given_userPassword_Length_Less_than_8_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_password_Length_Less_than_8_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_userPassword_Length_Less_than_8 req and resp not same.";
}

/*
校验密码长度校验
Given: checkPassword 填写为 1234567
When: 用户注册
Then: 报错 校验密码应该不小于8 位
*/
TEST_F(UserControllerTest, Given_checkPassword_is_1234567_When_Register_Then_check_fail)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json",
                      "../testcase/user/json/req/register/Given_checkPassword_Length_Less_than_8_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_password_Length_Less_than_8_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_checkPassword_Length_Less_than_8 req and resp not same.";
}

/*
账号特殊字符校验
Given: userAccount 填写为 admin@@!!
When: 用户注册
Then: 报错 账号不应该包含特殊字符
*/
TEST_F(UserControllerTest, Given_userAccount_has_special_charater_When_Register_Then_check_fail)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/register/Given_userAccount_contain_special_charater_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_userAccount_contain_special_charater_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_userAccount_contain_special_charater req and resp not same.";
}

/*
密码和校验密码相同性校验
Given: userPassword 为12345678, checkPassword 为12345679
When: 用户注册
Then: 报错 密码和校验密码应该相同
*/
TEST_F(UserControllerTest, Given_userPassword_checkPassword_not_same_When_Register_Then_check_fail)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/register/Given_userPassword_checkPassword_not_same_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_userPassword_checkPassword_not_same_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_userPassword_checkPassword_not_same req and resp not same.";
}

// 账号重复性校验
TEST_F(UserControllerTest, DISABLED_Register_userAccount_unique)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/register/Given_userAccount_unique_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/register/Given_userAccount_unique_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_userAccount_unique req and resp not same.";
}

// 用户注册,星球编号校验

TEST_F(UserControllerTest, DISABLED_Register_plant_code_greater_5)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_userPassword_checkPassword_not_same_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_userPassword_checkPassword_not_same_When_register_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Register_userPassword_checkPassword_not_same req and resp not same.";
}

/*  用户注册  */

/*  用户登录  */

// 登录正常用户
TEST_F(UserControllerTest, Given_correct_user_When_login_Then_success)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/login", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/login/Given_correct_user_When_login_Then_return_success.json",
                      "../testcase/user/json/resp/login/Given_correct_user_When_login_Then_return_success_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "correct_user login fail.";

    // test readArrayStringFromJson
    /*
    [readArrayStringFromJson] key: checkPasswordvalue: 12345678
    [readArrayStringFromJson] key: userAccountvalue: testuser
    [readArrayStringFromJson] key: userPasswordvalue: 12345678
    [readArrayStringFromJson] key: checkPasswordvalue: 12345678333
    [readArrayStringFromJson] key: userAccountvalue: testuser222
    [readArrayStringFromJson] key: userPasswordvalue: 12345678333
    [readArrayStringFromJson] file: /home/stibel/cpp-backend/testcase/user/json/login../testcase/user/json/req/Given_correct_array_user_When_login_Then_return_success.json,
    res:[{"checkPassword":"12345678","userAccount":"testuser","userPassword":"12345678"},
    {"checkPassword":"12345678333","userAccount":"testuser222","userPassword":"12345678333"}]
    */

   /*
    std::string temp = "../testcase/user/json/req/Given_correct_array_user_When_login_Then_return_success.json";
    httpTest->readArrayStringFromJson(temp);

    EXPECT_EQ(response, expect) << "Login_correct_user req and resp not same.";

    // 注销，避免影响后续用例
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/logout", HTTPMessage::HTTP_1_1,"application/json",
                      "",
                      "../testcase/user/json/resp/Given_null_When_logout_Then_return_success_resp.json");

    std::string resp3 = httpTest->sendRequest();
    std::string res3 = httpTest->readStringFromJson(httpTest->getRespJsonFile());
	
    EXPECT_EQ(resp3, res3) << "Logout_normal req and resp not same.";
    */
}

// 登录不存在的用户
TEST_F(UserControllerTest, Given_no_exist_user_When_login_Then_fail)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/login", HTTPMessage::HTTP_1_1,"application/json",
                      "../testcase/user/json/req/login/Given_no_exist_user_When_login_Then_return_fail.json",
                      "../testcase/user/json/resp/login/Given_no_exist_user_When_login_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Login_no_exist_user req and resp not same.";
}

/*  用户登录  */

/*  获取当前用户  */

// 登录正常用户,获取当前用户
TEST_F(UserControllerTest, DISABLED_Current_Login_correct_user)
{
    // 先登录
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/login", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_correct_user_When_login_Then_return_success.json",
                      "../testcase/user/json/resp/Given_correct_user_When_login_Then_return_success_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Current_Login_correct_user login req and resp not same.";

    // 再获取当前用户
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_GET, "/api/user/current", HTTPMessage::HTTP_1_1,"application/json", 
                       "",
                       "../testcase/user/json/resp/Given_login_user_When_query_Then_return_success_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Current_Login_correct_user current req and resp not same.";

    // 注销，避免影响后续用例
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/logout", HTTPMessage::HTTP_1_1,"application/json",
                      "",
                      "../testcase/user/json/resp/Given_null_When_logout_Then_return_success_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());
	
    EXPECT_EQ(response, expect) << "Logout_normal req and resp not same.";
}

// 登录不存在的用户
TEST_F(UserControllerTest, DISABLED_Current_Login_no_exist_user)
{
    // 先注销
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/login", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_no_exist_user_When_login_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_no_exist_user_When_login_Then_return_fail_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Current_Login_no_exist_user req and resp not same.";

    // 再获取当前用户
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_GET, "/api/user/current", HTTPMessage::HTTP_1_1,"application/json",
                       "",
                       "../testcase/user/json/resp/Given_login_user_When_query_Then_return_success_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Current_Login_no_exist_user current req and resp not same.";
}

/*  获取当前用户  */

/*  注销用户  */

// 正常注销
TEST_F(UserControllerTest, DISABLED_Logout_normal)
{
    httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/logout", HTTPMessage::HTTP_1_1,"application/json",
                      "",
                      "../testcase/user/json/resp/Given_null_When_logout_Then_return_success_resp.json");

    response = httpTest->sendRequest();
    expect = httpTest->readStringFromJson(httpTest->getRespJsonFile());

    EXPECT_EQ(response, expect) << "Logout_normal req and resp not same.";
}

/*  注销用户  */