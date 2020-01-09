FROM alpine:latest

RUN apk update && \
    apk add --no-cache \
            boost \
            boost-dev \
            cmake \
            git \
            g++ \
            linux-headers \
            make

RUN git clone https://github.com/ffontaine/tbb.git --depth 1 && cd tbb && \
    make -j4 && cp -r include /usr/local && \
    cp -r build/linux_intel64_gcc_cc9.2.0_libc_kernel5.0.0_release/*.so.2 /usr/local/lib && \
    cd .. && rm -rf tbb && \
    cd /usr/local/lib/ && \
    ln -s libtbb.so.2 libtbb.so && \
    ln -s libtbbmalloc.so.2 libtbbmalloc.so && \
    ln -s libtbbmalloc_proxy.so.2 libtbbmalloc_proxy.so

RUN git clone https://github.com/google/benchmark.git --depth 1 && \
    git clone https://github.com/google/googletest.git --depth 1 benchmark/googletest && \
    cd benchmark && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && make -j4 && make install && \
    cd / && rm -rf benchmark

COPY . /src

WORKDIR /src
CMD sh ./run.sh
