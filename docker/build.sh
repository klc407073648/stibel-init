#!/bin/bash
source ./common.sh

function preDeal() 
{
   logDebug "preDeal begin"

   if [ ! -d $work_path/build ]; then
      mkdir -p $work_path/build
   else
      rm -rf $work_path/build/*
   fi

   if [ ! -d $work_path/logs ]; then
      mkdir -p $work_path/logs
   else
      rm -rf $work_path/logs/*
   fi

   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$work_path/lib/3partlib:$work_path/lib/comlib
   cd $work_path/docker && chmod 777 *.sh && dos2unix *.sh

   logDebug "preDeal end"
}

function buildProject() 
{
   logDebug "buildProject begin"

   cd $work_path
   tar zxf StiBel_V2.1.1.tar.gz

   cd $work_path/build  && rm -rf ./*

   #cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DCMAKE_BUILD_VERSION=V2.1.1 ..
   cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DCMAKE_BUILD_VERSION=V2.1.1 ..
   make -j4

   checkBuildResult buildProject

   # 链接so特殊处理
   cd $work_path/docker && ./ldd.sh

   logDebug "buildProject end"
}

function tarProject() 
{
   logDebug "tarProject begin"

   cd $work_path
   mkdir -p $work_path/logs
   touch $work_path/logs/stibel-init.log 
   
   # tar -zcvf stibel-init.tar.gz ./lib/app ./deploy ./conf ./docker ./logs
   # 后续看是否需要区分包含测试用例所需的json文件
   tar -zcvf stibel-init.tar.gz ./lib/app ./deploy ./conf ./docker ./logs ./testcase/json
   logDebug "tarProject end"
}

function MAIN() 
{
   logDebug "build.sh MAIN begin"
   preDeal
   buildProject
   tarProject
   logDebug "build.sh MAIN end"
}

MAIN