
#include "cubic_root.hpp"

#include "Arduino.h"
#include "math.h"

Number nth_root(NumberArgument x, int n) {
  // http://stackoverflow.com/a/10441069/1320237
  if (!(n%2) || x<0){
    return get_not_a_number(); // even root from negative is fail
  }
  bool sign = (x >= 0);
  Number result = exp(log(abs(x))/n);
  return sign ? result : -result;
}

Number curt_1(NumberArgument x) {
  return nth_root(x, 3);
}

const Number one_third = 1.0 / 3.0;

Number curt_3(NumberArgument x) {
  // http://stackoverflow.com/a/4269145/1320237
  if (x < 0)
    return -1.0 * pow(-1.0*x, one_third);
  else
    return pow(x, one_third);
}

Number curt(NumberArgument x) {
  // see the benchmark example for the decision
  // curt_3 is fastest
  return curt_3(x); 
};
