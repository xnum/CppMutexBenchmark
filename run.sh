#!/usr/bin/env sh

g++ threadsafe.cxx -std=c++17 -lbenchmark -pthread -ltbb -lboost_thread -o mybenchmark && ./mybenchmark
