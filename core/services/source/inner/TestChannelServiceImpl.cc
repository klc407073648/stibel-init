#include "inner/impl/TestChannelServiceImpl.h"
#include "BusinessException.h"
#include <stdio.h>
#include "FunStat.h"

using namespace drogon;
using namespace stibel_init::exception;
using namespace stibel_init::common;

namespace stibel_init {
namespace service {

TestChannelServiceImpl::TestChannelServiceImpl()
{
    LOG_INFO << "TestChannelServiceImpl constructor!";
}

TestChannelServiceImpl::~TestChannelServiceImpl()
{
    LOG_INFO << "TestChannelServiceImpl destructor!";
}

std::string TestChannelServiceImpl::testChannel(const HttpRequestPtr &request)
{
    
    try
    {
        std::string script = ((*(request->getJsonObject()))["script"]).asString();
		
		printf("testChannel");
		FunStat::getInstance()->show();
		/*
        if( script == "show_fun_stat")
        {
            std::string fun0 ="index0";
            std::string fun1 ="index1";
            std::string fun2 ="index2";
            std::string fun3 ="index3";
            std::string fun4 ="index4";
            std::string fun5 ="index5";
            std::string fun6 ="index6";
            std::string fun7 ="index7";

            printf("Function Stat %10s %10s %10s %10s %10s %10s %10s %10s\n", \
            fun0.c_str(),fun1.c_str(),fun2.c_str(),fun3.c_str(),
            fun4.c_str(),fun5.c_str(),fun6.c_str(),fun7.c_str() ); 
            printf("UserController_userRegister %10d %10d %10d %10d %10d %10d %10d %10d\n",  \
            UserController_userRegister[0],UserController_userRegister[1],UserController_userRegister[2],UserController_userRegister[3], \
            UserController_userRegister[4],UserController_userRegister[5],UserController_userRegister[6],UserController_userRegister[7]); 
        }
		*/
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    auto client = HttpClient::newHttpClient("127.0.0.1", 8082);
    auto req = HttpRequest::newHttpRequest();
    req->setMethod(drogon::Post);
    req->setPath("/api/user/register");
    req->setBody("{\"userAccount\":\"111\",\"userPassword\":\"222\",\"checkPassword\":\"333\",\"planetCode\":\"4444\"}");
    std::pair<ReqResult, HttpResponsePtr> resp = client->sendRequest(req);

    /*
    client->sendRequest(req,[](ReqResult r, const HttpResponsePtr &resp) {
                            //REQUIRE(r == ReqResult::Ok);
                            //REQUIRE(resp->getBody().length() == 44618UL);
                            LOG_INFO << "[syncSendRequest] respBody:" << resp->body();
                        });
    */

    // 成功
    /*
    auto client = HttpClient::newHttpClient("https://api.btstu.cn");
    auto req = HttpRequest::newHttpRequest();
    req->setMethod(drogon::Get);
    req->setPath("/sjbz/api.php");
    req->setParameter("lx", "dongman");
    req->setParameter("format", "json");

    //'https://api.btstu.cn/sjbz/api.php', 'Get', '{\"lx\":\"dongman\",\"format\":\"json\"}'

    std::pair<ReqResult, HttpResponsePtr> resp = client->sendRequest(req);
    std::string respBody = static_cast<std::string>((resp.second)->body());

    LOG_INFO << "[syncSendRequest] respBody:" << respBody;
    */

    return "";
}

// std::string TestChannelServiceImpl::testChannel(const HttpRequestPtr &request)
// {

//     LOG_INFO << "[syncSendRequest] testChannel in:";

//     auto client = HttpClient::newHttpClient("127.0.0.1", 8082);
//     auto req = HttpRequest::newHttpRequest();
//     req->setMethod(drogon::Post);
//     req->setPath("/api/user/register");
//     req->setBody("{\"userAccount\":\"111\",\"userPassword\":\"222\",\"checkPassword\":\"333\",\"planetCode\":\"4444\"}");
//     std::pair<ReqResult, HttpResponsePtr> resp = client->sendRequest(req);

//     /*
//     client->sendRequest(req,[](ReqResult r, const HttpResponsePtr &resp) {
//                             //REQUIRE(r == ReqResult::Ok);
//                             //REQUIRE(resp->getBody().length() == 44618UL);
//                             LOG_INFO << "[syncSendRequest] respBody:" << resp->body();
//                         });
//     */

//     // 成功
//     /*
//     auto client = HttpClient::newHttpClient("https://api.btstu.cn");
//     auto req = HttpRequest::newHttpRequest();
//     req->setMethod(drogon::Get);
//     req->setPath("/sjbz/api.php");
//     req->setParameter("lx", "dongman");
//     req->setParameter("format", "json");

//     //'https://api.btstu.cn/sjbz/api.php', 'Get', '{\"lx\":\"dongman\",\"format\":\"json\"}'

//     std::pair<ReqResult, HttpResponsePtr> resp = client->sendRequest(req);
//     std::string respBody = static_cast<std::string>((resp.second)->body());

//     LOG_INFO << "[syncSendRequest] respBody:" << respBody;
//     */

//     return "";
// }

} } // namespace stibel_init::service
