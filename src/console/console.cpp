#include "console/console.hpp"
#include <cstdio>
#include <cstdarg>
#include <cstdio>
#include "protocol/protocol.hpp"

namespace
{
    constexpr char CLEAR_COMMAND[] = "CLEAR";
    constexpr char PRINT_PREFIX[] = "PRINT ";
}

void console::initialize()
{
}

void console::clear()
{
    protocol::send_command(CLEAR_COMMAND);
}

void console::print(const char* text)
{
    char buffer[256];

    std::snprintf(
        buffer,
        sizeof(buffer),
        "%s%s",
        PRINT_PREFIX,
        text);

    protocol::send_command(buffer);
}

void console::println(const char* text)
{
    print(text);
}

void console::newline()
{
    print("");
}

void console::printf(
    const char* format,
    ...)
{
    char buffer[256];

    va_list args;

    va_start(args, format);

    vsnprintf(
        buffer,
        sizeof(buffer),
        format,
        args);

    va_end(args);

    print(buffer);
}