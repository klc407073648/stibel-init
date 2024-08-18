# 功能

- [X] 初始项目代码，移植来自cmd-terminal/cpp-backend的内容
- [X] 测试用例 UserControllerTest、InterfaceControllerTest 整改
- [ ] 编译警告整改： warning: 'BusinessException::message_' will be initialized after [-Wreorder]  
- [ ] 配置类，读写锁
- [ ] 根据测试用例是否成功判断，构建是否正常，或者区分构建成功和用例成功
- [ ] 测试用例interface given when then
- [ ] 需求分析
- [ ] 方案设计  逻辑框图
- [ ] 编码实现
- [ ] 依赖数据库的测试 —————— 不应该依赖测试用例，自己打桩覆盖函数
- [ ] core下面目录细化
- [ ] UserControllerTest调试，让中文国际化能够对上，移植cmd-terminal下的文档
       UserControllerTest 还待调试，Interface用例也是

       函数统计
       构建镜像

- [ ] 测试用例interface given when then
- [ ] 需求分析
- [ ] 方案设计  逻辑框图
- [ ] 编码实现
- [X] 研究公司代码的函数统计
- [ ] 参考infra分不同路径，明确代码用途
- [ ] 多线程处理thread local
- [ ] 全局异常处理
- [ ] 调试命令处理
- [X] 改目录结构按照功能分类，不要再include了
- [X] 国际化代码和用例校验
- [ ] Debug和Release区别生不生成测试程序和testcase ———— BUILD_TESTS 来区分不生成程序程序
- [X] 命令空间整改stibel_init service controller utils common                drogon_model::stibel_init::  
- [ ] swd.sh 无法正常拉起来进程 
- [ ] 补充其他函数打印，打印需要收到控制，需要接管drogon的打印
- [ ] 定时器的库，实现MySQL接口数据库内容会有定时刷新数据的更新，避免数据不一致
- [ ] 考虑接管drogon库的日志打印，采用log4cpp
- [ ] 考虑多线程处理