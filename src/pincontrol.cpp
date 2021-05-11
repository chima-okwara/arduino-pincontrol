#include <Arduino.h>
#include <stdint.h>
#include "pincontrol.hpp"
#include "pincontrolDefinitions.hpp"

pin::pin(const uint8_t &pin, const uint8_t &mode):_mode(mode)
{
  set(pin, _mode);
}

void pin::set(const uint8_t &pin, const uint8_t &mode)
{
  port = getPort(pin);
  exists = EXIST(port);
  if (exists)
  {
    reg = getPortReg(port);
    out = getOutReg(port);

    bit = getBit(pin);
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
    return((*getInReg(port) & bit) ? HIGH:LOW);
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
