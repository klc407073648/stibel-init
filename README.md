# stibel_init

cpp后端开发万用模板，基于drogon的Web应用框架，集成各类库的功能实现

## 使用方法

### 启动镜像

```
docker run -it -d --rm=false --privileged --restart="always" --name build_lib_test_run  -e.utf8 \
    -v /home/stibel/build_lib:/home/stibel/build_lib \
    -v /var/run/docker.sock:/var/run/docker.sock -v $(which docker):/usr/bin/docker    \
    -v $(which gdb):/usr/bin/gdb    \
    -p 8082:8082 \
    -w /home/stibel/build_lib docker.io/klc407073648/centos_build_lib:v3.0 /bin/bash
```

### 容器内编译

#### 脚本方式

```
# 将 StiBel_V2.1.1.tar.gz 放置在 /home/stibel/stibel-init/ 路径下
cd /home/stibel/stibel-init/docker/
chmod 777 build.sh
dos2unix build.sh
./build.sh

cd ../deploy/
./stibel-init
```

#### 手工方式

```
cd /home/stibel/build_lib/stibel-init/
tar -zxvf StiBel_V2.1.1.tar.gz
mkdir -p build
cd ./build/
export LD_LIBRARY_PATH=/home/stibel/build_lib/stibel-init/lib/3partlib:/home/stibel/build_lib/stibel-init/lib/comlib
ldconfig

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_VERSION=V2.1.1 ..
make

# 需要业务库剥离
export LD_LIBRARY_PATH=/home/stibel/lib/app
ldconfig
```

### 测试验证

#### 另外起一个终端做测试

```
cd ../deploy/
./InterfaceControllerTest
./UserControllerTest
```

#### gdb测试

```
# 断点调试
gdb -tui --args ./InterfaceControllerTest
b HttpTest.cpp:31

# 执行指定用例
./UserControllerTest  --gtest_filter=*Register_userAccount_Null*
```

### 其他测试

```
curl -XPOST 81.68.132.31:8083/api/user/register -H 'content-type:  application/json' -d '{"userAccount":"111","userPassword":"222","checkPassword":"333","planetCode":"4444"}'
```

## 其他

ldd 找寻需要的so，基于centos7运行

```
docker run -it -d --rm=false --privileged --restart="always" --name build_lib_centos_7  -e.utf8 \
    -v /home/stibel/build_lib:/home/stibel/build_lib \
    -v /var/run/docker.sock:/var/run/docker.sock -v $(which docker):/usr/bin/docker    \
    -v $(which gdb):/usr/bin/gdb    \
    -p 8083:8083 \
    -w /home/stibel/build_lib centos:7 /bin/bash
```