#!/bin/bash

# 具体逻辑参见ldd.md
cur_path=`pwd`
exec_file_list=`ls $cur_path/../deploy`
app_lib_path=$cur_path/../lib/app
mkdir -p $app_lib_path

# 思路：ldd获取可执行文件的so列表，然后拷贝到 app_lib_path 下
for exec_file in $exec_file_list  
do 
   echo "current exec_file is $exec_file"
   depend_so_list=`ldd $cur_path/../deploy/$exec_file  | grep -v "linux-vdso.so.1" | cut -d ">" -f 2 |cut -d "(" -f 1`
   #echo $depend_so_list
   echo "$depend_so_list" | while read rows
   do
      cp -rf $rows $app_lib_path
   done
done
