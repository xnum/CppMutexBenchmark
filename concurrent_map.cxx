#include <boost/thread/shared_mutex.hpp>
#include <mutex>
#include <shared_mutex>
#include "benchmark/benchmark.h"
#include "tbb/concurrent_unordered_map.h"
#include "tbb/global_control.h"
#include "tbb/queuing_rw_mutex.h"
#include "tbb/task_group.h"

using namespace tbb;

static void BM_TBBConcurrentUnorderedMap(benchmark::State &state)
{
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  tbb::concurrent_unordered_map<int32_t, int64_t> m;
  for(int i = 0; i < 1024; i++) {
    m[i] = i + 10000;
  }

  for(auto _ : state) {
    for(int i = 0; i < 4; i++) {
      tg.run([&] {
        for(int j = 0; j < 1024; j++) {
          m[j]++;
        }
      });
    }

    tg.wait();
  }
}

static void BM_TBBRWMutexWithStdUnorderedMap(benchmark::State &state)
{
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  std::unordered_map<int32_t, int64_t> m;
  for(int i = 0; i < 1024; i++) {
    m[i] = i + 10000;
  }

  queuing_rw_mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 4; i++) {
      tg.run([&] {
        for(int j = 0; j < 1024; j++) {
          queuing_rw_mutex::scoped_lock lk(mtx, true);
          m[j]++;
        }
      });
    }

    tg.wait();
  }
}

BENCHMARK(BM_TBBConcurrentUnorderedMap)->DenseRange(1, 6, 1)->UseRealTime();
BENCHMARK(BM_TBBRWMutexWithStdUnorderedMap)->DenseRange(1, 6, 1)->UseRealTime();

BENCHMARK_MAIN();
