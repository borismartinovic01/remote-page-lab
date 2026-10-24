# Milestone 1: Baseline remote page cache

## Goal

Build a small, testable system that serves fixed-size pages from a remote-page service through a bounded LRU cache. Model remote latency and record observable costs.

## Non-goals

- PostgreSQL integration or a PostgreSQL fork
- WAL, transactions, durability guarantees, crash recovery, or replication
- Persistent on-disk page storage
- Adaptive prefetching or advanced replacement algorithms
- Claims about production cloud database performance

## Component responsibilities

### `common/page.h`
Define a page identifier type and fixed-size page representation. Choose one page size and document it. Keep page identity separate from page contents.

### `storage/remote_page_service.h/.cpp`
Own the backing page map or deterministic page generator. Expose a page-fetch operation. Apply configurable artificial latency to each remote fetch. Track remote requests and bytes served. Ensure the same page ID produces stable contents during a run.

### `cache/lru_page_cache.h/.cpp`
Own a fixed number of page frames. On a hit, update recency. On a miss, fetch from the remote service and insert the page. When full, evict the least-recently-used page. Track hits and misses. Define behavior for zero capacity explicitly (prefer rejecting it during construction for this milestone).

### `metrics/latency_histogram.h/.cpp`
Collect individual measured latencies or a documented histogram representation. Provide count, min, max, mean, and p50/p95/p99. Define percentile calculation precisely and test it. For this small baseline, storing samples is acceptable; optimize memory only if measurements require it.

### `benchmark/`
Parse a small set of command-line parameters: number of requests, cache capacity, artificial remote latency, page size if configurable, workload type, and random seed. Emit machine-readable CSV or JSON results. Keep warm-up requests separate from measured requests.

### `test/`
Use a lightweight test harness initially; avoid adding a large dependency before needed. Cover deterministic unit tests for each component and a small end-to-end test.

## Suggested public concepts

These are design responsibilities, not a prescribed class implementation:
- `PageId`
- `Page`
- `RemotePageService`
- `LruPageCache`
- `LatencyHistogram` or `LatencyRecorder`
- `BenchmarkConfig`
- `BenchmarkResult`

## Invariants to protect

1. Cache occupancy never exceeds capacity.
2. A page ID appears at most once in the cache.
3. A cache hit does not call the remote service.
4. A miss calls the remote service exactly once in this single-threaded baseline.
5. A hit updates the page's recency.
6. Eviction removes the least-recently-used page.
7. Transfer-byte accounting counts bytes served by the remote service, not cache hits.
8. Latency units are consistent and documented (recommend microseconds internally).
9. Percentile results are deterministic for a fixed sample set.
10. The same workload and seed produce the same request sequence.

## Acceptance criteria

- Clean configure/build succeeds.
- All unit tests pass.
- A small end-to-end run produces internally consistent counters.
- With capacity 2 and request sequence A, B, A, C, B, the cache behavior proves that A was promoted on its hit and B is evicted when C arrives.
- Repeating the same configuration and seed produces the same logical counters.
- Setting artificial remote latency to zero is supported.
- Reported remote bytes equal remote fetch count multiplied by page size, unless the implementation explicitly supports variable-size pages.
- Benchmark output includes configuration, request count, hits, misses, remote fetches, bytes transferred, and latency distribution.
