
#include "numbers.hpp"
#include "equation_solving.hpp"
#include "math.h"

void solve_equation(NumberArgument e, 
                    NumberPointer zero1) {
  if (approximates(e, 0)) {
    *zero1 = 0;
  } else {
    *zero1 = get_not_a_number();
  }
}

void solve_equation(NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1) {
  if (d == 0) {
    solve_equation(e, zero1);
  } else {
    *zero1 = - e / d;
  }
}

void solve_equation(NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2) {
  if (c == 0) {
    solve_equation(d, e, zero1);
    *zero2 = get_not_a_number();
  } else {
    NumberArgument p = d / c;
    NumberArgument q = e / c;
    NumberArgument D = p * p / 4 - q;
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
      NumberArgument root_of_D = sqrt(D);
      NumberArgument minus_p_half = - p / 2;
      *zero1 = minus_p_half + root_of_D;
      *zero2 = minus_p_half - root_of_D;
    }
  }
}

void solve_equation(NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3) {
}

void solve_equation(NumberArgument a,    NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4) {
}
