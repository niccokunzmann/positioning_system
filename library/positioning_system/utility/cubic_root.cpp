
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

Number curt_2(NumberArgument x) {
  // http://stackoverflow.com/a/28273079/1320237
  if (x == 0) {
    // would otherwise return something like 4.257959840008151e-109
    return 0;
  }
  Number b = 1; // use any value except 0
  Number last_b_1 = 0;
  Number last_b_2 = 0;
  while (last_b_1 != b && last_b_2 != b) {
    last_b_1 = b;
    b = (b + x / b / b) / 2;
    last_b_2 = b;
    b = (b + x / b / b) / 2;
  }
  return b;
}

Number curt_3(NumberArgument x) {
  // http://stackoverflow.com/a/4269145/1320237
  if (x < 0)
    return -1.0 * pow(-1.0*x, 1.0 / 3.0);
  else
    return pow(x, 1.0 / 3.0);
}

Number curt(NumberArgument x) {
  // see the benchmark example for the decision
  //return curt_3(x); // fastest
  return curt_3(x);
};
