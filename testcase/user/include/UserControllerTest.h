#ifndef UserControllerTest_H_
#define UserControllerTest_H_

#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "stub_glibc.h"
#include <iostream>
#include "HttpTest.h"
#include <Poco/Net/HTTPRequest.h>

using namespace Poco;
using namespace Poco::Net;

class UserControllerTest : public ::testing::Test
{
    // You can remove any or all of the following functions if its body
    // is empty.
protected:
    UserControllerTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~UserControllerTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp()
    {
        printf("SetUp()");
        response.clear();
        expect.clear();
        //httpTest->reset();
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
        printf("TearDown()");
        response.clear();
        expect.clear();
        //httpTest->reset();
    }

    //只执行一次
    static void SetUpTestCase() {
        printf("SetUpTestCase()");
        // httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/register", HTTPMessage::HTTP_1_1, "application/json",
        //                                   "../testcase/json/user/req/register/Given_normal_user_When_register_Then_success.json",
        //                                   "");
        // httpTest->sendRequest();
    } 

    //只执行一次
    static void TearDownTestCase() {
        //TODO 看看能不能查询对应账号，获取ID，然后删除
        printf("TearDownTestCase()");
        // httpTest = std::make_shared<HttpTest>(BACKEND_IP, BACKEND_PORT, HTTPRequest::HTTP_POST, "/api/user/delete", HTTPMessage::HTTP_1_1, "application/json",
        //                                   "../testcase/json/user/req/delete/Given_delete_user_id_When_delete_Then_success.json",
        //                                   "");
        // httpTest->sendRequest();
    } 

public:
    static std::shared_ptr<HttpTest> httpTest;    // 构造http请求
    std::string response; // 正常响应结果
    std::string expect;   // 预期结果
};

#endif /* UserControllerTest */