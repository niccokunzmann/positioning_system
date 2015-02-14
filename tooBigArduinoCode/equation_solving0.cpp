
#include "equation_solving.hpp"
#include "approximation.hpp"

void solve_equation(NumberArgument e, 
                    NumberPointer zero1) {
  if (approximates(e, 0)) {
    *zero1 = 0;
  } else {
    *zero1 = get_not_a_number();
  }
}