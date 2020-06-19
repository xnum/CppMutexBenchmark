#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "benchmark/benchmark.h"

using namespace std;

static void BM_Functional(benchmark::State &state)
{
  map<int, double> m;
  for(int key = 1; key <= 100; key++) {
    m.emplace(key, 3.14);
  }

  for(auto _ : state) {
    double v = 0;
    auto fn = [&v](const pair<const int, double> &it) { v += it.second; };
    for_each(m.begin(), m.end(), fn);
  }
}

static void BM_Iterator(benchmark::State &state)
{
  map<int, double> m;
  for(int key = 1; key <= 100; key++) {
    m.emplace(key, 3.14);
  }

  for(auto _ : state) {
    double v = 0;
    for(auto it = m.begin(); it != m.end(); it++) {
      v += it->second;
    }
  }
}

BENCHMARK(BM_Functional);
BENCHMARK(BM_Iterator);

BENCHMARK_MAIN();
