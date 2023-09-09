#ifndef __CACHE_SERVICE_H__
#define __CACHE_SERVICE_H__

#include "Interface.h"

using namespace drogon;

// CacheService 纯虚函数，接口类

namespace stibel_init {
namespace service {

using drogon_model::stibel_init::Interface;

class CacheService;
using CacheServicePtr = std::shared_ptr<CacheService>;

class CacheService
{
public:
  /**
   * @brief 根据接口名称获取接口信息
   *
   */
  virtual bool getInterfaceInfoByName(const std::string &name, Interface &interface) = 0;
};

} } // namespace stibel_init::service

#endif //__CACHE_SERVICE_H__