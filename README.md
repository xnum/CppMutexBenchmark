thread-safe container benchmark
===============================

# Assumption

3 reader, 1 writer (75%R) or 4 reader (99% R)

# Conclusion

`std::shared_mutex` is better than `boost::shared_mutex` (5%), but only supports since C++17.

`boost::upgrade_lock` is slow.

Using `boost::shared_lock` or `boost::unique_lock` on simple read/write operation.

`tbb::concurrent_vector` is extermely slow due to fine-grained lock.

`tbb::xxx_mutex` -> spinlock-based implementation.
