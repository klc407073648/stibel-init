# stibel-init

cpp后端开发万用模板，基于drogon的Web应用框架，集成各类库的功能实现


使用方式：

```
# 手动解压 StiBel_V2.1.1.tar.gz
mkdir -p /home/stibel/stibel-init/build/
cd /home/stibel/stibel-init/build/
rm -rf ./*
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_VERSION=V2.1.1 ..
make -j32
```

使用脚本：

```
# 将 StiBel_V2.1.1.tar.gz 放置在 /home/stibel/stibel-init/ 路径下
cd /home/stibel/stibel-init/docker/

./build.sh
```

## 手动使用

镜像启动
```
docker run -it -d --rm=false --privileged --restart="always" --name build_lib_test  -e.utf8 \
    -v /home/stibel/build_lib:/home/stibel/build_lib \
    -v /var/run/docker.sock:/var/run/docker.sock -v $(which docker):/usr/bin/docker    \
    -v $(which gdb):/usr/bin/gdb    \
    -w /home/stibel/build_lib docker.io/klc407073648/centos_build_lib:v3.0 /bin/bash
```

编译
```
cd /home/stibel/build_lib/stibel-init/
tar -zxvf StiBel_V2.1.1.tar.gz
mkdir -p build
cd ./build/
export LD_LIBRARY_PATH=/home/stibel/build_lib/stibel-init/lib/3partlib:/home/stibel/build_lib/stibel-init/lib/comlib
ldconfig

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_VERSION=V2.1.1 ..
make
```

```gdb
gdb -tui --args ./InterfaceControllerTest
b HttpTest.cpp:31
```
