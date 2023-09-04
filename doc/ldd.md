# ldd截取需要的so

原始命令执行结果
```
[root@b62fd7877e1e deploy]# ldd stibel-init
        linux-vdso.so.1 =>  (0x00007ffc6e1c7000)
        libdrogon.so.1 => /home/stibel/build_lib/stibel-init/lib/3partlib/lib64/libdrogon.so.1 (0x00007f81d1be9000)
        libtrantor.so.1 => /home/stibel/build_lib/stibel-init/lib/3partlib/lib64/libtrantor.so.1 (0x00007f81d1815000)
        libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f81d15f9000)
        libjsoncpp.so.25 => /home/stibel/build_lib/stibel-init/lib/3partlib/libjsoncpp.so.25 (0x00007f81d13c0000)
        libstdc++.so.6 => /home/stibel/build_lib/stibel-init/lib/3partlib/libstdc++.so.6 (0x00007f81d0fe7000)
        libm.so.6 => /lib64/libm.so.6 (0x00007f81d0ce5000)
        libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f81d0acf000)
        libc.so.6 => /lib64/libc.so.6 (0x00007f81d0701000)
        libdl.so.2 => /lib64/libdl.so.2 (0x00007f81d04fd000)
        libz.so.1 => /home/stibel/build_lib/stibel-init/lib/3partlib/libz.so.1 (0x00007f81d02e2000)
        libssl.so.3 => /home/stibel/build_lib/stibel-init/lib/3partlib/libssl.so.3 (0x00007f81d0039000)
        libcrypto.so.3 => /home/stibel/build_lib/stibel-init/lib/3partlib/libcrypto.so.3 (0x00007f81cf9bf000)
        libuuid.so.1 => /home/stibel/build_lib/stibel-init/lib/3partlib/libuuid.so.1 (0x00007f81cf7bb000)
        libmysqlclient.so.18 => /home/stibel/build_lib/stibel-init/lib/3partlib/libmysqlclient.so.18 (0x00007f81cf2bb000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f81d24c9000)
        libssl.so.10 => /lib64/libssl.so.10 (0x00007f81cf049000)
        libcrypto.so.10 => /lib64/libcrypto.so.10 (0x00007f81cebe6000)
        libgssapi_krb5.so.2 => /lib64/libgssapi_krb5.so.2 (0x00007f81ce999000)
        libkrb5.so.3 => /lib64/libkrb5.so.3 (0x00007f81ce6b0000)
        libcom_err.so.2 => /lib64/libcom_err.so.2 (0x00007f81ce4ac000)
        libk5crypto.so.3 => /lib64/libk5crypto.so.3 (0x00007f81ce279000)
        libkrb5support.so.0 => /lib64/libkrb5support.so.0 (0x00007f81ce069000)
        libkeyutils.so.1 => /lib64/libkeyutils.so.1 (0x00007f81cde65000)
        libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f81cdc4b000)
        libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f81cda24000)
        libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f81cd7c2000)
```

预处理后

```
[root@b62fd7877e1e deploy]# ldd stibel-init  | grep -v "linux-vdso.so.1" | cut -d ">" -f 2 |cut -d "(" -f 1
 /home/stibel/build_lib/stibel-init/lib/3partlib/lib64/libdrogon.so.1
 /home/stibel/build_lib/stibel-init/lib/3partlib/lib64/libtrantor.so.1
 /lib64/libpthread.so.0
 /home/stibel/build_lib/stibel-init/lib/3partlib/libjsoncpp.so.25
 /home/stibel/build_lib/stibel-init/lib/3partlib/libstdc++.so.6
 /lib64/libm.so.6
 /lib64/libgcc_s.so.1
 /lib64/libc.so.6
 /lib64/libdl.so.2
 /home/stibel/build_lib/stibel-init/lib/3partlib/libz.so.1
 /home/stibel/build_lib/stibel-init/lib/3partlib/libssl.so.3
 /home/stibel/build_lib/stibel-init/lib/3partlib/libcrypto.so.3
 /home/stibel/build_lib/stibel-init/lib/3partlib/libuuid.so.1
 /home/stibel/build_lib/stibel-init/lib/3partlib/libmysqlclient.so.18
        /lib64/ld-linux-x86-64.so.2
 /lib64/libssl.so.10
 /lib64/libcrypto.so.10
 /lib64/libgssapi_krb5.so.2
 /lib64/libkrb5.so.3
 /lib64/libcom_err.so.2
 /lib64/libk5crypto.so.3
 /lib64/libkrb5support.so.0
 /lib64/libkeyutils.so.1
 /lib64/libresolv.so.2
 /lib64/libselinux.so.1
 /lib64/libpcre.so.1
```

脚本拷贝需要的so

```
tmp=`ldd stibel-init  | grep -v "linux-vdso.so.1" | cut -d ">" -f 2 |cut -d "(" -f 1`
mkdir -p temp
echo "$tmp" | while read rows
do
  cp -rf $rows ./temp
done
```
