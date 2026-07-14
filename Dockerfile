FROM ubuntu:12.04

RUN sed -i 's/archive.ubuntu.com/old-releases.ubuntu.com/g' /etc/apt/sources.list && \
    apt-get update && \
    apt-get install -y \
    build-essential \
    libncurses5-dev \
    libssl-dev \
    libelf-dev \
    bc \
    flex \
    bison \
    wget \
    nano

WORKDIR /kernel

RUN wget --no-check-certificate https://busybox.net/downloads/busybox-1.17.4.tar.bz2 && \
    tar xf busybox-1.17.4.tar.bz2

COPY linux-2.6.32.tar.xz .

RUN tar xf linux-2.6.32.tar.xz

CMD ["bash"]
