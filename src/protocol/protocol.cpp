#include "protocol/protocol.hpp"

#include <Arduino.h>

#include "platform/platform.hpp"

namespace
{
    constexpr std::uint8_t SYNC = 0xA5;
    constexpr std::uint8_t HELLO = 0x01;
    constexpr std::uint8_t PROTOCOL_VERSION = 0x01;
}

void protocol::initialize()
{
    Serial.begin(115200);
    delay(500);
}

void protocol::hello()
{
    Serial.write(SYNC);
    Serial.write(HELLO);
    Serial.write(PROTOCOL_VERSION);
    Serial.write(
        static_cast<std::uint8_t>(
            platform::machine()));
}

void protocol::enter_splash_mode()
{
    send_command("SHOW_SPLASH");
}

void protocol::enter_console_mode()
{
    send_command("CONSOLE");
}

void protocol::send_command(
    const char* command)
{
    Serial.println(command);
}