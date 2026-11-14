#pragma once
#include <common/page.h>
#include <common/page_id.h>
#include <atomic>

namespace storage {
    class PageService{
        public:
            virtual storage::Page Fetch(storage::PageId pageId) = 0;
            virtual int GetFetchCount() const = 0;
            virtual int GetBytesServed() const = 0;
            virtual ~PageService() = default;
    };


    struct RemotePageServiceConfig {
        std::chrono::microseconds latency;
    };


    class RemotePageService: public PageService{
        public:
            RemotePageService(RemotePageServiceConfig cfg);
            storage::Page Fetch(storage::PageId pageId);
            int GetFetchCount();
            int GetBytesServed();
        private:
            std::atomic<int> fetchCount;
            std::chrono::microseconds latency;
    };
}