
#include "call_coefficients.hpp"

Number call(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, double x){
  return (((a * x + b) * x + c) * x + d) * x + e;
}
Number call(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, int x){
  return (((a * x + b) * x + c) * x + d) * x + e;
}