#pragma once

#include <cstdint>

namespace loader::cpu
{
    struct CpuInfo
    {
        const char* manufacturer;
        const char* architecture;
        const char* model;
        std::uint32_t frequency_mhz;
        std::uint8_t cores;
    };

    struct CpuTestResult
    {
        bool overall_pass;
        std::uint8_t tested_cores;
        bool core_pass[8];
    };

    CpuInfo discover();
    CpuTestResult test(const CpuInfo& cpu);
}