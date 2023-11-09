#include "FunStat.h"
#include <stdio.h>
#include <vector>

namespace stibel_init {
namespace common {

FunStat *FunStat::getInstance()
{
    static FunStat funStat;
    return &funStat;
}

FunStat::FunStat()
{
}

FunStat::~FunStat()
{
}

void FunStat::init()
{
#ifdef USE_FUN_STAT
#include "fun_stat.inc"
#endif
}

void FunStat::increaseCount(std::string fun_name, int pos)
{
    g_fun_stat_map[fun_name][pos]++;
}

void FunStat::show()
{
    std::string nullstr("");
    std::vector<std::string> vec = {"index0", "index1", "index2", "index3", "index4", "index5", "index6", "index7"};
    printf("%45s%10s %10s %10s %10s %10s %10s %10s %10s\n",
           nullstr.c_str(), vec[0].c_str(), vec[1].c_str(), vec[2].c_str(), vec[3].c_str(), vec[4].c_str(), vec[5].c_str(), vec[6].c_str(), vec[7].c_str());
    for (auto iter = g_fun_stat_map.begin(); iter != g_fun_stat_map.end(); iter++)
    {
        auto funName = iter->first;
        auto arr = g_fun_stat_map[funName];
        printf("[%40s]: %10d %10d %10d %10d %10d %10d %10d %10d\n",
               funName.c_str(), arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]);
    }
}

}} // namespace stibel_init::common