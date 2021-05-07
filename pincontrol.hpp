#include <Arduino.h>
#include <stdint.h>

#define NOEXIST(x) (((x)==NOT_A_PIN)?1:0)
#define EXIST(x) (((x)==NOT_A_PIN)?0:1)
#define ON HIGH
#define OFF LOW
#define NOPORT -1
#define DELAY(x) (_delay_ms(x))

class pin
{
public:
  pin(const uint8_t &ArduinoPin, const uint8_t &Mode = INPUT);
  pin() = default;

  void set();
  void set(const uint8_t &pin, const uint8_t &mode);
  void write(const uint8_t &value);
  uint8_t read(void);

protected:
  uint8_t oldSREG { };
  uint8_t bit { }, port { };
  volatile uint8_t *reg { }, *out { };
  bool exists;

  uint8_t getPort() const { return (port); }
  uint8_t getBit() const { return (bit); }
  volatile uint8_t *getReg() const { return (reg); }
  volatile uint8_t *getOut() const { return (out); }

  void setPort(uint8_t value) { port = value; }

private:
  uint8_t _mode;
};

class inputPin : public pin
{
public:
  inputPin() = default;
  inputPin(const uint8_t &ArduinoPin) { set(ArduinoPin, INPUT); }

  void pullUpRes(const uint8_t &value) { write(value); }
};


class outputPin : public pin
{
public:
  outputPin(const uint8_t & ArduinoPin) { set(ArduinoPin, OUTPUT); }
  outputPin() = default;

  void toggle(void);
};
