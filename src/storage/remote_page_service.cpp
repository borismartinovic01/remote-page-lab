#include "storage/remote_page_service.h"
#include <chrono>
#include <thread>

namespace storage {
    RemotePageService::RemotePageService(RemotePageServiceConfig cfg) {
        latency = cfg.latency;
    }

    storage::Page RemotePageService::Fetch(storage::PageId pageId) {
        std::this_thread::sleep_for(std::chrono::microseconds(latency));

        storage::Page newPage{};

        for(size_t i = 0; i < newPage.buffer.size(); ++i) {
            newPage.buffer[i] = static_cast<std::byte>(
                (pageId * 31 + i * 17) % 256
            );
        }

        ++fetchCount;

        return newPage;
    }

    int RemotePageService::GetFetchCount() {
        return fetchCount;
    }

    int RemotePageService::GetBytesServed() {
        return fetchCount * storage::config::kPageSize;
    }
}