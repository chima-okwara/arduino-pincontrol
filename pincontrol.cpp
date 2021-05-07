#include <Arduino.h>
#include <stdint.h>
#include "pincontrol.hpp"

pin::pin(const uint8_t &pin, const uint8_t &mode)
{
  set(pin, mode);
}

void pin::set(const uint8_t &pin, const uint8_t &mode)
{
  port = digitalPinToPort(pin);
  exists = EXIST(port);
  if (exists)
  {
    reg = portModeRegister(port);
    out = portOutputRegister(port);

    bit = digitalPinToBitMask(pin);
    _mode = mode;
    set();
  }

  else;
}

void pin::set()
{
  if(exists)
  {
    if(_mode == INPUT)
    {
      oldSREG = SREG;
      cli();
      *reg &= ~bit;
      *out &= ~bit;
      SREG = oldSREG;
    }
    else if(_mode == OUTPUT)
    {
      oldSREG = SREG;
      cli();
      *reg |= bit;
      SREG = oldSREG;
    }
  }

  else;
}

uint8_t pin::read()
{
  if(exists)
    return((*portInputRegister(port) & bit) ? HIGH:LOW);
  else
    return NOPORT;
}

void pin::write(const uint8_t &value)
{
  if (exists)
  {
    switch (value)
    {
      case (LOW):
      {
        oldSREG =SREG;
        *out &= ~bit;
        SREG = oldSREG;
        break;
      }

      case HIGH:
      {
        oldSREG = SREG;
        *out |= bit;
        SREG = oldSREG;
        break;
      }
      default:
      {
        break;
      }
    }
  }

  else;
}

void outputPin::toggle()
{
  oldSREG = SREG;
  *out ^= bit;
  SREG = oldSREG;
}
