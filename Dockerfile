FROM 32bit/ubuntu:16.04
LABEL name="yuuuuuuan"
LABEL maintainer="https://github.com/yuuuuuuan"

# Install build dependencies
RUN apt-get update -y \
    && apt-get install -y make \
    build-essential \
    apt-utils \
    git \
    vim \
    minicom
#   ia32-libs \
#   gcc-arm-linux-gnueabi \
#   -y lsb-core

COPY build.sh uboot_tiny4412-20130729.tgz arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz /arm/
COPY /exp /arm/exp

RUN chmod +x /arm/build.sh \
         && /arm/build.sh

RUN rm -rf /arm/uboot_tiny4412-20130729.tgz \
        /arm/arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz

ENV PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/arm/opt/FriendlyARM/toolschain/4.5.1/bin"

WORKDIR /arm/uboot_tiny4412/

RUN mkdir /mnt/sdb && chmod 777 /mnt/sdb \
    && make tiny4412_config \
    && make
