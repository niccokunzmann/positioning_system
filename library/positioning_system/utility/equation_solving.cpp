
#include "equation_solving.hpp"

//#define DEBUG_SOLVE

#ifdef DEBUG_SOLVE
#include "positioning_system_test.h"

#define P1(A) println2("{{solve}} ", A);
#define P2(A, B) println3("{{solve}} ", A, B);

#else 

#define P1(A)
#define P2(A, B)  

#endif

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
  Number slope2;
  // t can be used by everyone
  Number t;
  Number t1;
  
  void compute_y_at_x() {
    y = coefficients[0];
    for (int i = 1; i < NumberOfCoefficients; ++i) {
      y*= x;
      y+= coefficients[i];
    }
  }
  void compute_slope_at_x() {
    int di = NumberOfCoefficients - 1;
    slope = coefficients[0];
    slope *= di;
    for (int i = 1; i < NumberOfCoefficients - 1; ++i) {
      --di;
      slope *= x;
      t = coefficients[i];
      //pvar(t);
      t *= di; // this can be optimized
      //pvar(t);
      slope += t;
    }
    //slope = ((4 * a * x + 3 * b) * x + 2 * c) * x + d;
  }
  
  /*void compute_slope2_at_x() {
    int di = NumberOfCoefficients - 1;
    slope2 = coefficients[0];
    slope2 *= di * (di - 1);
    for (int i = 1; i < NumberOfCoefficients - 2; ++i) {
      --di;
      slope2 *= x;
      t = coefficients[i];
      t *= di * (di - 1); // this can be optimized
      slope2 += t;
    }
    //slope2 = ((4 * 3 * a * x + 3 * 2 * b) * x + 2 * 1 * c) * x + 1 * 0 * d;
  }  
  */
  
  int failes;
  
  void newton_step() {
    P1("newton step");
    P2("x: ", x);
    compute_slope_at_x();
    P2("slope: ", slope);
    if (!slope) {
      failes++;
      x += failes;
      return;
    }
    compute_y_at_x();
    P2("y: ", y);
    //new_x = - y / slope + x
    // newton verfahren
    t = y;
    t /= slope;
    // modifiziertes newtonverfahren
    // http://www.tavrodir.lima-city.de/Arbeiten/Newton-%20und%20Sekantenverfahren%20Beleg.pdf
    //compute_slope2_at_x();
    //t1 = y;
    //t1 /= slope;
    //t1 *= slope2;
    //t1 /= slope;
    //t1 -= xONE;
    //t1 =-t1;
    //t /= t1;
    // x_n+1
    //P2("x: ", x);
    //P2("t1: ", t1);
    //P2("t: ", t);
    x -= t;
    //P2("nx: ", x);
  }
  
  void compute_newton(const int iterations) {
    last_x = xNAN;
    for (int i = 0; i < iterations; ++i) {
      if (isNaN(x)) {
        P1("nan -> skip");
        return;
      }
      //if (i % 8 == 7) {
      //P2("x: ", x);
      //P2("slope: ", slope);
      //P2("slope2: ", slope2);
//      P2("a: ", coefficients[0]._2double());
//      P2("b: ", coefficients[1]._2double());
//      P2("c: ", coefficients[2]._2double());
//      P2("d: ", coefficients[3]._2double());
//      P2("e: ", coefficients[4]._2double());
      //}
      if (i % 8 == 7) {
        t = last_x;
        t -= x;
        if (t.isneg()) {
          t = -t;
        }
        t1 = x;
        // epsilon for double precision
        // log2(1e14) == 46.5
        t1 *= 1e-16; 
        if (t1 < 0) {
          t1 = -t1;
        }
        //P2("difference: ", t._2double() - t1._2double());
        if (t < t1) {
          P2("difference -> skip ", i);
          return;
        }     
      }
      if (last_x == x) {
        P2("-> skip ", i);
        return;
      }
      last_x = x;
      newton_step();
//      P2("slope: ", slope._2double());
    }
    P1("failed to determine x");
    x = xNAN;
  }
  
  void initialize_newton(const Number a, const Number b, const Number c, const Number d, const Number e) {
    coefficients[0] = a;
    coefficients[1] = b;
    coefficients[2] = c;
    coefficients[3] = d;
    coefficients[4] = e;
    x = xONE;
    failes = 0;
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

void initialize_newton(NumberArgument a,    NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e) {
  equation_solving::initialize_newton(a, b, c, d, e);
}

const int CYCLES_1 = 5;
const int CYCLES_2 = 100;
const int CYCLES_3 = 100;
const int CYCLES_4 = 300;


void get_one_zero(double* zero, int cycles) {
  equation_solving::compute_newton(cycles);
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
  get_one_zero(zero1, CYCLES_1);
}
void solve_equation(NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2) {
  initialize_newton(0, 0, c, d, e);
  get_one_zero(zero1, CYCLES_2);
  get_one_zero(zero2, CYCLES_1);
}
void solve_equation(NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3) {
  initialize_newton(0, b, c, d, e);
  get_one_zero(zero1, CYCLES_3);
  get_one_zero(zero2, CYCLES_2);
  get_one_zero(zero3, CYCLES_1);
}
void solve_equation(NumberArgument a,    NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4) {
  initialize_newton(a, b, c, d, e);
  get_one_zero(zero1, CYCLES_4);
  get_one_zero(zero2, CYCLES_3);
  get_one_zero(zero3, CYCLES_2);
  get_one_zero(zero4, CYCLES_1);
}
