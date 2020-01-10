thread-safe container benchmark
===============================

# Assumption

3 reader, 1 writer (75%R) or 4 reader (99% R)

# Result

```
2020-01-10 03:34:11
Running ./mybenchmark
Run on (6 X 3597.92 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x3)
  L1 Instruction 32 KiB (x3)
  L2 Unified 256 KiB (x3)
  L3 Unified 8192 KiB (x1)
Load Average: 0.14, 0.04, 0.01
-----------------------------------------------------------------------------------------------
Benchmark                                                     Time             CPU   Iterations
-----------------------------------------------------------------------------------------------
BM_TBBRWMutexReadOnlyWithStdVector/1/real_time              497 ns          497 ns      1395400
BM_TBBRWMutexReadOnlyWithStdVector/2/real_time              562 ns          562 ns      1200833
BM_TBBRWMutexReadOnlyWithStdVector/3/real_time              694 ns          694 ns       999577
BM_TBBRWMutexReadOnlyWithStdVector/4/real_time              754 ns          754 ns      1052812
BM_TBBRWMutexReadOnlyWithStdVector/5/real_time              766 ns          766 ns      1040653
BM_TBBRWMutexReadOnlyWithStdVector/6/real_time              842 ns          842 ns       907788
BM_TBBRWMutexWithStdVector/1/real_time                      834 ns          834 ns       832973
BM_TBBRWMutexWithStdVector/2/real_time                     1064 ns         1064 ns       674947
BM_TBBRWMutexWithStdVector/3/real_time                     1266 ns         1266 ns       582767
BM_TBBRWMutexWithStdVector/4/real_time                     1325 ns         1325 ns       529704
BM_TBBRWMutexWithStdVector/5/real_time                     1755 ns         1755 ns       432959
BM_TBBRWMutexWithStdVector/6/real_time                     1877 ns         1848 ns       418686
BM_BoostSharedMutexUpgradeWithStdVector/1/real_time         967 ns          967 ns       699845
BM_BoostSharedMutexUpgradeWithStdVector/2/real_time        1207 ns         1206 ns       580093
BM_BoostSharedMutexUpgradeWithStdVector/3/real_time        2212 ns         2148 ns       310692
BM_BoostSharedMutexUpgradeWithStdVector/4/real_time        3397 ns         3267 ns       193411
BM_BoostSharedMutexUpgradeWithStdVector/5/real_time        4255 ns         4064 ns       162626
BM_BoostSharedMutexUpgradeWithStdVector/6/real_time        5045 ns         4818 ns       132455
BM_BoostSharedMutexReadOnlyWithStdVector/1/real_time        945 ns          945 ns       722967
BM_BoostSharedMutexReadOnlyWithStdVector/2/real_time       1115 ns         1114 ns       630878
BM_BoostSharedMutexReadOnlyWithStdVector/3/real_time       1251 ns         1250 ns       556841
BM_BoostSharedMutexReadOnlyWithStdVector/4/real_time       1414 ns         1412 ns       500023
BM_BoostSharedMutexReadOnlyWithStdVector/5/real_time       1575 ns         1546 ns       469274
BM_BoostSharedMutexReadOnlyWithStdVector/6/real_time       1733 ns         1728 ns       427882
BM_BoostSharedMutexWithStdVector/1/real_time               1308 ns         1308 ns       527286
BM_BoostSharedMutexWithStdVector/2/real_time               1865 ns         1864 ns       372503
BM_BoostSharedMutexWithStdVector/3/real_time               4051 ns         3972 ns       162851
BM_BoostSharedMutexWithStdVector/4/real_time               6836 ns         6656 ns       101692
BM_BoostSharedMutexWithStdVector/5/real_time               9334 ns         9127 ns        71550
BM_BoostSharedMutexWithStdVector/6/real_time               9920 ns         9742 ns        69931
BM_ConcurrentVector/1/real_time                           60743 ns        60742 ns        11095
BM_ConcurrentVector/2/real_time                           34496 ns        34495 ns        20418
BM_ConcurrentVector/3/real_time                           34523 ns        34523 ns        21392
BM_ConcurrentVector/4/real_time                           28096 ns        27940 ns        27367
BM_ConcurrentVector/5/real_time                           27325 ns        27325 ns        25378
BM_ConcurrentVector/6/real_time                           29884 ns        29876 ns        23474
BM_StdSharedMutexReadOnlyWithStdVector/1/real_time          450 ns          450 ns      1559657
BM_StdSharedMutexReadOnlyWithStdVector/2/real_time          551 ns          551 ns      1293665
BM_StdSharedMutexReadOnlyWithStdVector/3/real_time          589 ns          589 ns      1125182
BM_StdSharedMutexReadOnlyWithStdVector/4/real_time          620 ns          620 ns      1144650
BM_StdSharedMutexReadOnlyWithStdVector/5/real_time          703 ns          703 ns      1000609
BM_StdSharedMutexReadOnlyWithStdVector/6/real_time          723 ns          723 ns      1022659
BM_StdSharedMutexWithStdVector/1/real_time                  802 ns          802 ns       834069
BM_StdSharedMutexWithStdVector/2/real_time                  930 ns          930 ns       791791
BM_StdSharedMutexWithStdVector/3/real_time                 1065 ns         1065 ns       677361
BM_StdSharedMutexWithStdVector/4/real_time                 1076 ns         1076 ns       661860
BM_StdSharedMutexWithStdVector/5/real_time                 1237 ns         1237 ns       560336
BM_StdSharedMutexWithStdVector/6/real_time                 1351 ns         1351 ns       525693
BM_StdMutexWithStdVector/1/real_time                        789 ns          789 ns       843262
BM_StdMutexWithStdVector/2/real_time                        882 ns          882 ns       788578
BM_StdMutexWithStdVector/3/real_time                        985 ns          984 ns       714691
BM_StdMutexWithStdVector/4/real_time                       1105 ns         1104 ns       648823
BM_StdMutexWithStdVector/5/real_time                       1202 ns         1202 ns       512034
BM_StdMutexWithStdVector/6/real_time                       1380 ns         1377 ns       523132
```

3R 1W

| concurrency | std::mutex | std::shared_mutex | boost::shared_mutex | tbb::queuing_rw_mutex | tbb::concurrent_vector |
| ----------- | ---------- | ----------------- | ------------------- | --------------------- | ---------------------- |
|      1      |     789    |        802        |        1308         |          834          |        60742           |
|      2      |     882    |        930        |        1864         |         1064          |        34495           |
|      3      |     984    |       1065        |        3972         |         1266          |        34523           |
|      4      |    1104    |       1076        |        6656         |         1325          |        27940           |
|      5      |    1202    |       1237        |        9127         |         1755          |        27325           |
|      6      |    1377    |       1351        |        9742         |         1848          |        29876           |

4R

| concurrency | std::shared_mutex | boost::shared_mutex | tbb::queuing_rw_mutex | boost::shared_mutex (upgrade_lock) |
| ----------- | ----------------- | ------------------- | --------------------- | ---------------------------------- |
|      1      |        450        |         945         |          497          |              967                   |
|      2      |        551        |        1114         |          562          |             1206                   |
|      3      |        589        |        1250         |          694          |             2148                   |
|      4      |        620        |        1412         |          754          |             3267                   |
|      5      |        703        |        1546         |          766          |             4064                   |
|      6      |        723        |        1728         |          842          |             4818                   |

# Conclusion

`boost::upgrade_lock` is slow.

Using `shared_lock` or `unique_lock` on simple read/write operation.

`tbb::concurrent_vector` is extermely slow due to fine-grained lock.

`tbb::xxx_mutex` -> spinlock-based implementation.
