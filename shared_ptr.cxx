#include <iostream>
#include <stack>
#include <vector>
#include <memory>
#include <chrono>
#include <atomic>
#include <boost/lockfree/stack.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include "benchmark/benchmark.h"

using namespace std;

class TimeLog {
public:
  TimeLog(const string &action, shared_ptr<TimeLog> prev = nullptr)
    : time_(chrono::system_clock::now()), action_(action), prev_(prev)
  {}

  int64_t dump()
  {
    if(prev_) {
      auto n = std::chrono::duration_cast<std::chrono::nanoseconds>(
                 time_ - prev_->time_)
                 .count();
      return n + prev_->dump();
    }

    return 0;
  }

  chrono::system_clock::time_point time_;

private:
  string action_;
  shared_ptr<TimeLog> prev_;
};

void endA(shared_ptr<TimeLog> log)
{
  auto log3 = make_shared<TimeLog>("end", log);
  log3->dump();
}

void workA(shared_ptr<TimeLog> log)
{
  auto log2 = make_shared<TimeLog>("work", log);
  endA(log2);
}

void masterA()
{
  auto log = make_shared<TimeLog>("master");
  for(int i = 0; i < 10; i++) {
    workA(log);
  }
}

static void BM_SharedPtr(benchmark::State &state)
{
  for(auto _ : state) {
    masterA();
  }
}

BENCHMARK(BM_SharedPtr);

enum Action { End, Work, Master };

struct TimePoint {
  TimePoint()
  {}
  TimePoint(int64_t id, Action action)
    : id_(id), action_(action), time_(chrono::system_clock::now())
  {}

  int64_t id_;
  Action action_;
  chrono::system_clock::time_point time_;
};

class Tracer {
public:
  Tracer() : que_(256), id_(1)
  {
    //que_.reserve(256);
  }

  int64_t getID()
  {
    return id_++;
  }

  void push(const TimePoint &tp)
  {
    //que_.unsynchronized_push(tp);
    //que_.push(tp);
    que_.bounded_push(tp);
    //que_.push_back(tp);
  }

private:
  boost::lockfree::stack<TimePoint> que_;
  //boost::lockfree::queue<TimePoint> que_;
  //boost::lockfree::spsc_queue<TimePoint> que_;
  //std::vector<TimePoint> que_;
  int64_t id_;
};

void endB(Tracer &tracer, int64_t id)
{
  auto tp = TimePoint(id, End);
  tracer.push(tp);
}

void workB(Tracer &tracer, int64_t id)
{
  auto tp = TimePoint(id, Work);
  tracer.push(tp);
  endB(tracer, id);
}

void masterB()
{
  Tracer tracer;
  for(int i = 0; i < 10; i++) {
    auto id = tracer.getID();
    auto tp = TimePoint(id, Master);
    tracer.push(tp);
    workB(tracer, id);
  }
}

static void BM_Lockfree(benchmark::State &state)
{
  for(auto _ : state) {
    masterB();
  }
}

BENCHMARK(BM_Lockfree);

BENCHMARK_MAIN();
