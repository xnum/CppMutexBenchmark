#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <unordered_map>
#include "benchmark/benchmark.h"

using namespace std;

static void BM_MapInsert(benchmark::State &state)
{
  for(auto _ : state) {
    unordered_map<int, double> m;
    m.rehash(2048);
    for(int key = 1; key <= 1000; key++) {
      m.emplace(key, 3.14);
    }
  }
}

static void BM_DequeInsert(benchmark::State &state)
{
  struct S {
    int Key;
    double Value;
    S(int k, double v) : Key(k), Value(v)
    {}
  };

  for(auto _ : state) {
    deque<S> q;
    for(int key = 1; key <= 1000; key++) {
      q.emplace_back(S(key, 3.14));
    }
  }
}

BENCHMARK(BM_MapInsert);
BENCHMARK(BM_DequeInsert);

BENCHMARK_MAIN();
