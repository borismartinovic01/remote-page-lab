cmake_minimum_required(VERSION 3.16)
project(RemotePageLab VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(REMOTEPAGELAB_ENABLE_WARNINGS "Enable strict compiler warnings" ON)
option(REMOTEPAGELAB_BUILD_TESTS "Build tests" ON)

add_library(remotepagelab_options INTERFACE)
if(REMOTEPAGELAB_ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(remotepagelab_options INTERFACE /W4)
    else()
        target_compile_options(remotepagelab_options INTERFACE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow
        )
    endif()
endif()

add_library(remotepagelab_core
    src/cache/lru_page_cache.cpp
    src/storage/remote_page_service.cpp
    src/metrics/latency_histogram.cpp
)
target_include_directories(remotepagelab_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(remotepagelab_core PUBLIC remotepagelab_options)

add_executable(remotepagelab_bench
    src/benchmark/main.cpp
)
target_link_libraries(remotepagelab_bench PRIVATE remotepagelab_core)

if(REMOTEPAGELAB_BUILD_TESTS)
    enable_testing()
    add_executable(remotepagelab_tests
        test/test_main.cpp
        test/test_lru_page_cache.cpp
        test/test_remote_page_service.cpp
        test/test_latency_histogram.cpp
    )
    target_link_libraries(remotepagelab_tests PRIVATE remotepagelab_core)
    add_test(NAME remotepagelab_tests COMMAND remotepagelab_tests)
endif()
