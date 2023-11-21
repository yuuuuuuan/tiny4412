FROM ubuntu:20.04
LABEL name="yuuuuuuan"
LABEL maintainer="https://github.com/yuuuuuuan"

# 将本地的脚本文件复制到镜像中
COPY myscript.sh /usr/local/bin/myscript.sh

# 设置脚本文件的执行权限并执行
RUN chmod +x /usr/local/bin/myscript.sh && /usr/local/bin/myscript.sh

