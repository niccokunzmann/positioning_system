
#include "equation_solving.hpp"
#include "math.h"

Number p;
Number q;
Number D;
Number root_of_D;
Number minus_p_half;

void solve_equation(NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2) {
  if (c == 0) {
    solve_equation(d, e, zero1);
    *zero2 = get_not_a_number();
  } else {
    p = d / c;
    q = e / c;
    D = p * p / 4 - q;
    if (D < 0) {
      // no solution
      *zero1 = get_not_a_number();
      *zero2 = get_not_a_number();
    } else if (D == 0) {
      // one solution
      *zero1 = -p / 2;
      *zero2 = get_not_a_number();
    } else {
      // two solutions
      root_of_D = sqrt(D);
      minus_p_half = - p / 2;
      *zero1 = minus_p_half + root_of_D;
      *zero2 = minus_p_half - root_of_D;
    }
  }
}
