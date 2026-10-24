# RemotePageLab

RemotePageLab is an experimental C++ project for studying page caching and remote-storage latency in a simplified storage-disaggregated database architecture.

The first milestone establishes a reproducible baseline:
- a fixed-capacity page cache using LRU eviction;
- a remote page service with configurable artificial latency;
- cache hit/miss, transfer-byte, and latency measurements;
- a benchmark executable and unit-test target.

This is an experimental model, not a PostgreSQL implementation. The initial milestone does not model WAL, transactions, crash recovery, or distributed consistency.

## Requirements

- CMake 3.16+
- A C++17 compiler (GCC 8.5+ should be suitable)
- Make or Ninja

## Build

```sh
cmake -S . -B build
cmake --build build -j
```

## Run tests

```sh
ctest --test-dir build --output-on-failure
```

## Run the benchmark

The benchmark interface will be defined as the first milestone is implemented. The intended invocation is:

```sh
./build/remotepagelab_bench --help
```

## Suggested implementation order

1. Define page identifiers, page representation, and shared interfaces.
2. Implement the remote page service and its deterministic page contents.
3. Implement the LRU cache and its invariants.
4. Implement latency/transfer metrics.
5. Wire components into a benchmark workload.
6. Add tests for each component and for end-to-end behavior.

## Experimental principles

- Keep configuration explicit and record it with every run.
- Use deterministic workloads/seeds so comparisons are reproducible.
- Separate warm-up from measured requests.
- Report latency percentiles, not only averages.
- Compare policies under identical workload and service settings.
- Do not claim real cloud-storage performance from artificial-delay simulations.

## Repository layout

See `docs/milestone-1.md` for the planned boundaries and acceptance criteria.
