FROM ubuntu:20.04
LABEL name="yuuuuuuan"
LABEL maintainer="https://github.com/yuuuuuuan"

# Install build dependencies
RUN apt-get update -y \
    && apt-get install -y make \
    build-essential \
    apt-utils \
    git \
    && apt-get clean

CP /arm/uboot_tiny4412-20130729.tgz ../uboot_tiny4412-20130729.tgz
CP /arm/arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz ../arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz
