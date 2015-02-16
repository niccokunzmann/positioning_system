
#include "Arduino.h"
#include "approximation.hpp"
#include "positioning_system_test.h"

const Number default_epsilon = Number(0.00000001);

Number get_default_epsilon() {
  return default_epsilon;
}

Number epsilon = default_epsilon;

Number get_epsilon() {
  return epsilon;
}

void set_epsilon(NumberArgument new_epsilon) {
  epsilon = new_epsilon;
}

bool approximates(NumberArgument a, NumberArgument b) {
  return approximates(a, b, get_epsilon());
}

#define ABS(X) ((X < 0) ? -X : X)

bool approximates(NumberArgument a, NumberArgument b, NumberArgument epsilon) {
  if ((a == 0) || (b == 0)) {
    // one of the arguments is zero
    if (a < b) {
      return b - a <= epsilon;
    } else {
      return a - b <= epsilon;
    }
  }
  Number epsilon_;
  if (ABS(a) > ABS(b)) {
    epsilon_ = ABS(a) * epsilon;
  } else {
    epsilon_ = ABS(b) * epsilon;
  }
  
  println6("a: ", a, " b: ", b, " epsilon_*100000: ", epsilon_ * 100000);
  if (a < b) {
    return b - a <= epsilon_;
  } else {
    return a - b <= epsilon_;
  }
}

