#include "LoginFilter.h"
#include "HttpResponseUtils.h"
#include "UserDescription.h"

using namespace drogon;
void LoginFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    //Edit your logic here
    try{
        //管理员用户校验
        if (!srvPtr_->isAdmin(req))
        {
            throw stibel_init::exception::BusinessException(stibel_init::exception::ErrorCode::PARAMS_ERROR(), stibel_init::utils::UserDescription::NO_QUERY_PERMISSION());
        }

        //接口存在性校验  todo
        /*if (!srvPtr_->isAdmin(req))
        {
            throw BusinessException(ErrorCode::PARAMS_ERROR(), "LoginFilter::非管理员用户，无查询权限");
        }*/

        //Passed
        fccb();
        return;
    }
    catch (stibel_init::exception::BusinessException &e)
    {
        stibel_init::utils::callErrorResponse(std::move(fcb), e);
    }
}
