#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "benchmark/benchmark.h"

using namespace std;

static void BM_ContainerCopy(benchmark::State &state)
{
  map<int, double> m;
  for(int key = 1; key <= 100; key++) {
    m.emplace(key, 3.14);
  }

  auto fn = [&m]() -> map<int, double> { return m; };

  for(auto _ : state) {
    auto t = fn();
    double s = 0;
    for(const auto &it : t) {
      s += it.second;
    }
  }
}

static void BM_NoContainerCopy(benchmark::State &state)
{
  map<int, double> m;
  for(int key = 1; key <= 100; key++) {
    m.emplace(key, 3.14);
  }

  auto fn = [&m](std::function<void(int, double)> action) {
    for(const auto &it : m) {
      action(it.first, it.second);
    }
  };

  for(auto _ : state) {
    double sum = 0;
    fn([&sum](int k, double v) { sum += v; });
  }
}

BENCHMARK(BM_ContainerCopy);
BENCHMARK(BM_NoContainerCopy);

BENCHMARK_MAIN();
