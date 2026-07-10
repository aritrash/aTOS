#pragma once

#include <cstdint>

enum class MachineType : std::uint8_t
{
    Unknown = 0x00,

    Esp32 = 0x01,
    Esp8266 = 0x02,

    Stm32F103 = 0x10,
    Stm32F407 = 0x11,

    Teensy31 = 0x20,
    Teensy40 = 0x21,

    RaspberryPi3 = 0x30,
    RaspberryPi4 = 0x31,
    RaspberryPi5 = 0x32,
    RaspberryPiCm4 = 0x33,
    RaspberryPiCm5 = 0x34
};