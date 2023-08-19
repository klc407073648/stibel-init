#ifndef UserControllerTest_H_
#define UserControllerTest_H_

#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "stub_glibc.h"

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
        response.clear();
        //httpTest->reset();
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
        printf("TearDown()");
        response.clear();
        response.clear();
        //httpTest->reset();
    }

    //只执行一次
    static void SetUpTestCase() {
        printf("SetUpTestCase()");
    } 

    //只执行一次
    static void TearDownTestCase() {
        printf("TearDownTestCase()");
    } 

public:
    std::shared_ptr<HttpTest> httpTest;    // 构造http请求
    std::string response; // 正常响应结果
    std::string expect;   // 预期结果
};

#endif /* UserControllerTest */