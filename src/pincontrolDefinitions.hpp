#ifndef PINCONTROLDEFS
#define PINCONTROLDEFS

#include <Arduino.h>
#define NOEXIST(x) (((x)==NOT_A_PIN)?1:0)
#define EXIST(x) (((x)==NOT_A_PIN)?0:1)
#define ON HIGH
#define OFF LOW
#define NOPORT -1
#define DELAY(x) (_delay_ms(x))

#define getPort(x) (digitalPinToPort(x))
#define getBit(x) (digitalPinToBitMask(x))
#define getPortReg(x) (portModeRegister(x))
#define getOutReg(x) (portOutputRegister(x))
#define getInReg(x) (portInputRegister(x))


#endif
