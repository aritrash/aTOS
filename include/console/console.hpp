#pragma once

namespace console
{
    void initialize();
    void clear();
    void print(const char* text);
    void println(const char* text);
    void printf(const char* format, ...);
    void newline();
}