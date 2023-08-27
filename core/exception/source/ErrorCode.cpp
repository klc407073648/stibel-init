#include "ErrorCode.h"

namespace stibel_init {
namespace exception {

DEFINE_STATIC_ERROR_CODE(SUCCESS,SUCCESS, "ok", "")
DEFINE_STATIC_ERROR_CODE(PARAMS_ERROR,PARAMS_ERROR, "Request parameter error", "")//请求参数错误
DEFINE_STATIC_ERROR_CODE(NULL_ERROR,NULL_ERROR, "Request data is empty", "")//请求数据为空
DEFINE_STATIC_ERROR_CODE(NO_LOGIN,NO_LOGIN, "No login", "")//未登录
DEFINE_STATIC_ERROR_CODE(NO_AUTH,NO_AUTH, "No permission", "")//无权限
DEFINE_STATIC_ERROR_CODE(SYSTEM_ERROR,SYSTEM_ERROR, "Internal system error", "")//系统内部异常

} } // namespace stibel_init::exception