#include <iostream>
#include "gtest/gtest.h"
#include "HttpTest.h"
#include "UserControllerTest.h"
#include <Poco/Net/HTTPRequest.h>

using namespace Poco;
using namespace Poco::Net;

/*  用户注册  */

// 非空校验
TEST_F(UserControllerTest, Register_userAccount_Null)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/user/json/req/Given_userAccount_Null_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_userAccount_Null_When_register_Then_return_fail_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Register_userAccount_Null req and resp not same.";
}

// 账号长度校验
TEST_F(UserControllerTest, Register_userAccount_Length_Less_than_4)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/user/json/req/Given_userAccount_Length_Less_than_4_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_userAccount_Length_Less_than_4_When_register_Then_return_fail_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Register_userAccount_Length_Less_than_4 req and resp not same.";
}

// 密码长度校验
TEST_F(UserControllerTest, Register_userPassword_Length_Less_than_8)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json",
                      "../testcase/user/json/req/Given_userPassword_Length_Less_than_8_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_userPassword_Length_Less_than_8_When_register_Then_return_fail_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Register_userPassword_Length_Less_than_8 req and resp not same.";
}

// 账号重复性校验
TEST_F(UserControllerTest, Register_userAccount_unique)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_userAccount_unique_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_userAccount_unique_When_register_Then_return_fail_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Register_userAccount_unique req and resp not same.";
}

// 账号特殊字符校验
TEST_F(UserControllerTest, Register_userAccount_contain_special_charater)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_userAccount_contain_special_charater_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_userAccount_contain_special_charater_When_register_Then_return_fail_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Register_userAccount_contain_special_charater req and resp not same.";
}

// 密码和校验密码相同性校验
TEST_F(UserControllerTest, Register_userPassword_checkPassword_not_same)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_userPassword_checkPassword_not_same_When_register_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_userPassword_checkPassword_not_same_When_register_Then_return_fail_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Register_userPassword_checkPassword_not_same req and resp not same.";
}

// 用户注册,星球编号校验

/*  用户注册  */

/*  用户登录  */

// 登录正常用户
TEST_F(UserControllerTest, Login_correct_user)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/login", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_correct_user_When_login_Then_return_success.json",
                      "../testcase/user/json/resp/Given_correct_user_When_login_Then_return_success_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

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
    std::string temp = "../testcase/user/json/req/Given_correct_array_user_When_login_Then_return_success.json";
    httpTest.readArrayStringFromJson(temp);

    EXPECT_EQ(resp, res) << "Login_correct_user req and resp not same.";

    // 注销，避免影响后续用例
    HttpTest httpTest3(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/logout", HTTPMessage::HTTP_1_1,"application/json",
                      "",
                      "../testcase/user/json/resp/Given_null_When_logout_Then_return_success_resp.json");

    std::string resp3 = httpTest.sendRequest();
    std::string res3 = httpTest.readStringFromJson(httpTest.getRespJsonFile());
	
    EXPECT_EQ(resp3, res3) << "Logout_normal req and resp not same.";
}

// 登录不存在的用户
TEST_F(UserControllerTest, Login_no_exist_user)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/login", HTTPMessage::HTTP_1_1,"application/json",
                      "../testcase/user/json/req/Given_no_exist_user_When_login_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_no_exist_user_When_login_Then_return_fail_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Login_no_exist_user req and resp not same.";
}

/*  用户登录  */

/*  获取当前用户  */

// 登录正常用户,获取当前用户
TEST_F(UserControllerTest, Current_Login_correct_user)
{
    // 先登录
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/login", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_correct_user_When_login_Then_return_success.json",
                      "../testcase/user/json/resp/Given_correct_user_When_login_Then_return_success_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Current_Login_correct_user login req and resp not same.";

    // 再获取当前用户
    HttpTest httpTest2(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_GET, "/api/user/current", HTTPMessage::HTTP_1_1,"application/json", 
                       "",
                       "../testcase/user/json/resp/Given_login_user_When_query_Then_return_success_resp.json");

    std::string resp2 = httpTest2.sendRequest();
    std::string res2 = httpTest2.readStringFromJson(httpTest2.getRespJsonFile());

    EXPECT_EQ(resp2, res2) << "Current_Login_correct_user current req and resp not same.";

    // 注销，避免影响后续用例
    HttpTest httpTest3(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/logout", HTTPMessage::HTTP_1_1,"application/json",
                      "",
                      "../testcase/user/json/resp/Given_null_When_logout_Then_return_success_resp.json");

    std::string resp3 = httpTest.sendRequest();
    std::string res3 = httpTest.readStringFromJson(httpTest.getRespJsonFile());
	
    EXPECT_EQ(resp3, res3) << "Logout_normal req and resp not same.";
}

// 登录不存在的用户
TEST_F(UserControllerTest, Current_Login_no_exist_user)
{
    // 先注销
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/login", HTTPMessage::HTTP_1_1,"application/json", 
                      "../testcase/user/json/req/Given_no_exist_user_When_login_Then_return_fail.json",
                      "../testcase/user/json/resp/Given_no_exist_user_When_login_Then_return_fail_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Current_Login_no_exist_user req and resp not same.";

    // 再获取当前用户
    HttpTest httpTest2(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_GET, "/api/user/current", HTTPMessage::HTTP_1_1,"application/json",
                       "",
                       "../testcase/user/json/resp/Given_login_user_When_query_Then_return_success_resp.json");

    std::string resp2 = httpTest2.sendRequest();
    std::string res2 = httpTest2.readStringFromJson(httpTest2.getRespJsonFile());

    EXPECT_EQ(resp2, res2) << "Current_Login_no_exist_user current req and resp not same.";
}

/*  获取当前用户  */

/*  注销用户  */

// 正常注销
TEST_F(UserControllerTest, Logout_normal)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/logout", HTTPMessage::HTTP_1_1,"application/json",
                      "",
                      "../testcase/user/json/resp/Given_null_When_logout_Then_return_success_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Logout_normal req and resp not same.";
}

/*  注销用户  */