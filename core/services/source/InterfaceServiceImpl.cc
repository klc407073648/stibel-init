#include "impl/InterfaceServiceImpl.h"
#include "BusinessException.h"
#include "InterfaceDescription.h"

using namespace drogon;
using namespace drogon::internal;
using namespace stibel_init::exception;
using stibel_init::utils::InterfaceDescription;

namespace stibel_init {
namespace service {

InterfaceServiceImpl::InterfaceServiceImpl() : cacheServicePtr_(new CacheServiceImpl())
{
    LOG_INFO << "InterfaceServiceImpl constructor!";
    initHttpMethodMap();
}

InterfaceServiceImpl::~InterfaceServiceImpl()
{
    LOG_INFO << "InterfaceServiceImpl destructor!";
}

void InterfaceServiceImpl::initHttpMethodMap()
{
    httpMethodMap["Get"] = drogon::Get;
    httpMethodMap["Post"] = drogon::Post;
    httpMethodMap["Head"] = drogon::Head;
    httpMethodMap["Put"] = drogon::Put;
    httpMethodMap["Delete"] = drogon::Delete;
    httpMethodMap["Options"] = drogon::Options;
    httpMethodMap["Patch"] = drogon::Patch;
    httpMethodMap["Invalid"] = drogon::Invalid;
}

std::string InterfaceServiceImpl::getBackground(const HttpRequestPtr &request)
{
    std::string funName = __FUNCTION__;
    std::string imgurl("");

    try
    {
        // 1. 根据接口名称做校验，如果通过则返回对应接口内容
        Interface interface = checkInterface(funName);

        // 2. 获取接口中的请求参数
        std::string lx = ((*(request->getJsonObject()))["lx"]).asString();
        const std::string BACKGROUND_FORMAT = "json"; 

        std::string host("");
        std::string path("");
        getHostAndPathFromUrl(interface.getValueOfUrl(), host, path);

        auto client = HttpClient::newHttpClient(host);
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(httpMethodMap[interface.getValueOfMethod()]);
        req->setPath(path);
        req->setParameter("lx", lx);
        req->setParameter("format", BACKGROUND_FORMAT);

        imgurl = syncSendRequest(req, client, "imgurl");
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), funName + InterfaceDescription::NO_EXIST());
    }
    return imgurl;
}

std::string InterfaceServiceImpl::getTranslate(const HttpRequestPtr &request)
{
    std::string funName = __FUNCTION__;
    std::string translateRes("");

    try
    {
        // 1. 根据接口名称做校验，如果通过则返回对应接口内容
        Interface interface = checkInterface(funName);

        // 2. 获取接口中的请求参数
        auto interfaceJson = interface.toJson();
        std::string appid = interfaceJson["requestParams"]["appid"].asString();
        std::string key = interfaceJson["requestParams"]["key"].asString();

        LOG_INFO << "appid:[" << appid << "], key:[" <<key << "]";

        std::string host("");
        std::string path("");
        getHostAndPathFromUrl(interface.getValueOfUrl(), host, path);
        auto client = HttpClient::newHttpClient(host);

        // 3. 百度云翻译api方法
        auto json = *(request->getJsonObject()); // 从请求参数中获取keywords,from,to内容

        std::string keywords = json.isMember("keywords") ? json["keywords"].asString() : "";
        std::string from = json.isMember("config") ? ((json["config"]).isMember("from") ? json["config"]["from"].asString() : "") : "";
        std::string to = json.isMember("config") ? ((json["config"]).isMember("to") ? json["config"]["to"].asString() : "") : "";

        LOG_INFO << "[getTranslate] keywords:" << keywords << ", from:" << from << ", to:" << to;
        std::string salt = std::to_string(trantor::Date::now().microSecondsSinceEpoch()).substr(0, 10); // 随机数
        std::string sign = drogon::utils::getMd5(appid + keywords + salt + key);
        toLower(sign);

        auto req = HttpRequest::newHttpRequest();
        req->setMethod(httpMethodMap[interface.getValueOfMethod()]);
        req->setPath(path);
        req->setParameter("q", keywords);  // 请求翻译query	UTF-8编码
        req->setParameter("from", from);   // 翻译源语言	语言列表(可设置为auto)
        req->setParameter("to", to);       // 译文语言	语言列表(不可设置为auto)
        req->setParameter("appid", appid); // APP ID	可在管理控制台查看
        req->setParameter("salt", salt);   // appid+q+salt+密钥 的MD5值
        req->setParameter("sign", sign);   // 要转小写才行
        translateRes = syncSendRequest(req, client);
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), funName + InterfaceDescription::NO_EXIST());
    }

    return translateRes;
}

std::string InterfaceServiceImpl::getBackendVersion(const HttpRequestPtr &request)
{
    std::string funName = __FUNCTION__;
    std::string version("");

    try
    {
        // 1. 根据接口名称做校验，如果通过则返回对应接口内容
        Interface interface = checkInterface(funName);

        // 2. 返回后端版本号,待存储到数据库
        version = "drogon:V1.1.0";
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), funName + InterfaceDescription::NO_EXIST());
    }

    return version;
}

std::string InterfaceServiceImpl::getCurrentWeather(const HttpRequestPtr &request)
{
    std::string funName = __FUNCTION__;
    std::string weatherInfo("");
    try
    {
        // 1. 根据接口名称做校验，如果通过则返回对应接口内容
        Interface interface = checkInterface(funName);

        // 2. 获取接口中的请求参数
		std::string weather_api_key = (interface.toJson())["requestParams"]["key"].asString();

        std::string host("");
        std::string path("");
        getHostAndPathFromUrl(interface.getValueOfUrl(), host, path);

        // 3. 填写对应请求内容，发送请求
        auto client = HttpClient::newHttpClient(host);
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(httpMethodMap[interface.getValueOfMethod()]);
        req->setPath(path);

        auto json = *(request->getJsonObject());
        std::string city = json.isMember("city") ? json["city"].asString() : "";

        // 高德天气API
        req->setParameter("key", weather_api_key); // 请求服务权限标识
        req->setParameter("city", city);           // 城市编码
        req->setParameter("extensions", "base");   // 气象类型 base:返回实况天气,all:返回预报天气
        req->setParameter("output", "JSON");       // 返回格式:可选值：JSON,XML ,默认JSON

        weatherInfo = syncSendRequest(req, client);
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), funName + InterfaceDescription::NO_EXIST());
    }

    return weatherInfo;
}

std::string InterfaceServiceImpl::getFutureWeather(const HttpRequestPtr &request)
{
    std::string funName = __FUNCTION__;
    std::string weatherInfo("");
    try
    {
        // 1. 根据接口名称做校验，如果通过则返回对应接口内容
        Interface interface = checkInterface(funName);

        // 2. 获取接口中的请求参数
		std::string weather_api_key = (interface.toJson())["requestParams"]["key"].asString();

        std::string host("");
        std::string path("");
        getHostAndPathFromUrl(interface.getValueOfUrl(), host, path);

        // 3. 填写对应请求内容，发送请求
        auto client = HttpClient::newHttpClient(host);
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(httpMethodMap[interface.getValueOfMethod()]);
        req->setPath(path);

        auto json = *(request->getJsonObject());
        std::string city = json.isMember("city") ? json["city"].asString() : "";

        // 高德天气API
        req->setParameter("key", weather_api_key); // 请求服务权限标识
        req->setParameter("city", city);           // 城市编码
        req->setParameter("extensions", "all");    // 气象类型 base:返回实况天气,all:返回预报天气
        req->setParameter("output", "JSON");       // 返回格式:可选值：JSON,XML ,默认JSON

        weatherInfo = syncSendRequest(req, client);
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), funName + InterfaceDescription::NO_EXIST());
    }

    return weatherInfo;
}

void InterfaceServiceImpl::getHostAndPathFromUrl(const std::string &url, std::string &host, std::string &path)
{
    try
    {
        int postion = url.find("//");

        int divide_postion = url.find("/", postion + 2);

        if (divide_postion != -1)
        {
            host = url.substr(0, divide_postion);
            path = url.substr(divide_postion);
        }
        else
        {
            host = url;
        }

        LOG_INFO << "[getHostAndPathFromUrl] url:" << url << ", host:" << host << ", path:" << path;
    }
    catch (...)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), InterfaceDescription::PARSE_URL_ERROR());
    }
}

std::string InterfaceServiceImpl::syncSendRequest(const HttpRequestPtr &req, const HttpClientPtr &client, const std::string &keyword)
{
    std::string res("");
    
    std::pair<ReqResult, HttpResponsePtr> resp = client->sendRequest(req);
    std::string respBody("");
    if (resp.first == ReqResult::Ok)
    {
        respBody = static_cast<std::string>((resp.second)->body()); // TODO 翻译和背景 有问题，会core
    }
    else
    {
        LOG_ERROR << "[syncSendRequest] error";
        return res;
    }

    LOG_INFO << "[syncSendRequest] respBody:" << respBody;

    if (keyword.empty())
    {
        return respBody;
    }

    Json::Reader reader;
    Json::Value value;
    if (reader.parse(respBody, value))
    {
        res = value[keyword].asString();
    }

    LOG_INFO << "[syncSendRequest] keyword:" << keyword << ", value:" << res;

    return res;
}

Interface InterfaceServiceImpl::checkInterface(const std::string& interfaceName)
{
    Interface interface;

    if (!cacheServicePtr_->getInterfaceInfoByName(interfaceName, interface))
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), interfaceName + InterfaceDescription::NO_EXIST());
    }

    if (interface.getValueOfStatus() != 0)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), interface.getValueOfName() + InterfaceDescription::STATUS_ERROR());
    }

    /*
    if(interface.getValueOfIsdelete != "0"){
        throw BusinessException(ErrorCode::PARAMS_ERROR(), name + "接口已经删除");
    }
    */

   return interface;
}

void InterfaceServiceImpl::toLower(std::string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        str[i] = tolower(str[i]);
    }
}

} } // namespace stibel_init::service