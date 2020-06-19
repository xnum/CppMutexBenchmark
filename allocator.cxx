#include <vector>
#include "benchmark/benchmark.h"
#include "tbb/cache_aligned_allocator.h"

using namespace std;

struct Node {
  int32_t ID;
  int32_t unused[7];
  int32_t key;
  std::string unuseds[3];
  int32_t value;
  Node()
  {
    static int32_t id = 1;
    ID = id;
    key = id;
    value = id;
    id++;
  }
};

static void BM_CacheAlignAllocator(benchmark::State &state)
{
  vector<Node, tbb::cache_aligned_allocator<Node>> vec(8192);
  for(auto _ : state) {
    int sum = 0;
    for(const auto &it : vec) {
      if(it.key % 2 == 0)
        sum += it.value;
    }
  }
}

static void BM_DefaultAllocator(benchmark::State &state)
{
  vector<Node> vec(8192);
  for(auto _ : state) {
    int sum = 0;
    for(const auto &it : vec) {
      if(it.key % 2 == 0)
        sum += it.value;
    }
  }
}

BENCHMARK(BM_CacheAlignAllocator);
BENCHMARK(BM_DefaultAllocator);

BENCHMARK_MAIN();
