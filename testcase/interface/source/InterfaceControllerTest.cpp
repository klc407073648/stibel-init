#include <iostream>
#include "gtest/gtest.h"
#include "HttpTest.h"
#include "InterfaceControllerTest.h"
#include <Poco/Net/HTTPRequest.h>

using namespace Poco;
using namespace Poco::Net;

/* 获取后台版本 */
TEST_F(InterfaceControllerTest, BackendVersion_query)
{
    // 先登录
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_GET, "/api/backend/version", HTTPMessage::HTTP_1_1, "application/json",
                      "",
                      "../testcase/json/interface/resp/Given_null_When_query_backend_version_Then_return_success_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "BackendVersion_query login req and resp not same.";
}

/* 获取动漫背景 */
TEST_F(InterfaceControllerTest, Background_Dongman)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/background/get/random", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/json/interface/req/Given_dongman_When_get_background_Then_return_success.json",
                      "../testcase/json/interface/resp/Given_dongman_When_get_background_Then_return_success_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Background_Dongman req and resp not same.";
}

/* 翻译 */
TEST_F(InterfaceControllerTest, Translate_hello)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/fanyi/translate", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/json/interface/req/Given_hello_When_translate_Then_return_success.json",
                      "../testcase/json/interface/resp/Given_hello_When_translate_Then_return_success_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Translate_hello req and resp not same.";
}

/* 查询当前天气 */
TEST_F(InterfaceControllerTest, Weather_current)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/weather/now", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/json/interface/req/Given_city_When_query_now_weather_Then_return_success.json",
                      "../testcase/json/interface/resp/Given_city_When_query_now_weather_Then_return_success_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Weather_current req and resp not same.";
}

/* 查询未来天气 */
TEST_F(InterfaceControllerTest, Weather_future)
{
    HttpTest httpTest(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/weather/future", HTTPMessage::HTTP_1_1, "application/json",
                      "../testcase/json/interface/req/Given_city_When_query_future_weather_Then_return_success.json",
                      "../testcase/json/interface/resp/Given_city_When_query_future_weather_Then_return_success_resp.json");

    std::string resp = httpTest.sendRequest();
    std::string res = httpTest.readStringFromJson(httpTest.getRespJsonFile());

    EXPECT_EQ(resp, res) << "Weather_future req and resp not same.";
}