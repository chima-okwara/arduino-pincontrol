#include "pincontrol.hpp"

outputPin led(13);

void setup()
{

}

void loop()
{
    led.toggle();
    DELAY(1000);
}
