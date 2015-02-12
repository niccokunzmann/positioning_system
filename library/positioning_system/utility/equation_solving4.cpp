
#include "equation_solving.hpp"
#include "approximation.hpp"
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
HPA::xreal a_4_;
HPA::xreal p_;
HPA::xreal q_;
HPA::xreal r_;

Number minus_a_4;

Number p;
Number q;
Number r;

Number vs[2];
Number v;
NumberPointer zeros[4];

int zero_index;

Number z1;
Number z2;

Number Ps[3];
Number Pb;
Number Pc;
Number Pd;
Number Pe;

boolean has_solution;

Number P;
Number Q;
Number R;

Number Q_squared;
Number R_squared;

Number Q1;
Number Q2;
Number R1;
Number R2;
Number minus_q_half;
Number QR[8];

Number Zs[4];
NumberPointer zeros[4];

Number z;
Number x;

void solve_equation(NumberArgument e,    NumberArgument f,    NumberArgument g,    NumberArgument h,    NumberArgument i, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4) {
  if (e == 0) {
    solve_equation(f, g, h, i, zero1, zero2, zero3);
    *zero4 = get_not_a_number();
  } else {
    a = f / e;
    b = g / e;
    c = h / e;
    d = i / e;
    
    a_ = a;
    b_ = b;
    c_ = c;
    d_ = d;

    a_2_ = a_ * a_;
    a_3_ = a_2_ * a_;
    a_4_ = a_2_ * a_2_;

    // x = z - a/4    
    minus_a_4 = - a / 4;
    p_ = b_ - a_2_ * 3. / 8.;
    q_ = a_3_ / 8. - a_ * b_ / 2. + c_;
    r_ = -a_4_ * 3/256 + a_2_ * b_ / 16 - a_ * c_ / 4 + d_;

    p = p_._2double();
    q = q_._2double();
    r = r_._2double();
    
    //println6("p: ", p, " q: ", q, " r: ", r);
    
    if (approximates(p, 0) && approximates(q, 0)) {
      println1("{solve_4} -> p == 0 and q == 0");
      if (approximates(r4, 0)) {
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
      solve_equation(1, p, r, &vs[0], &vs[1]);
      zeros = {zero1, zero2, zero3, zero4};
      zero_index = 0;
      
      for (int i = 0; i < 2; ++i) {
        v = vs[i];
        if (is_not_a_number(v)) {
          continue;
        } else if (approximates(v, 0)) {
          *(zeros[zero_index]) = minus_a_4;
          ++zero_index;
        } else if (v < 0) {
          continue;
        } else {
          z1 = sqrt(v);
          z2 = -z1;
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
      Pb = 8;
      Pc = -4*p;
      Pd = -8*r;
      Pe = (4*p_*r_ - q_*q_)._2double();
      //print1("Solving order 3: "); print_coefficients_to_serial(0, Pb, Pc, Pd, Pe); println0();
      // Pb, Pc, Pd, Pe work fine
      // solve([8, 17.5, -5.90625, -16.435546875])
      println1(5);
      solve_equation(Pb, Pc, Pd, Pe, &(Ps[0]), &(Ps[1]), &(Ps[2]));
      println1(6);
      has_solution = false;
      for (int i = 0; i < 3; ++i) {
        println1(0);
        P = Ps[i];
        if (is_not_a_number(P)) {
          continue;
        } 
        Q_squared = 2 * P - p;
        R_squared = P * P - r;
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
        Q1 = sqrt(Q_squared);
        Q2 = -Q1;
        R1 = sqrt(R_squared);
        R2 = -R1;
        minus_q_half = -q / 2;
        QR = {Q1, R1, Q2, R1, Q1, R2, Q2, R2};
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
        Zs[4];
        zeros[4] = {zero1, zero2, zero3, zero4};
        solve_equation(1, Q, P + R, &(Zs[0]), &(Zs[1]));
        solve_equation(1, -Q, P - R, &(Zs[2]), &(Zs[3]));
        for (int i = 0; i < 4; ++i) {
          z = Zs[i];
          if (is_not_a_number(z)) {
            continue;
          } else {
            x = z + minus_a_4;
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
