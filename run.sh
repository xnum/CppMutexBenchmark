#!/usr/bin/env sh

g++ shared_ptr.cxx -O3 -march=native -std=c++17 -lbenchmark -pthread -ltbb -lboost_thread -o mybenchmark && ./mybenchmark
