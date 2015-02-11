
#include "approximation.hpp"

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

bool approximates(NumberArgument a, NumberArgument b, NumberArgument epsilon) {
  if (a < b) {
    return b - a <= epsilon;
  } else {
    return a - b <= epsilon;
  }
}

