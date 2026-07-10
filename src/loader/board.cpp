#include "loader/board.hpp"

#include "console/console.hpp"

namespace
{
    constexpr const char* MANUFACTURER =
        "Espressif";

    constexpr const char* BOARD =
        "ESP32 Dev Module";

    constexpr const char* REVISION =
        "1.0";
}

void loader::board::discover()
{
    console::println("Board");
    console::println("-----");

    console::printf(
        "Manufacturer : %s",
        MANUFACTURER);

    console::printf(
        "Board        : %s",
        BOARD);

    console::printf(
        "Revision     : %s",
        REVISION);

    console::newline();
}