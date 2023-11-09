/**
 * @file FunStat.h
 * @brief 描述信息
 * @author klc
 * @date 2023-07-29
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_FunStat_H__
#define __STIBEL_FunStat_H__

#include<array>
#include<map>
#include<string>

//函数统计目的：为了记录代码具体跑到的功能点
/*
实现方式：为需要进行统计的函数创建一个定长数组，一般为8个分支，因为分支过多的话也需要考虑封装小的函数

步骤：
1. 预定义数组：std::array<int,MAX_ARRAY_NUM> UserController_userRegister
2. 使用：MAKE_FUN_STAT(num)

*/

namespace stibel_init {
namespace common {

#define MAX_ARRAY_NUM 8 //函数统计数组的最大长度

#define MAKE_FUN_STAT_ARRAY(array_name, length) \
    g_fun_stat_map[#array_name]={0}; 

#define MAKE_FUN_STAT(index) \
{\
    if(USE_FUN_STAT) \
    FunStat::getInstance()->increaseCount(FUN_NAME,index); \
}

class FunStat
{
public:
    static FunStat* getInstance();
    void init();
    void increaseCount(std::string fun_name,int pos);
    void show();

private:
    FunStat();
    ~FunStat();

private:
    std::map<std::string,std::array<long,MAX_ARRAY_NUM>> g_fun_stat_map;
};
} } // namespace stibel_init::common

# endif