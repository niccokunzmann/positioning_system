#ifndef fix_arduino_macros_h
#define fix_arduino_macros_h

#include "Arduino.h"

#define fix_arduino_macros_h_abs(X) abs(X)
#undef abs

template <typename Type>
Type abs(Type a) {
    return fix_arduino_macros_h_abs(a);
}

#define fix_arduino_macros_h_round(X) round(X)
#undef round


template <typename Type>
long round(Type a) {
    return fix_arduino_macros_h_round(a);
}

#endif