#ifndef PINCONTROLDEFS
#define PINCONTROLDEFS

#include <Arduino.h>
#define NOEXIST(x) (((x)==NOT_A_PIN)?1:0)
#define EXIST(x) (((x)==NOT_A_PIN)?0:1)
#define ON HIGH
#define OFF LOW
#define NOPORT -1
#define DELAY(x) (wait(x))

#define analog_reference  DEFAULT
#define analogReference(x) (analog_reference = x)


#endif
