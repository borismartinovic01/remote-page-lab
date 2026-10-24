#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace storage::config {
inline constexpr std::size_t kPageSize = 8 * 1024;
}

namespace storage {
using PageBuffer = std::array<std::byte, config::kPageSize>;

struct Page {
    storage::PageBuffer buffer{};
};
}



// Milestone 1 TODO:
// - define PageId;
// - define the fixed-size page representation;
// - document page size and whether page contents are bytes or a typed structure.
//
// Keep this header independent of cache, storage, and metrics implementations.
