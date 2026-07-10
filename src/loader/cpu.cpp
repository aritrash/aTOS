#include "loader/cpu.hpp"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace loader::cpu
{
    namespace
    {
        volatile bool core_completed[8];

        void core_test_task(void* parameter)
        {
            const std::uint32_t core =
                static_cast<std::uint32_t>(
                    reinterpret_cast<std::uintptr_t>(parameter));

            core_completed[core] = true;

            vTaskDelete(nullptr);
        }
    }

    CpuInfo discover()
    {
        CpuInfo info;

        info.manufacturer = "Espressif";
        info.architecture = "Xtensa LX6";
        info.model = "ESP32";
        info.frequency_mhz = ESP.getCpuFreqMHz();
        info.cores = ESP.getChipCores();

        return info;
    }

    CpuTestResult test(const CpuInfo& cpu)
    {
        CpuTestResult result{};

        result.overall_pass = true;
        result.tested_cores = cpu.cores;

        for (std::uint8_t i = 0; i < 8; ++i)
        {
            result.core_pass[i] = false;
            core_completed[i] = false;
        }

        for (std::uint8_t core = 0;
             core < cpu.cores && core < 8;
             ++core)
        {
            BaseType_t status =
                xTaskCreatePinnedToCore(
                    core_test_task,
                    "cpu_test",
                    2048,
                    reinterpret_cast<void*>(
                        static_cast<std::uintptr_t>(core)),
                    1,
                    nullptr,
                    core);

            if (status != pdPASS)
            {
                result.overall_pass = false;
                continue;
            }
        }

        constexpr TickType_t TIMEOUT =
            pdMS_TO_TICKS(100);

        TickType_t start = xTaskGetTickCount();

        while ((xTaskGetTickCount() - start) < TIMEOUT)
        {
            bool complete = true;

            for (std::uint8_t core = 0;
                 core < cpu.cores;
                 ++core)
            {
                if (!core_completed[core])
                {
                    complete = false;
                    break;
                }
            }

            if (complete)
                break;

            vTaskDelay(pdMS_TO_TICKS(1));
        }

        for (std::uint8_t core = 0;
             core < cpu.cores;
             ++core)
        {
            result.core_pass[core] = core_completed[core];

            if (!core_completed[core])
                result.overall_pass = false;
        }

        return result;
    }
}