#pragma once

namespace protocol
{
    void initialize();
    void hello();
    void enter_splash_mode();
    void enter_console_mode();
    void send_command(const char* command);
}