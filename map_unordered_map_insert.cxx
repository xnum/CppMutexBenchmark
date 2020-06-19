#include <vector>
#include <map>
#include <unordered_map>
#include "benchmark/benchmark.h"

using namespace std;

static void BM_MapInsert(benchmark::State &state)
{
  for(auto _ : state) {
    map<int, double> m;
    for(int key = 1; key <= 1000; key++) {
      m.emplace(key, 3.14);
    }
  }
}

static void BM_UnorderedMapInsert(benchmark::State &state)
{
  for(auto _ : state) {
    unordered_map<int, double> m;
    for(int key = 1; key <= 1000; key++) {
      m.emplace(key, 3.14);
    }
  }
}

static void BM_UnorderedMapInsertRehashTwoPow(benchmark::State &state)
{
  for(auto _ : state) {
    unordered_map<int, double> m;
    m.rehash(2048);
    for(int key = 1; key <= 1000; key++) {
      m.emplace(key, 3.14);
    }
  }
}

static void BM_UnorderedMapInsertRehashPrime(benchmark::State &state)
{
  for(auto _ : state) {
    unordered_map<int, double> m;
    m.rehash(2063);
    for(int key = 1; key <= 1000; key++) {
      m.emplace(key, 3.14);
    }
  }
}

BENCHMARK(BM_MapInsert);
BENCHMARK(BM_UnorderedMapInsert);
BENCHMARK(BM_UnorderedMapInsertRehashTwoPow);
BENCHMARK(BM_UnorderedMapInsertRehashPrime);

BENCHMARK_MAIN();
