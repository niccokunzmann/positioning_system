

#ifndef assertions_hpp
#define assertions_hpp

#include "Arduino.h"

#ifndef TEST_APPROXIMATION_EPSILON
#define TEST_APPROXIMATION_EPSILON 0.00000001
#endif

/** Template binary operator== to assist with assertions */
template <typename T>
bool isApproximately(const T& a, const T& b) { return abs(a - b) <= TEST_APPROXIMATION_EPSILON; }

/** macro generates optional output and calls fail() followed by a return if false. */
#define assertApproximately(arg1,arg2)       assertOp(arg1,isApproximately,"=~=",arg2)


#endif