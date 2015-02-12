
#include "numbers.hpp"
#include "equation_solving.hpp"
#include "approximation.hpp"
#include "cubic_root.hpp"
#include "math.h"

// for debug
#include "positioning_system_test.h"

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
    
    HPA::xreal a_ = a;
    HPA::xreal b_ = b;
    HPA::xreal c_ = c;
//      println2("a: ", a_);
//      println2("b: ", b_);
//      println2("c: ", c_);
//      println2("0.33333333333333333333: ", 0.33333333333333333333);

    // x = z - a / 3
    // z³ + pz + q = 0
    HPA::xreal a_2 = a_*a_;
    HPA::xreal p_ = (b_ - a_2 / 3);
    HPA::xreal q_ = (2 * a_2*a_ / 27 - a_ * b_ / 3 + c_);
    
    Number p = p_._2double();
    Number q = q_._2double();
    
    HPA::xreal discriminant_ = q_*q_ / 4 + p_*p_*p_ / 27;
    Number discriminant = discriminant_._2double();
    Number minus_a_third =  - a/3;
    
    if (approximates(p, 0) and approximates(q, 0)) {
//      println1("{solve_3} -> p == 0 and q == 0");
      // z = 0
      *zero1 = minus_a_third;
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
    } else if (approximates(discriminant, 0)) { // and (p != 0 or q != 0)
//      println1("{solve_3} -> discriminant == 0 and (p != 0 or q != 0)");
      Number u = curt(- q / 2);
      Number z1 = 2 * u;
      Number z23 = - u;

      *zero1 = z1 + minus_a_third;
      *zero2 = z23 + minus_a_third;
      *zero3 = get_not_a_number();
    } else if (discriminant > 0) {
      //println1("{solve_3} -> discriminant > 0");
      //println2("D: ", discriminant);
      HPA::xreal sqrt_of_D = square_root(discriminant_);
      //println2("sqrt_of_D: ", sqrt_of_D);
      HPA::xreal minus_q_half = - q / 2;
      //println2("mins_q_half: ", minus_q_half);
      Number u = curt((minus_q_half + sqrt_of_D)._2double());
      //println2("u: ", u);
      Number v = curt((minus_q_half - sqrt_of_D)._2double());
      //println2("v: ", v);
      Number z = u + v;
      //println2("z: ", z);
      *zero1 = (z + minus_a_third);
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
    } else { // discriminant < 0
//      println1("{solve_3} -> discriminant < 0");
      Number sq3p = sqrt(-3 / p);
//      println2("p: ", p_);
//      println2("q: ", q_);
//      println2("sq3p: ", sq3p);
      Number m = 2 / sq3p;
//      println2("m: ", m);
      Number n1 = -q/2 * sq3p * sq3p * sq3p;
//      println2("n1: ", n1);
      Number n2 = acos(n1);
//      println2("n2: ", n2);
      Number n = n2 / 3;
//      println2("n: ", n);
      // M_PI from math.h
      // HPA::xPI from hpa.h
      Number PI_3 = M_PI / 3;
      // the following can be more optimized, I guess
      Number z2 = -m * cos(n + PI_3);
      Number z1 =  m * cos(n);
      Number z3 = -m * cos(n - PI_3);
//      println2("z2: ", z2);
//      println2("z1: ", z1);
//      println2("z3: ", z3);

      *zero1 = (z1 + minus_a_third);
      *zero2 = (z2 + minus_a_third);
      *zero3 = (z3 + minus_a_third);
    }
  }
}

void solve_equation(NumberArgument e,    NumberArgument f,    NumberArgument g,    NumberArgument h,    NumberArgument i, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4) {
  if (e == 0) {
    solve_equation(f, g, h, i, zero1, zero2, zero3);
    *zero4 = get_not_a_number();
  } else {
    const Number a = f / e;
    const Number b = g / e;
    const Number c = h / e;
    const Number d = i / e;
    
    const HPA::xreal a_ = a;
    const HPA::xreal b_ = b;
    const HPA::xreal c_ = c;
    const HPA::xreal d_ = d;

    const HPA::xreal a_2_ = a_ * a_;
    const HPA::xreal a_3_ = a_2_ * a_;
    const HPA::xreal a_4_ = a_2_ * a_2_;

    // x = z - a/4    
    const HPA::xreal p_ = b_ - a_2_ * 3. / 8.;
    const HPA::xreal q_ = a_3_ / 8. - a_ * b_ / 2. + c_;
    const HPA::xreal r_ = -a_4_ * 3/256 + a_2_ * b_ / 16 - a_ * c_ / 4 + d_;

    const Number p = p_._2double();
    const Number q = q_._2double();
    const Number r = r_._2double();
    
    //println6("p: ", p, " q: ", q, " r: ", r);
    
    if (approximates(p, 0) && approximates(q, 0)) {
      println1("{solve_4} -> p == 0 and q == 0");
      if (approximates(r, 0)) {
        println1("{solve_4} -> r == 0");
        *zero1 = 0;
      } else if (r > 0){
        println1("{solve_4} -> r > 0");
        *zero1 = get_not_a_number();
      } else {
        println1("{solve_4} -> r < 0");
        *zero1 = sqrt(-r);
      }
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
      *zero4 = get_not_a_number();
    } else if (approximates(q, 0)) {
      println1("{solve_4} -> q == 0");
      // v = z²
      Number vs[2];
      solve_equation(1, p, r, &vs[0], &vs[1]);
      NumberPointer zeros[4] = {zero1, zero2, zero3, zero4};
      int zero_index = 0;
      const Number minus_a_4 = - a / 4;
      for (int i = 0; i < 2; ++i) {
        const Number v = vs[i];
        if (is_not_a_number(v)) {
          continue;
        } else if (approximates(v, 0)) {
          *(zeros[zero_index]) = minus_a_4;
          ++zero_index;
        } else if (v < 0) {
          continue;
        } else {
          const Number z1 = sqrt(v);
          const Number z2 = -z1;
          *(zeros[zero_index]) = z1 + minus_a_4;
          ++zero_index;
          *(zeros[zero_index]) = z2 + minus_a_4;
          ++zero_index;
        }
      }
      for (; zero_index < 4; ++zero_index) {
        *(zeros[zero_index]) = get_not_a_number();
      }
    } else {
      println1("{solve_4} -> q != 0");
      Number Ps[3];
      const Number Pb = 8;
      const Number Pc = -4*p;
      const Number Pd = -8*r;
      const Number Pe = (4*p_*r_ - q_*q_)._2double();
      //print1("Solving order 3: "); print_coefficients_to_serial(0, Pb, Pc, Pd, Pe); println0();
      // Pb, Pc, Pd, Pe work fine
      // solve([8, 17.5, -5.90625, -16.435546875])
      println1(5);
      solve_equation(Pb, Pc, Pd, Pe, &(Ps[0]), &(Ps[1]), &(Ps[2]));
      println1(6);
      boolean has_solution = false;
      Number P;
      Number Q;
      Number R;
      for (int i = 0; i < 3; ++i) {
        println1(0);
        P = Ps[i];
        if (is_not_a_number(P)) {
          continue;
        } 
        Number Q_squared = 2 * P - p;
        Number R_squared = P * P - r;
        if (approximates(Q_squared, 0)) {
          Q_squared = 0;
        } else if (Q_squared < 0) {
          continue;
        }
        if (approximates(R_squared, 0)) {
          R_squared = 0;
        } else if (R_squared < 0) {
          continue;
        }
        const Number Q1 = sqrt(Q_squared);
        const Number Q2 = -Q1;
        const Number R1 = sqrt(R_squared);
        const Number R2 = -R1;
        const Number minus_q_half = -q / 2;
        const Number QR[8] = {Q1, R1, Q2, R1, Q1, R2, Q2, R2};
        for (int QR_i = 0; QR_i < 8; QR_i+= 2) {
          println1(2);
          Q = QR[QR_i];
          R = QR[QR_i + 1];
          
          has_solution = approximates(R * Q, minus_q_half);
          if (has_solution) {
            break;
          }
        }
        // found suitable solution
        println1(1);
        break; 
      }
      println2("has_solution: ", has_solution);
      if (!has_solution) {
        *zero1 = *zero2 = *zero3 = *zero4 = get_not_a_number();
      } else {
        const Number minus_a_4 = - a / 4;
        Number Zs[4];
        NumberPointer zeros[4] = {zero1, zero2, zero3, zero4};
        solve_equation(1, Q, P + R, &(Zs[0]), &(Zs[1]));
        solve_equation(1, -Q, P - R, &(Zs[2]), &(Zs[3]));
        int zero_index = 0;
        for (int i = 0; i < 4; ++i) {
          const Number z = Zs[i];
          if (is_not_a_number(z)) {
            continue;
          } else {
            const Number x = z + minus_a_4;
            *(zeros[zero_index]) = x;
            ++zero_index;
          }
        }
        for (; zero_index < 4; ++zero_index) {
          *(zeros[zero_index]) = get_not_a_number();
        }
      }
    }
  }
}
