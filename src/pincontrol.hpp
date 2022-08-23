#ifndef PINCONTROL
#define PINCONTROL

#include <Arduino.h>
#include <stdint.h>
#include "pincontrolDefinitions.hpp"
#include "wiring_private.h"
#include "pins_arduino.h"

class pin
{
public:
  pin() = default;
  explicit pin(const uint8_t &ArduinoPin, const uint8_t &Mode = INPUT);

  bool set();
  bool write(const uint8_t &value);
  uint8_t read(void);


protected:
  bool set(const uint8_t &pin, const uint8_t &mode);
  uint8_t oldSREG { };
  uint8_t bit { }, port { }, _pin;
  volatile uint8_t *reg { }, *out { };
  bool exists { };

  uint8_t getPort() const { return (port); }
  uint8_t getBit() const { return (bit); }
  volatile uint8_t *getReg() const { return (reg); }
  volatile uint8_t *getOut() const { return (out); }
  uint8_t _mode = 0;
};

class inputPin : public virtual pin
{
public:
  using pin::pin;
  inputPin() = default;
  explicit inputPin(const uint8_t &ArduinoPin):pin(ArduinoPin, INPUT) {  }
  uint16_t analogueRead(void);

  bool pullUp(const uint8_t &value) { return(write(value)); }
};


class outputPin : public virtual pin
{
public:
  using pin::pin;
  outputPin() = default;
  explicit outputPin(const uint8_t &ArduinoPin = LED_BUILTIN):pin(ArduinoPin, OUTPUT) {  }

  bool toggle(void);
};

#endif
