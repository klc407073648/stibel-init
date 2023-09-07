#include "inner/impl/CacheServiceImpl.h"
#include "BusinessException.h"
#include "InterfaceDescription.h"

using namespace drogon;
using namespace stibel_init::exception;
using stibel_init::utils::InterfaceDescription;

namespace stibel_init {
namespace service {

CacheServiceImpl::CacheServiceImpl()
{
    LOG_INFO << "CacheServiceImpl constructor!";
    initData();
}

CacheServiceImpl::~CacheServiceImpl()
{
    LOG_INFO << "CacheServiceImpl destructor!";
}

void CacheServiceImpl::initData()
{
    try
    {
        auto interfaces = interfaceMapper_.findAll();
        for (auto &interface : interfaces)
        {
            std::string name = interface.getValueOfName();
            int isDelete = interface.getValueOfIsdelete();

            // 接口未被删除
            if (isDelete == 0)
            {
                name2Interface_.insert(make_pair(name, interface));
                LOG_DEBUG << "name:" << name << ",value:" << interface.toJson().toStyledString();
            }
        }
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), InterfaceDescription::GET_INFO_ERROR());
    }
}

bool CacheServiceImpl::getInterfaceInfoByName(const std::string &name, Interface &interface)
{
    if (name2Interface_.count(name) > 0)
    {
        interface = name2Interface_[name];
        return true;
    }
    return false;
}

} } // namespace stibel_init::service
