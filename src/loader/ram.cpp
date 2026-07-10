#include "loader/ram.hpp"

#include <Arduino.h>

#include <cstdlib>
#include <cstring>

namespace loader::ram
{
    RamInfo discover()
    {
        RamInfo info{};

        info.total_heap = ESP.getHeapSize();
        info.free_heap = ESP.getFreeHeap();
        info.minimum_free_heap = ESP.getMinFreeHeap();
        info.largest_block = ESP.getMaxAllocHeap();

        return info;
    }

    RamTestResult test(const RamInfo&)
    {
        RamTestResult result{};

        constexpr std::size_t TEST_SIZE = 4096;

        std::uint8_t* buffer =
            static_cast<std::uint8_t*>(
                std::malloc(TEST_SIZE));

        result.allocation_pass =
            (buffer != nullptr);

        if (!result.allocation_pass)
        {
            result.write_pass = false;
            result.read_pass = false;
            result.overall_pass = false;

            return result;
        }

        std::memset(
            buffer,
            0xAA,
            TEST_SIZE);

        result.write_pass = true;

        result.read_pass = true;

        for (std::size_t i = 0;
             i < TEST_SIZE;
             ++i)
        {
            if (buffer[i] != 0xAA)
            {
                result.read_pass = false;
                break;
            }
        }

        std::free(buffer);

        result.overall_pass =
            result.allocation_pass &&
            result.write_pass &&
            result.read_pass;

        return result;
    }
}