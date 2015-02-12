
#include "equation_solving.hpp"
#include "approximation.hpp"
#include "cubic_root.hpp"
#include "math.h"
// for debug
#include "positioning_system_test.h"

Number a;
Number b;
Number c;
Number d;

HPA::xreal a_;
HPA::xreal b_;
HPA::xreal c_;
HPA::xreal d_;
HPA::xreal a_2_;
HPA::xreal a_3_;
HPA::xreal p_;
HPA::xreal q_;

Number p;
Number q;

HPA::xreal discriminant_;
Number discriminant;
Number minus_a_third;

Number u;
Number v;
HPA::xreal sqrt_of_D;
HPA::xreal minus_q_half;

Number z1;
Number z2;
Number z3;

Number sq3p;
Number n;
Number m;

// M_PI from math.h
// HPA::xPI from hpa.h
const Number PI_3 = M_PI / 3;

void solve_equation(NumberArgument A,    NumberArgument B,    NumberArgument C,    NumberArgument D, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3) {
  // https://de.wikipedia.org/wiki/Cardanische_Formeln
  if (A == 0) {
    solve_equation(B, C, D, zero1, zero2);
    *zero3 = get_not_a_number();
  } else {
    // x³ + ax² + bx + c = 0
    a = B / A;
    b = C / A;
    c = D / A;
    
    a_ = a;
    b_ = b;
    c_ = c;
//      println2("a: ", a_);
//      println2("b: ", b_);
//      println2("c: ", c_);
//      println2("0.33333333333333333333: ", 0.33333333333333333333);

    // x = z - a / 3
    // z³ + pz + q = 0
    a_2_ = a_*a_;
    p_ = b_ - a_2_ / 3;
    q_ = 2 * a_2_*a_ / 27 - a_ * b_ / 3 + c_;
    
    p = p_._2double();
    q = q_._2double();
    
    discriminant_ = q_*q_ / 4 + p_*p_*p_ / 27;
    discriminant = discriminant_._2double();
    minus_a_third =  - a/3;
    
    if (approximates(p, 0) and approximates(q, 0)) {
//      println1("{solve_3} -> p == 0 and q == 0");
      // z = 0
      *zero1 = minus_a_third;
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
    } else if (approximates(discriminant, 0)) { // and (p != 0 or q != 0)
//      println1("{solve_3} -> discriminant == 0 and (p != 0 or q != 0)");
      u = curt(- q / 2);
      z1 = 2 * u;
      z2 = - u;
      
      *zero1 = z1 + minus_a_third;
      *zero2 = z2 + minus_a_third;
      *zero3 = get_not_a_number();
    } else if (discriminant > 0) {
      //println1("{solve_3} -> discriminant > 0");
      //println2("D: ", discriminant);
      sqrt_of_D = square_root(discriminant_);
      //println2("sqrt_of_D: ", sqrt_of_D);
      minus_q_half = - q / 2;
      //println2("mins_q_half: ", minus_q_half);
      u = curt((minus_q_half + sqrt_of_D)._2double());
      //println2("u: ", u);
      v = curt((minus_q_half - sqrt_of_D)._2double());
      //println2("v: ", v);
      z = u + v;
      //println2("z: ", z);
      *zero1 = z + minus_a_third;
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
    } else { // discriminant < 0
//      println1("{solve_3} -> discriminant < 0");
      sq3p3 = sqrt(-3 / p);
//      println2("p: ", p_);
//      println2("q: ", q_);
//      println2("sq3p: ", sq3p);
      m = 2 / sq3p;
//      println2("m: ", m);
      n = -q3/2 * sq3p * sq3p * sq3p;
//      println2("n1: ", n1);
      n = acos(n3);
//      println2("n2: ", n2);
      n = n3 / 3;
//      println2("n: ", n);

      // the following can be more optimized, I guess
      z2 = -m * cos(n + PI_3);
      z1 =  m * cos(n);
      z3 = -m * cos(n - PI_3);
//      println2("z2: ", z2);
//      println2("z1: ", z1);
//      println2("z3: ", z3);

      *zero1 = (z1 + minus_a_third);
      *zero2 = (z2 + minus_a_third);
      *zero3 = (z3 + minus_a_third);
    }
  }
}