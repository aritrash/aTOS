#include <Arduino.h>

#include "loader/loader.hpp"
#include "protocol/protocol.hpp"

void setup()
{
    protocol::initialize();
    protocol::hello();
    loader::boot();
}

void loop()
{
}