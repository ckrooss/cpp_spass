FROM ubuntu:26.04

WORKDIR /project

RUN export DEBIAN_FRONTEND=noninteractive  \
         && apt-get update \
         && apt-get install -y \
            wget \
            lsb-release \
            software-properties-common \
            g++-14 \
            g++-15 \
            g++-16 \
            clang-20 \
            clang-21 \
            clang-22 \
            cmake \
            git \
            gdb \
         && apt-get autoremove --purge -y \
         && apt-get autoclean -y \
         && rm -rf /var/cache/apt/*

RUN export DEBIAN_FRONTEND=noninteractive  \
      && apt-get update \
      && apt-get install -y \
         clangd \
         clangd-20 \
         clangd-21 \
         clangd-22

RUN echo 'DEBUGINFOD_URLS=""' >> /etc/environment
RUN echo 'export DEBUGINFOD_URLS=""' >> /root/.bashrc
ENTRYPOINT [ "/bin/bash" ]
