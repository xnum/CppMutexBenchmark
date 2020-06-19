#include <vector>
#include <map>
#include <unordered_map>
#include "benchmark/benchmark.h"

using namespace std;

static void BM_MapFind(benchmark::State &state)
{
  map<int, double> m;
  for(int key = 1; key <= 1000; key++) {
    m.emplace(key, 3.14);
  }

  for(auto _ : state) {
    for(int i = 1; i <= 1000; i++) {
      m.find(i);
    }
  }
}

static void BM_UnorderedMapFind(benchmark::State &state)
{
  unordered_map<int, double> m;
  for(int key = 1; key <= 1000; key++) {
    m.emplace(key, 3.14);
  }

  for(auto _ : state) {
    for(int i = 1; i <= 1000; i++) {
      m.find(i);
    }
  }
}

BENCHMARK(BM_MapFind);
BENCHMARK(BM_UnorderedMapFind);

BENCHMARK_MAIN();
