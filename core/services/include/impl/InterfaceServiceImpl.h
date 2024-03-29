#ifndef __INTERFACE_SERVICE_IMPL_H__
#define __INTERFACE_SERVICE_IMPL_H__

#include "InterfaceService.h"
#include "inner/impl/CacheServiceImpl.h"

namespace stibel_init {
namespace service {

using drogon_model::stibel_init::Interface;

class InterfaceServiceImpl : public InterfaceService
{
public:
  InterfaceServiceImpl();
  ~InterfaceServiceImpl();

public:
  std::string getBackground(const HttpRequestPtr &request) override;
  std::string getTranslate(const HttpRequestPtr &request) override;
  std::string getBackendVersion(const HttpRequestPtr &request) override;
  std::string getCurrentWeather(const HttpRequestPtr &request) override;
  std::string getFutureWeather(const HttpRequestPtr &request) override;

private:
  /**
   * @brief 从URL信息里获取主机地址和路径
   *
   * @param url
   * @param host
   * @param path
   */
  void getHostAndPathFromUrl(const std::string &url, std::string &host, std::string &path);
  /**
   * @brief 根据json字符串内容获取请求参数
   *
   * @param req
   * @param jsonStr
   */
  void getRequestParams(const std::string &json, std::map<std::string, std::string> &retMap);
  /**
   * @brief 同步发送Http请求，解析返回信息里keyword字符串对应的内容
   *
   * @param req
   * @param client
   * @param keyword
   * @return std::string
   */
  std::string syncSendRequest(const HttpRequestPtr &req, const HttpClientPtr &client, const std::string &keyword = "");

  void initHttpMethodMap();
  void toLower(std::string &str);
  Interface checkInterface(const std::string& interfaceName);

private:
  CacheServicePtr cacheServicePtr_;
  std::map<std::string, drogon::HttpMethod> httpMethodMap;
};

} } // namespace stibel_init::service

#endif //__INTERFACE_SERVICE_IMPL_H__