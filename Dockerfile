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

COPY uboot_tiny4412-20130729.tgz /arm/uboot_tiny4412-20130729.tgz 
COPY arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz /arm/arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz 
