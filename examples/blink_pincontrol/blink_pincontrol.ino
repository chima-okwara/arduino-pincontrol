#include "pincontrol.hpp"

outputPin led(13);

void setup()
{
    led.set();
}

void loop()
{
    led.toggle();
    DELAY(1000);
}
