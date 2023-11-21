FROM ubuntu:20.04
LABEL name="yuuuuuuan"
LABEL maintainer="https://github.com/yuuuuuuan"

# Install build dependencies
RUN apt-get update -y \
    && apt-get install -y make \
    build-essential \
    apt-utils \
    git \
    vim \
    minicom \
    && apt-get clean

COPY build.sh uboot_tiny4412-20130729.tgz arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz /arm/
COPY /exp /arm/exp

RUN chmod +x /arm/build.sh && \
	/arm/build.sh && \
	rm uboot_tiny4412-20130729.tgz && arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz

ENV PATH="/arm/opt/FriendlyARM/toolschain/4.5.1/bin:${PATH}"

