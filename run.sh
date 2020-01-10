#!/usr/bin/env sh

g++ threadsafe.cxx -O2 -std=c++17 -lbenchmark -pthread -ltbb -lboost_thread -o mybenchmark && ./mybenchmark
