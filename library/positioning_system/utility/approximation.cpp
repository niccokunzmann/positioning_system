
#include "Arduino.h"
#include "approximation.hpp"
//#include "positioning_system_test.h"

const double default_epsilon = 0.00000001;

double get_default_epsilon() {
  return default_epsilon;
}

double epsilon = default_epsilon;

double get_epsilon() {
  return epsilon;
}

void set_epsilon(const double new_epsilon) {
  epsilon = new_epsilon;
}

bool approximates(const double a, const double b) {
  return approximates(a, b, get_epsilon());
}

#define ABS(X) ((X < 0) ? -X : X)

bool approximates(const double a, const double b, const double epsilon) {
  if ((a == 0) || (b == 0)) {
    // one of the arguments is zero
    if (a < b) {
      return b - a <= epsilon;
    } else {
      return a - b <= epsilon;
    }
  }
  double epsilon_;
  if (ABS(a) > ABS(b)) {
    epsilon_ = ABS(a) * epsilon;
  } else {
    epsilon_ = ABS(b) * epsilon;
  }
  
  //println6("a: ", a, " b: ", b, " epsilon_*100000: ", epsilon_ * 100000);
  if (a < b) {
    return b - a <= epsilon_;
  } else {
    return a - b <= epsilon_;
  }
}

