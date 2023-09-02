/**
 * @file LoginFilter.h
 * @brief 过滤器
 * @author klc
 * @date 2023-08-05
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_LOGIN_FILTER_H__
#define __STIBEL_LOGIN_FILTER_H__

#include "impl/UserServiceImpl.h"
#include <drogon/HttpFilter.h>

using namespace drogon;
using namespace stibel_init;
using stibel_init::service::UserServicePtr;
using stibel_init::service::UserServiceImpl;

class LoginFilter : public HttpFilter<LoginFilter>
{
  public:
    LoginFilter():srvPtr_(new UserServiceImpl()) {}

    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
  private:
    UserServicePtr srvPtr_;
};

#endif //__STIBEL_LOGIN_FILTER_H__