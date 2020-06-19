#include <boost/thread/shared_mutex.hpp>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include "benchmark/benchmark.h"
#include "tbb/concurrent_vector.h"
#include "tbb/global_control.h"
#include "tbb/queuing_rw_mutex.h"
#include "tbb/task_group.h"

using std::vector;
using namespace tbb;

static void BM_TBBRWMutexReadOnlyWithStdVector(benchmark::State &state)
{
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  vector<int> vec(1024, 1024);
  queuing_rw_mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 4; i++) {
      tg.run([&] {
        int sum = 0;
        queuing_rw_mutex::scoped_lock lk(mtx, false);
        for(int j = 0; j < vec.size(); j++) {
          sum += vec[j];
        }
      });
    }

    tg.wait();
  }
}
static void BM_TBBRWMutexWithStdVector(benchmark::State &state)
{
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  vector<int> vec(1024, 1024);
  queuing_rw_mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 3; i++) {
      tg.run([&] {
        int sum = 0;
        queuing_rw_mutex::scoped_lock lk(mtx, false);
        for(int j = 0; j < vec.size(); j++) {
          sum += vec[j];
        }
      });
    }

    tg.run([&] {
      queuing_rw_mutex::scoped_lock lk(mtx, true);
      for(int j = 0; j < vec.size(); j++) {
        vec[j]++;
      }
    });

    tg.wait();
  }
}

static void BM_BoostSharedMutexUpgradeWithStdVector(benchmark::State &state)
{
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  vector<int> vec(1024, 1024);
  boost::shared_mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 4; i++) {
      tg.run([&] {
        int sum = 0;
        boost::upgrade_lock<boost::shared_mutex> lk(mtx);
        for(int j = 0; j < vec.size(); j++) {
          sum += vec[j];
        }
      });
    }

    tg.wait();
  }
}
static void BM_BoostSharedMutexReadOnlyWithStdVector(benchmark::State &state)
{
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  vector<int> vec(1024, 1024);
  boost::shared_mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 4; i++) {
      tg.run([&] {
        int sum = 0;
        boost::shared_lock<boost::shared_mutex> lk(mtx);
        for(int j = 0; j < vec.size(); j++) {
          sum += vec[j];
        }
      });
    }

    tg.wait();
  }
}
static void BM_BoostSharedMutexWithStdVector(benchmark::State &state)
{
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  vector<int> vec(1024, 1024);
  boost::shared_mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 3; i++) {
      tg.run([&] {
        int sum = 0;
        boost::shared_lock<boost::shared_mutex> lk(mtx);
        for(int j = 0; j < vec.size(); j++) {
          sum += vec[j];
        }
      });
    }

    tg.run([&] {
      boost::unique_lock<boost::shared_mutex> lk(mtx);
      for(int j = 0; j < vec.size(); j++) {
        vec[j]++;
      }
    });

    tg.wait();
  }
}

static void BM_ConcurrentVector(benchmark::State &state)
{
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  concurrent_vector<int> vec(1024, 1024);
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 3; i++) {
      tg.run([&] {
        int sum = 0;
        for(int j = 0; j < vec.size(); j++) {
          sum += vec[j];
        }
      });
    }

    tg.run([&] {
      for(int j = 0; j < vec.size(); j++) {
        vec[j]++;
      }
    });

    tg.wait();
  }
}

static void BM_StdSharedMutexReadOnlyWithStdVector(benchmark::State &state)
{
  using namespace std;
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  vector<int> vec(1024, 1024);
  shared_mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 4; i++) {
      tg.run([&] {
        int sum = 0;
        shared_lock<shared_mutex> lk(mtx);
        for(int j = 0; j < vec.size(); j++) {
          sum += vec[j];
        }
      });
    }

    tg.wait();
  }
}

static void BM_StdSharedMutexWithStdVector(benchmark::State &state)
{
  using namespace std;
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  vector<int> vec(1024, 1024);
  shared_mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 3; i++) {
      tg.run([&] {
        int sum = 0;
        shared_lock<shared_mutex> lk(mtx);
        for(int j = 0; j < vec.size(); j++) {
          sum += vec[j];
        }
      });
    }

    tg.run([&] {
      unique_lock<shared_mutex> lk(mtx);
      for(int j = 0; j < vec.size(); j++) {
        vec[j]++;
      }
    });

    tg.wait();
  }
}

static void BM_StdMutexWithStdVector(benchmark::State &state)
{
  using namespace std;
  global_control c(global_control::max_allowed_parallelism, state.range(0));
  task_group tg;

  vector<int> vec(1024, 1024);
  mutex mtx;
  for(auto _ : state) {
    // reader.
    for(int i = 0; i < 3; i++) {
      tg.run([&] {
        unique_lock<mutex> lk(mtx);
        int sum = 0;
        for(const auto &i : vec) {
          sum += i;
        }
      });
    }

    tg.run([&] {
      unique_lock<mutex> lk(mtx);
      for(auto &i : vec) {
        i++;
      }
    });

    tg.wait();
  }
}

BENCHMARK(BM_TBBRWMutexReadOnlyWithStdVector)
  ->DenseRange(1, 6, 1)
  ->UseRealTime();
BENCHMARK(BM_TBBRWMutexWithStdVector)->DenseRange(1, 6, 1)->UseRealTime();
BENCHMARK(BM_BoostSharedMutexUpgradeWithStdVector)
  ->DenseRange(1, 6, 1)
  ->UseRealTime();
BENCHMARK(BM_BoostSharedMutexReadOnlyWithStdVector)
  ->DenseRange(1, 6, 1)
  ->UseRealTime();
BENCHMARK(BM_BoostSharedMutexWithStdVector)->DenseRange(1, 6, 1)->UseRealTime();
BENCHMARK(BM_ConcurrentVector)->DenseRange(1, 6, 1)->UseRealTime();
BENCHMARK(BM_StdSharedMutexReadOnlyWithStdVector)
  ->DenseRange(1, 6, 1)
  ->UseRealTime();
BENCHMARK(BM_StdSharedMutexWithStdVector)->DenseRange(1, 6, 1)->UseRealTime();
BENCHMARK(BM_StdMutexWithStdVector)->DenseRange(1, 6, 1)->UseRealTime();

BENCHMARK_MAIN();
