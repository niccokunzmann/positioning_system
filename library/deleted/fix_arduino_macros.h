#ifndef fix_arduino_macros_h
#define fix_arduino_macros_h

#include "Arduino.h"

// abs

#define fix_arduino_macros_h_abs(X) abs(X)
#undef abs


#define fix_arduino_macros_h_define_abs(TYPE) TYPE abs(TYPE a) { return fix_arduino_macros_h_abs(a); };
#define declare_abs(TYPE) TYPE abs(TYPE a);

/*
// types from http://arduino.cc/en/Reference/HomePage
declare_abs(byte)
declare_abs(int)
declare_abs(word)
declare_abs(long)
declare_abs(short)
declare_abs(float)
declare_abs(float)
declare_abs(double)
*/

#undef declare_abs
#undef fix_arduino_macros_h_abs

// round

#define fix_arduino_macros_h_round(X) round(X)
#undef round

/*
long round(float a);
long round(double a);
*/


#undef fix_arduino_macros_h_round


#endif