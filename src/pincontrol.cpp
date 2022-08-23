#include <Arduino.h>
#include <stdint.h>
#include "pincontrol.hpp"
#include "pincontrolDefinitions.hpp"

pin::pin(const uint8_t &pin, const uint8_t &mode):_mode(mode), _pin(pin)
{
  set(pin, _mode);
}

bool pin::set(const uint8_t &pin, const uint8_t &mode)
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
    return 1;
  }

  else
    return 0;
}

bool pin::set()
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

    else
      return 0;
    return 1;
  }

  else
    return 0;
}

uint8_t pin::read()
{
  if(exists)
    return((*portInputRegister(port) & bit) ? HIGH:LOW);
  else
    return NOPORT;
}

uint16_t inputPin::analogueRead()
{
  uint8_t low, high;
  #if defined(analogPinToChannel)
  #if defined(__AVR_ATmega32U4__)
  	if (_pin >= 18) pin -= 18; // allow for channel or pin numbers
  #endif
  	_pin = analogPinToChannel(pin);
  #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  	if (_pin >= 54) _pin -= 54; // allow for channel or pin numbers
  #elif defined(__AVR_ATmega32U4__)
  	if (_pin >= 18) _pin -= 18; // allow for channel or pin numbers
  #elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
  	if (_pin >= 24) _pin -= 24; // allow for channel or pin numbers
  #else
  	if (_pin >= 14) _pin -= 14; // allow for channel or pin numbers
  #endif

  #if defined(ADCSRB) && defined(MUX5)
  	// the MUX5 bit of ADCSRB selects whether we're reading from channels
  	// 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
  	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((_pin >> 3) & 0x01) << MUX5);
  #endif

  	// set the analog reference (high two bits of ADMUX) and select the
  	// channel (low 4 bits).  this also sets ADLAR (left-adjust result)
  	// to 0 (the default).
  #if defined(ADMUX)
  #if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  	ADMUX = (analog_reference << 4) | (_pin & 0x07);
  #else
  	ADMUX = (analog_reference << 6) | (_pin & 0x07);
  #endif
  #endif

  	// without a delay, we seem to read from the wrong channel
  	//delay(1);

  #if defined(ADCSRA) && defined(ADCL)
  	// start the conversion
  	sbi(ADCSRA, ADSC);

  	// ADSC is cleared when the conversion finishes
  	while (bit_is_set(ADCSRA, ADSC));

  	// we have to read ADCL first; doing so locks both ADCL
  	// and ADCH until ADCH is read.  reading ADCL second would
  	// cause the results of each conversion to be discarded,
  	// as ADCL and ADCH would be locked when it completed.
  	low  = ADCL;
  	high = ADCH;
  #else
  	// we dont have an ADC, return 0
  	low  = 0;
  	high = 0;
  #endif

  	// combine the two bytes
  	return (high << 8) | low;
}

bool pin::write(const uint8_t &value)
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
    return 1;
  }

  else
    return 0;
}

bool outputPin::toggle()
{
  if (_mode == OUTPUT)
  {
    oldSREG = SREG;
    *out ^= bit;
    SREG = oldSREG;
    return (1);
  }

  else
    return (0);
}
