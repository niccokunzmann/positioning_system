
#include "equation_solving.hpp"

#include "positioning_system_test.h"


namespace equation_solving {
  using namespace HPA;
  
  typedef HPA::xreal Coefficient;
  
  // coefficients
  
  const int NumberOfCoefficients = 5; // >= 1
  Coefficient coefficients[NumberOfCoefficients];

  // for differeciation
  
  typedef HPA::xreal Number;
  
  Number y;
  Number last_x;
  Number x;
  Number slope;
  Number d;
  
  void compute_y_at_x() {
    y = coefficients[0];
    for (int i = 1; i < NumberOfCoefficients; ++i) {
      y*= x;
      y+= coefficients[i];
    }
  }
  void compute_slope_at_x() {
    int di = NumberOfCoefficients - 2;
    slope = coefficients[0];
    slope *= di;
    for (int i = 1; i < NumberOfCoefficients - 1; ++i) {
      slope *= x;
      d = coefficients[i];
      d *= di;
      slope += d;
      --di;
    }
    //slope = ((4 * a * x + 3 * b) * x + 2 * c) * x + d;
  }
  
  // t can be used by everyone
  Number t;
  
  void newton_step() {
    compute_slope_at_x();
    if (!slope) {
      x = xNAN;
      return;
    }
    compute_y_at_x();
    //new_x = - y / slope + x
    t = y;
    t /= slope;
    x -= t;
  }
  
  void compute_newton(const int iterations) {
    for (int i = 0; i < iterations; ++i) {
      if (isNaN(x)) {
        println1("not a number skip");
        return;
      }
      println2("x: ", x);
//      println2("a: ", coefficients[0]._2double());
//      println2("b: ", coefficients[1]._2double());
//      println2("c: ", coefficients[2]._2double());
//      println2("d: ", coefficients[3]._2double());
//      println2("e: ", coefficients[4]._2double());
      if (last_x == x) {
        println1("skip");
        return;
      }
      last_x = x;
      newton_step();
//      println2("slope: ", slope._2double());
    }
  }
  
  void initialize_newton(const Number a, const Number b, const Number c, const Number d, const Number e) {
    coefficients[0] = a;
    coefficients[1] = b;
    coefficients[2] = c;
    coefficients[3] = d;
    coefficients[4] = e;
    x = xZERO;
    last_x = xNAN;
  }
  
  double get_x() {
    return x._2double();
  }
  
  // ausklammern von x aus der Gleichung
  // treat x as a zero and remove it from the equation
  void remove_x_as_zero() {
    //less_coefficients = [coefficients[0]]
    //for coefficient in coefficients[1:-1]:
    //    less_coefficients.append(coefficient + zero * less_coefficients[-1])
    // remove the influence of x
    for (int i = 1; i < NumberOfCoefficients - 1; ++i) {
      t = coefficients[i - 1];
      t *= x;
      coefficients[i] += t;
    }
    // copy one more to the left
    for (int i = NumberOfCoefficients - 1; i > 0; --i) {
      coefficients[i] = coefficients[i - 1];
    }
    coefficients[0] = xZERO;
  }
}

// __attribute__((noinline))
// http://stackoverflow.com/questions/4862222/locally-disable-function-inlining

void __attribute__((noinline)) initialize_newton(NumberArgument a,    NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e) {
  equation_solving::initialize_newton(a, b, c, d, e);
}

void __attribute__((noinline)) get_one_zero(double* zero) {
  equation_solving::compute_newton(100);
  *zero = equation_solving::get_x();
  equation_solving::remove_x_as_zero();
}

void solve_equation(NumberArgument e, 
                    NumberPointer zero1) {
  if (e == 0) {
    *zero1 = 0; 
  } else {
    *zero1 = get_not_a_number();
  }
}
void solve_equation(NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1) {
  initialize_newton(0, 0, 0, d, e);
  get_one_zero(zero1);
}
void solve_equation(NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2) {
  initialize_newton(0, 0, c, d, e);
  get_one_zero(zero1);
  get_one_zero(zero2);
}
void solve_equation(NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3) {
  initialize_newton(0, b, c, d, e);
  get_one_zero(zero1);
  get_one_zero(zero2);
  get_one_zero(zero3);
}
void solve_equation(NumberArgument a,    NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4) {
  initialize_newton(a, b, c, d, e);
  get_one_zero(zero1);
  get_one_zero(zero2);
  get_one_zero(zero3);
  get_one_zero(zero4);
}
