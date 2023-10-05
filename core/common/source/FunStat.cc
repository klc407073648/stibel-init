#include "FunStat.h"
#include <stdio.h>
#include <vector>

namespace stibel_init {
namespace common {

FunStat* FunStat::getInstance()
{
    static FunStat* funStat = new FunStat();
    return funStat;
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

void FunStat::increaseCount(std::string fun_name,int pos)
{
    g_fun_stat_map[fun_name][pos]++;
}

void FunStat::show()
{
	std::vector<std::string> vec ={"index0","index1","index2","index3","index4","index5","index6","index7"};
    printf("                            %10s %10s %10s %10s %10s %10s %10s %10s\n", \
        vec[0],vec[1],vec[2],vec[3],vec[4],vec[5],vec[6],vec[7]);
    for (auto iter = g_fun_stat_map.begin();iter != g_fun_stat_map.end();iter++)
    {
        auto funName = iter->first;
        auto arr = g_fun_stat_map[funName];
        printf("Function Stat fun_name:[%s]: %10d %10d %10d %10d %10d %10d %10d %10d\n", \
        funName.c_str(), arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],arr[7]);
    }
    
}

}} // namespace stibel_init::common