#基础镜像
FROM centos:7

#创建路径
WORKDIR /home/stibel

#拷贝源文件
ADD ./stibel-init.tar.gz  /home/stibel

#添加动态搜索库路径; 替换宏定义; 修改权限； stibel.conf  来自
RUN  cp -rf /home/stibel/conf/etc/ld.so.conf.d/stibel.conf  /etc/ld.so.conf.d \
     && echo '$PROJECT_WORK_PATH/lib/app' >> /etc/ld.so.conf.d/stibel.conf  \
     && sed -i "s/\$PROJECT_WORK_PATH/\/home\/stibel/g"  /etc/ld.so.conf.d/stibel.conf  \
     && chmod 777 /etc/ld.so.conf.d/stibel.conf 

#添加ldconfig操作到 /etc/profile; source 使得动态库搜索的环境变量生效; 解决重启配置不生效（source /etc/profile）
RUN echo 'ldconfig'  >> /etc/profile \
    && source /etc/profile  \
    && echo 'source /etc/profile'   >> ~/.bashrc

#配置环境变量
ENV project_name  stibel-init

#执行命令 
CMD ["/bin/bash","-c","cd /home/stibel/docker && chmod 777 *.sh && dos2unix *.sh && ./run.sh && tail -f /dev/null"] 