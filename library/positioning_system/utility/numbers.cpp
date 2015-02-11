
#include "numbers.hpp"
#include "math.h"
#include "Arduino.h"

Number get_infinity() {
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#ifdef INFINITY
  return INFINITY;
#else
  static Number infinity;
  if (infinity + infinity + 1 == infinity) {
    return infinity;
  }
  infinity = 2;
  while (infinity != infinity + infinity) {
    infinity = infinity * infinity;
  }
  return infinity;
#endif
}

bool is_infinity(NumberArgument number) {
#ifdef isinf
  return isinf(number)
#else
  return abs(number) == get_infinity();
#endif
}

Number get_not_a_number() {
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#ifdef NAN
  return NAN;
#else
  static Number not_a_number;
  if (not_a_number - not_a_number == 0) {
    Number infinity = get_infinity();
    not_a_number = infinity - infinity;
    return not_a_number;
  }
  return not_a_number;
#endif
}

bool is_not_a_number(NumberArgument number) {
#ifdef isnan
  return isnan(number);
#else
  return number != get_infinity() && number - number != 0;
#endif
}

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

