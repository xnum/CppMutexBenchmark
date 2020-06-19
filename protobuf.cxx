#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <unordered_map>
#include <shared_mutex>
#include "benchmark/benchmark.h"
#include "protos/service.pb.cc"

using namespace std;
using order::OrderMessage;

string a = "aaaaaaaaaaaaaaaaaaaaaaa";
string b = "bbbbbbbbbbbbbbbbbbbbbbb";
string c = "ccccccccccccccccccccccc";

static void BM_Set(benchmark::State &state)
{
  for(auto _ : state) {
    OrderMessage msg;
    msg.set_account(a);
    msg.set_exchange(b);
    msg.set_symbol(c);

    string result;
    msg.SerializeToString(&result);
  }
}

static void BM_SetAllocated(benchmark::State &state)
{
  for(auto _ : state) {
    OrderMessage msg;
    msg.set_allocated_account(&a);
    msg.set_allocated_exchange(&b);
    msg.set_allocated_symbol(&c);

    string result;
    msg.SerializeToString(&result);

    msg.release_account();
    msg.release_exchange();
    msg.release_symbol();
  }
}

BENCHMARK(BM_Set);
BENCHMARK(BM_SetAllocated);

BENCHMARK_MAIN();
