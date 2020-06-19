#include <mutex>
#include <iostream>
#include <condition_variable>
#include <boost/lockfree/queue.hpp>
#include <queue>
#include "benchmark/benchmark.h"
#include "tbb/global_control.h"
#include "tbb/task_group.h"

using namespace std;
using namespace tbb;

struct Msg {
  int severity;
  int64_t timestamp;
  //string message;
};

class MutexQueue {
public:
  void push(const Msg &msg)
  {
    unique_lock<mutex> lk(mtx_);

    queue_.push(msg);
    cv_.notify_one();
  }

  bool pop(Msg *msg)
  {
    unique_lock<mutex> lk(mtx_);

    while(queue_.empty())
      cv_.wait(lk);
    *msg = queue_.front();
    queue_.pop();
    return true;
  }

private:
  std::mutex mtx_;
  std::condition_variable cv_;
  std::queue<Msg> queue_;
};

static void BM_LockfreeQueue(benchmark::State &state)
{
  boost::lockfree::queue<Msg> que(256);

  global_control c(global_control::max_allowed_parallelism, 8);
  task_group tg;

  for(auto _ : state) {
    tg.run([&] {
      int count = 0;
      while(count < 10000) {
        Msg msg;
        que.pop(msg);
        count++;
      }
    });

    for(int i = 0; i < 4; i++) {
      tg.run([&] {
        for(int k = 0; k < 10000 / 4; k++) {
          Msg msg;
          que.push(msg);
        }
      });
    }

    tg.wait();
  }
}

static void BM_MutexQueue(benchmark::State &state)
{
  MutexQueue que;

  global_control c(global_control::max_allowed_parallelism, 8);
  task_group tg;

  for(auto _ : state) {
    tg.run([&] {
      int count = 0;
      while(count < 10000) {
        Msg msg;
        que.pop(&msg);
        count++;
      }
    });

    for(int i = 0; i < 4; i++) {
      tg.run([&] {
        for(int k = 0; k < 10000 / 4; k++) {
          Msg msg;
          que.push(msg);
        }
      });
    }

    tg.wait();
  }
}

BENCHMARK(BM_LockfreeQueue)->UseRealTime();
BENCHMARK(BM_MutexQueue)->UseRealTime();

BENCHMARK_MAIN();
