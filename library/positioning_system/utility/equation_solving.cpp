
#include "numbers.hpp"
#include "equation_solving.hpp"
#include "approximation.hpp"
#include "cubic_root.hpp"
#include "math.h"
#include "hpa.h"

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

void solve_equation(NumberArgument A,    NumberArgument B,    NumberArgument C,    NumberArgument D, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3) {
  // https://de.wikipedia.org/wiki/Cardanische_Formeln
  if (A == 0) {
    solve_equation(B, C, D, zero1, zero2);
    *zero3 = get_not_a_number();
  } else {
    // x³ + ax² + bx + c = 0
    Number a = B / A;
    Number b = C / A;
    Number c = D / A;
    
    Number a_2 = a*a;
    // x = z - a / 3
    // z³ + pz + q = 0
    Number p = b - a_2 / 3;
    Number q = 2 * a_2*a / 27 - a * b / 3 + c;
    
    Number discriminant = q*q / 4 + p*p*p / 27;
    if (discriminant > 0) {
//      test_println("{solve_3} -> discriminant > 0");
      Number sqrt_of_D = sqrt(discriminant);
      Number mins_q_half = - q / 2;
      Number u = curt(mins_q_half + sqrt_of_D);
      Number v = curt(mins_q_half - sqrt_of_D);
      Number z = u + v;
      *zero1 = z - a/3;
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
    } else if (p == 0 and q == 0) {
//      test_println("{solve_3} -> p == 0 and q == 0");
      // z = 0
      *zero1 = - a / 3;
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
    } else if (discriminant == 0) { // and (p != 0 or q != 0)
//      test_println("{solve_3} -> discriminant == 0 and (p != 0 or q != 0)");
      Number u = curt(- q / 2);
      Number z1 = 2 * u;
      Number z23 = - u;
      Number minus_a_third =  - a/3;
      *zero1 = z1 + minus_a_third;
      *zero2 = z23 + minus_a_third;
      *zero3 = get_not_a_number();
    } else { // discriminant < 0
//      test_println("{solve_3} -> discriminant < 0");
      Number sq3p = sqrt(-3 / p);
//      test_println("sq3p: ", sq3p);
      Number m = 2 / sq3p;
//      test_println("m: ", m);
      Number n1 = -q/2 * sq3p * sq3p * sq3p;
//      test_println("n1: ", n1);
      Number n2 = acos(n1);
//      test_println("n2: ", n2);
      Number n = n2 / 3;
//      test_println("n: ", n);
      Number PI_3 = M_PI / 3;
      // the following can be more optimized, I guess
      Number z2 = -m * cos(n + PI_3);
      Number z1 =  m * cos(n);
      Number z3 = -m * cos(n - PI_3);
//      test_println("z2: ", z2);
//      test_println("z1: ", z1);
//      test_println("z3: ", z3);
      Number minus_a_third =  - a/3;
      *zero1 = z1 + minus_a_third;
      *zero2 = z2 + minus_a_third;
      *zero3 = z3 + minus_a_third;
    }
  }
}

void solve_equation(NumberArgument a,    NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4) {
}
