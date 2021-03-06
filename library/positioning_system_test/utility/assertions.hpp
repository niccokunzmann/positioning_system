

#ifndef assertions_hpp
#define assertions_hpp

#include "Arduino.h"
#include <ArduinoUnit.h>
#include "positioning_system.h"

extern double TEST_APPROXIMATION_EPSILON;

/** Template binary operator=~= to assist with assertions */
template <typename T>
bool isApproximately(const T& a, const T& b) { return approximates(a, b, TEST_APPROXIMATION_EPSILON); }

/** macro generates optional output and calls fail() followed by a return if false. */
#define assertApproximately(arg1,arg2)       assertOp(arg1,isApproximately,"=~=",arg2)

template <typename T>
bool isNotTooDifferent(const T& a, const T& b) { 
  T difference = a - b;
  if (difference < 0) {
    difference = -difference;
  }
  return difference < TEST_APPROXIMATION_EPSILON;
}

#define assertAboutTheSame(arg1,arg2)       assertOp(arg1,isNotTooDifferent,"=~=",arg2)

  
#endif