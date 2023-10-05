# 第三方库设置
## 设置第三方应用库的头文件
execute_process(COMMAND sh ${PROJECT_SOURCE_DIR}/cmake/make_fun_stat.sh
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/core/common/include)
