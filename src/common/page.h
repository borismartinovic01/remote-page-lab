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