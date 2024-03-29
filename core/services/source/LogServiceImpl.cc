#include "impl/LogServiceImpl.h"
#include "BusinessException.h"

using namespace stibel_init;
using namespace drogon;
using namespace drogon::internal;
using namespace stibel_init::exception;

namespace stibel_init {
namespace service {

LogServiceImpl::LogServiceImpl()
{
    LOG_INFO << "LogServiceImpl constructor!";
}

LogServiceImpl::~LogServiceImpl()
{
    LOG_INFO << "LogServiceImpl destructor!";
}

bool LogServiceImpl::writeUserLog(long userid, const std::string &content)
{
    std::string funName = __FUNCTION__;
    bool res = false;
    try
    {
        Log log;
        log.setUserid(userid);
        log.setContent(content);
        logMapper.insert(log);

        /*
        auto ret = logMapper.findBy(Criteria(Log::Cols::_userid, CompareOperator::EQ, userid) &&
                                    Criteria(Log::Cols::_content, CompareOperator::EQ, content));
        if (ret.size() >= 1)//可能有重复内容的记录
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), "插入数据失败");
        }
        */

        LOG_ERROR << "[writeUserLog] userid:" << userid << ", content:" << content << " success";
        res = true;
    }
    catch (const DrogonDbException &e)
    {
        throw BusinessException(ErrorCode::PARAMS_ERROR(), funName + "执行失败");
    }

    return res;
}

} } // namespace stibel_init::service