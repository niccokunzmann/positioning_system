/* 
 * Positioing System
 * =================
 *
 */

#ifndef positioing_system_h
#define positioing_system_h

#include "Arduino.h"

class Morse
{
  public:
    Morse(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};

#endif // positioing_system_h