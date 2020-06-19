#include <vector>
#include "benchmark/benchmark.h"

using namespace std;

static void BM_PassObject(benchmark::State &state)
{
  auto fn = [](string s) { s.find('a'); };

  string a = "bcGGadd";
  for(auto _ : state) {
    fn(a);
  }
}

static void BM_PassRValueRef(benchmark::State &state)
{
  auto fn = [](const string &s) { s.find('a'); };

  string a = "bcGGadd";
  for(auto _ : state) {
    fn(a);
  }
}

BENCHMARK(BM_PassObject);
BENCHMARK(BM_PassRValueRef);

BENCHMARK_MAIN();
