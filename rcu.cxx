#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <unordered_map>
#include <shared_mutex>
#include "benchmark/benchmark.h"

using namespace std;

static void BM_SharedLock(benchmark::State &state)
{
  unordered_map<int, double> m;
  m.rehash(2048);
  for(int key = 1; key <= 1000; key++) {
    m.emplace(key, 3.14);
  }

  shared_mutex mtx;
  for(auto _ : state) {
    shared_lock<shared_mutex> lk(mtx);
    double s = 0;
    for(const auto &it : m) {
      s += it.second;
    }
  }
}

static void BM_RCU_SharedPtr(benchmark::State &state)
{
  auto m = make_shared<unordered_map<int, double>>();
  m->rehash(2048);
  for(int key = 1; key <= 1000; key++) {
    m->emplace(key, 3.14);
  }

  for(auto _ : state) {
    auto t = m;
    double s = 0;
    for(const auto &it : *m) {
      s += it.second;
    }
  }
}

BENCHMARK(BM_SharedLock);
BENCHMARK(BM_RCU_SharedPtr);

BENCHMARK_MAIN();
