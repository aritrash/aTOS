#pragma once

#include <cstdint>

namespace loader::ram
{
    struct RamInfo
    {
        std::uint32_t total_heap;
        std::uint32_t free_heap;
        std::uint32_t minimum_free_heap;
        std::uint32_t largest_block;
    };

    struct RamTestResult
    {
        bool allocation_pass;
        bool read_pass;
        bool write_pass;
        bool overall_pass;
    };

    RamInfo discover();

    RamTestResult test(const RamInfo& info);
}