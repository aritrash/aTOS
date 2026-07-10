#include "loader/loader.hpp"

#include <Arduino.h>

#include "atos/version.hpp"
#include "console/console.hpp"
#include "protocol/protocol.hpp"
#include "loader/board.hpp"
#include "loader/cpu.hpp"

namespace
{
    constexpr unsigned SPLASH_DELAY_MS = 2000;

    void print_banner()
    {
        console::println("====================================================");
        console::println("                 aTLoader v0.1.0");
        console::println("====================================================");
        console::newline();
    }
}

void loader::boot()
{
    protocol::enter_splash_mode();
    delay(SPLASH_DELAY_MS);
    protocol::enter_console_mode();
    console::clear();
    print_banner();
    console::println("Discovering Hardware...");
    console::newline();
    board::discover();
    const loader::cpu::CpuInfo cpu =
        loader::cpu::discover();

    console::println("CPU");
    console::println("---");

    console::printf(
        "Manufacturer : %s",
        cpu.manufacturer);

    console::printf(
        "Architecture : %s",
        cpu.architecture);

    console::printf(
        "Model        : %s",
        cpu.model);

    console::printf(
        "Frequency    : %u MHz",
        cpu.frequency_mhz);

    console::printf(
        "Cores        : %u",
        cpu.cores);

    console::newline();
    console::println("Hardware discovery complete.");
    console::newline();
    console::println("CPU Test");
    console::println("--------");

    console::print("Testing CPU");
    loader::cpu::CpuTestResult cpu_test =
        cpu::test(cpu);
    console::println(" PASS");

    for (std::uint8_t i = 0;
        i < cpu_test.tested_cores;
        ++i)
    {
        console::printf(
            "Core %u ........ %s",
            i,
            cpu_test.core_pass[i] ? "PASS" : "FAIL");
    }

    console::printf(
        "Overall ....... %s",
        cpu_test.overall_pass ? "PASS" : "FAIL");

    console::newline();
}