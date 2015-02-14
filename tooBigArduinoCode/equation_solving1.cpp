
#include "equation_solving.hpp"

void solve_equation(NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1) {
  if (d == 0) {
    solve_equation(e, zero1);
  } else {
    *zero1 = - e / d;
  }
}