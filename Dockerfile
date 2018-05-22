################################################################
#  Compiler-assisted Code Randomization - Dockerfile           #
#   (In the 39th IEEE Symposium on Security & Privacy 2018)    #
#                                                              #
#  Author: Hyungjoon Koo <hykoo@cs.stonybrook.edu>             #
#          Computer Science@Stony Brook University             #
#                                                              #
#  This file can be distributed under the MIT License.         #
#  See the LICENSE.TXT for details.                            #
################################################################

FROM       ubuntu:16.04
MAINTAINER Hyungjoon Koo (hykoo@cs.stonybrook.edu)

RUN apt-get -y update && apt-get install -y \
    git \
    texinfo \
    byacc \
    flex \
    bison \
    automake \
    autoconf \
    build-essential \
    libtool \
    cmake \
    gawk \
    python \
    python-dev \
    wget \
    elfutils \
    sudo \
    python-pip

RUN pip install protobuf pyelftools

RUN git clone https://github.com/kevinkoo001/CCR.git
WORKDIR /CCR
RUN ./build_docker.sh
RUN ldconfig