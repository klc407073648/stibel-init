#ifndef __Cache_SERVICE_IMPL_H__
#define __Cache_SERVICE_IMPL_H__

#include "inner/CacheService.h"
#include <drogon/drogon.h>

namespace stibel_init {
namespace service {

using drogon_model::stibel_init::Interface;

enum CacheType
{
  BY_MEMEORY,
  BY_REDIS
};

class CacheServiceImpl : public CacheService
{
public:
  CacheServiceImpl();
  ~CacheServiceImpl();
  bool getInterfaceInfoByName(const std::string &name, Interface &interface) override;
  std::map<std::string, Interface> getInterfaceInfoMap();
private:
  void initData();

private:
  Mapper<Interface> interfaceMapper_ = drogon::orm::Mapper<Interface>(drogon::app().getDbClient()); // 对象持久化映射层,连接User对象和数据库
  std::map<std::string, Interface> name2Interface_;
  CacheType cacheType_;
};

} } // namespace stibel_init::service

#endif //__Cache_SERVICE_IMPL_H__