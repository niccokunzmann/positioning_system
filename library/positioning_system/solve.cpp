

#include "solve.hpp"
#include "test_positioning_system.hpp"
#include "math.h"

void get_coefficients_from_zeros(xreal zero1, xreal *d, xreal *e) {
  *d = HPA::xONE;
  *e = -zero1;
};
void get_coefficients_from_zeros(xreal zero1, xreal zero2, xreal *c, xreal *d, xreal *e) {
  *c = HPA::xONE;
  *d = -zero1 - zero2;
  *e = zero1 * zero2;
};
void get_coefficients_from_zeros(xreal zero1, xreal zero2, xreal zero3, xreal *b, xreal *c, xreal *d, xreal *e) {
  *b = HPA::xONE;
  *c = -zero1 - zero2 - zero3;
  *d = zero1 * zero2 + zero1 * zero3 + zero2 * zero3;
  *e = - zero1 * zero2 * zero3;
};
void get_coefficients_from_zeros(xreal zero1, xreal zero2, xreal zero3, xreal zero4, xreal *a, xreal *b, xreal *c, xreal *d, xreal *e) {
  *a = HPA::xONE;
  *b = -zero1 - zero2 - zero3 - zero4;
  *c = zero1 * zero2 + zero1 * zero3 + zero1 * zero4 + zero2 * zero3 + zero2 * zero4 + zero3 * zero4;
  *d = - zero2 * zero3 * zero4 - zero1 * zero3 * zero4 - zero1 * zero2 * zero4 - zero1 * zero2 * zero3;
  *e = zero1 * zero2 * zero3 * zero4;
};

xreal call(xreal a, xreal b, xreal c, xreal d, xreal e, xreal x){
  return (((a * x + b) * x + c) * x + d) * x + e;
};

void print_coefficients_to_serial(xreal a, xreal b, xreal c, xreal d, xreal e){
  if (a != 0) {
    test_print(a);
    test_print(F("*x^4 + "));
  }
  if (b != 0) {
    test_print(b);
    test_print(F("*x^3 + "));
  }
  if (c != 0) {
    test_print(c);
    test_print(F("*x^2 + "));
  }
  if (d != 0) {
    test_print(d);
    test_print(F("*x + "));
  }
  test_print(e);
};

const xreal default_epsilon = xreal(0.00000001);
xreal get_default_epsilon() {
  return default_epsilon;
}
xreal epsilon = default_epsilon;
xreal get_epsilon() {
  return epsilon;
}

void set_epsilon(xreal new_epsilon) {
  epsilon = new_epsilon;
}



boolean approximates(xreal a, xreal b) {
  return approximates(a, b, get_epsilon());
}

boolean approximates(xreal a, xreal b, xreal epsilon) {
  if (a < b) {
    return b - a <= epsilon;
  } else {
    return a - b <= epsilon;
  }
}

xreal get_infinity() {
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#ifdef INFINITY
  return INFINITY;
#else
  static xreal infinity;
  if (infinity + infinity + 1 == infinity) {
    return infinity;
  }
  infinity = 2;
  while (infinity != infinity + infinity) {
    infinity = infinity * infinity;
  }
  return infinity;
#endif
}


xreal get_not_a_number() {
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#ifdef NAN
  return NAN;
#else
  static xreal not_a_number;
  if (not_a_number - not_a_number == 0) {
    xreal infinity = get_infinity();
    not_a_number = infinity - infinity;
    return not_a_number;
  }
  return not_a_number;
#endif
}

boolean is_not_a_number(xreal number) {
#ifdef isnan
  return isnan(number);
#else
  return number != get_infinity() && number - number != 0;
#endif
}

void solve(xreal e, xreal *zero1) {
  if (approximates(e, 0)) {
    *zero1 = 0;
  } else {
    *zero1 = get_not_a_number();
  }
}

void solve(xreal d, xreal e, xreal *zero1) {
  if (d == 0) {
    solve(e, zero1);
  } else {
    *zero1 = - e / d;
  }
}

void solve(xreal c, xreal d, xreal e, xreal *zero1, xreal *zero2) {
  if (c == 0) {
    solve(d, e, zero1);
    *zero2 = get_not_a_number();
  } else {
    xreal p = d / c;
    xreal q = e / c;
    xreal D = p * p / 4 - q;
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
      xreal root_of_D = sqrt(D);
      xreal minus_p_half = - p / 2;
      *zero1 = minus_p_half + root_of_D;
      *zero2 = minus_p_half - root_of_D;
    }
  }
}

xreal nth_root(xreal x, int n) {
  // http://stackoverflow.com/a/10441069/1320237
  if (!(n%2) || x<0){
    return get_not_a_number(); // even root from negative is fail
  }
  boolean sign = (x >= 0);
  x = exp(log(abs(x))/n);
  return sign ? x : -x;
}

xreal curt_1(xreal x) {
  return nth_root(x, 3);
}

xreal curt_2(xreal x) {
  // http://stackoverflow.com/a/28273079/1320237
  if (x == 0) {
    // would otherwise return something like 4.257959840008151e-109
    return 0;
  }
  xreal b = 1; // use any value except 0
  xreal last_b_1 = 0;
  xreal last_b_2 = 0;
  while (last_b_1 != b && last_b_2 != b) {
    last_b_1 = b;
    b = (b + x / b / b) / 2;
    last_b_2 = b;
    b = (b + x / b / b) / 2;
  }
  return b;
}

xreal curt_3(xreal x) {
  // http://stackoverflow.com/a/4269145/1320237
  if (x < 0)
    return -1.0 * pow(-1.0*x, 1.0 / 3.0);
  else
    return pow(x, 1.0 / 3.0);
}

xreal curt(xreal x) {
  // see the benchmark example for the decision
  //return curt_3(x); // fastest
  return curt_3(x);
};

void solve(xreal A, xreal B, xreal C, xreal D, xreal *zero1, xreal *zero2, xreal *zero3) {
  // https://de.wikipedia.org/wiki/Cardanische_Formeln
  if (A == 0) {
    solve(B, C, D, zero1, zero2);
    *zero3 = get_not_a_number();
  } else {
    // x³ + ax² + bx + c = 0
    xreal a = B / A;
    xreal b = C / A;
    xreal c = D / A;
    
    xreal a_2 = a*a;
    // x = z - a / 3
    // z³ + pz + q = 0
    xreal p = b - a_2 / 3;
    xreal q = 2 * a_2*a / 27 - a * b / 3 + c;
    
    xreal discriminant = q*q / 4 + p*p*p / 27;
    if (discriminant > 0) {
//      test_println("{solve_3} -> discriminant > 0");
      xreal sqrt_of_D = sqrt(discriminant);
      xreal mins_q_half = - q / 2;
      xreal u = curt(mins_q_half + sqrt_of_D);
      xreal v = curt(mins_q_half - sqrt_of_D);
      xreal z = u + v;
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
      xreal u = curt(- q / 2);
      xreal z1 = 2 * u;
      xreal z23 = - u;
      xreal minus_a_third =  - a/3;
      *zero1 = z1 + minus_a_third;
      *zero2 = z23 + minus_a_third;
      *zero3 = get_not_a_number();
    } else { // discriminant < 0
//      test_println("{solve_3} -> discriminant < 0");
      xreal sq3p = sqrt(-3 / p);
//      test_println("sq3p: ", sq3p);
      xreal m = 2 / sq3p;
//      test_println("m: ", m);
      xreal n1 = -q/2 * sq3p * sq3p * sq3p;
//      test_println("n1: ", n1);
      xreal n2 = acos(n1);
//      test_println("n2: ", n2);
      xreal n = n2 / 3;
//      test_println("n: ", n);
      xreal PI_3 = PI / 3;
      // the following can be more optimized, I guess
      xreal z2 = -m * cos(n + PI_3);
      xreal z1 =  m * cos(n);
      xreal z3 = -m * cos(n - PI_3);
//      test_println("z2: ", z2);
//      test_println("z1: ", z1);
//      test_println("z3: ", z3);
      xreal minus_a_third =  - a/3;
      *zero1 = z1 + minus_a_third;
      *zero2 = z2 + minus_a_third;
      *zero3 = z3 + minus_a_third;
    }
  }
}

void solve(xreal e, xreal f, xreal g, xreal h, xreal i, xreal *zero1, xreal *zero2, xreal *zero3, xreal *zero4) {
  if (e == 0) {
    solve(f, g, h, i, zero1, zero2, zero3);
    *zero4 = get_not_a_number();
  } else {
    test_print("Solving "); print_coefficients_to_serial(e, f, g, h, i); test_println(" = 0");
    xreal a = f / e;
    xreal b = g / e;
    xreal c = h / e;
    xreal d = i / e;
    test_print("Solving "); print_coefficients_to_serial(1, a, b, c, d); test_println(" = 0");
    
    xreal a_2 = a * a;
    xreal a_3 = a_2 * a;
    xreal a_4 = a_2 * a_2;

    // x = z - a/4    
    xreal p = b - 3. / 8. * a_2;
    xreal q = a_3 / 8. - a * b / 2. + c;
    xreal r = (-3. /256. + d / a_4 * 3) * a_4;
    test_println("r: ", r);
    r += a_2 * (b / 16. - 3 * d / a_2);
    test_println("r: ", r);
    r -= a * (c / 4. - d / a);
    test_println("r: ", r);
    //r += d;
    
    test_println("p: ", p, " q: ", q, " r: ", r);
    
    if (approximates(p, 0) && approximates(q, 0)) {
      test_println("{solve_4} -> p == 0 and q == 0");
      if (approximates(r, 0)) {
        test_println("{solve_4} -> r == 0");
        *zero1 = 0;
      } else if (r > 0){
        test_println("{solve_4} -> r > 0");
        *zero1 = get_not_a_number();
      } else {
        test_println("{solve_4} -> r < 0");
        *zero1 = sqrt(-r);
      }
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
      *zero4 = get_not_a_number();
    } else if (approximates(q, 0)) {
      test_println("{solve_4} -> q == 0");
      // v = z²
      xreal vs[2];
      solve(1, p, r, &vs[1], &vs[2]);
      xreal *zeros[4] = {zero1, zero2, zero3, zero4};
      int zero_index = 0;
      xreal minus_a_4 = - a / 4;
      for (int i = 0; i < 2; ++i) {
        xreal v = vs[i];
        if (is_not_a_number(v)) {
          continue;
        } else if (approximates(v, 0)) {
          *(zeros[zero_index]) = minus_a_4;
          ++zero_index;
        } else if (v < 0) {
          continue;
        } else {
          xreal z1 = sqrt(v);
          xreal z2 = -z1;
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
      test_println("{solve_4} -> q != 0");
      xreal Ps[3];
      xreal Pb = 8;
      xreal Pc = -4*p;
      xreal Pd = -8*r;
      xreal Pe = 4*p*r - q*q;
      test_print("Solving order 3:"); print_coefficients_to_serial(0, Pb, Pc, Pd, Pe); test_println();
      solve(Pb, Pc, Pd, Pe, &(Ps[0]), &(Ps[1]), &(Ps[2]));
      boolean has_solution = false;
      xreal P;
      xreal Q;
      xreal R;
      for (int i = 0; i < 3; ++i) {
        P = Ps[i];
        if (is_not_a_number(P)) {
          continue;
        } 
        xreal Q_squared = 2 * P - p;
        xreal R_squared = P * P - r;
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
        xreal Q1 = sqrt(Q_squared);
        xreal Q2 = -Q1;
        xreal R1 = sqrt(R_squared);
        xreal R2 = -R1;
        xreal minus_q_half = -q / 2;
        xreal QR[8] = {Q1, R1, Q2, R1, Q1, R2, Q2, R2};
        for (int QR_i = 0; QR_i < 8; ++QR_i) {
          Q = QR[QR_i];
          ++QR_i;
          R = QR[QR_i];
          
          has_solution = approximates(R * Q, minus_q_half);
          if (has_solution) {
            break;
          }
        }
        // found suitable solution
        break; 
      }
      if (!has_solution) {
        *zero1 = *zero2 = *zero3 = *zero4 = get_not_a_number();
      } else {
        xreal minus_a_4 = - a / 4;
        xreal Zs[4];
        xreal *zeros[4] = {zero1, zero2, zero3, zero4};
        solve(1, Q, P + R, &(Zs[0]), &(Zs[1]));
        solve(1, -Q, P - R, &(Zs[2]), &(Zs[3]));
        int zero_index = 0;
        for (int i = 0; i < 4; ++i) {
          xreal z = Zs[i];
          if (is_not_a_number(z)) {
            continue;
          } else {
            xreal x = z + minus_a_4;
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

void switch_numbers(xreal *a, xreal *b) {
  xreal temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void sort_numbers(xreal *a, xreal *b) {
  if ((*a > *b) || is_not_a_number(*a)) {
    switch_numbers(a, b);
  }
}

void sort_numbers(xreal *a, xreal *b, xreal *c) {
  // bubblesort
  sort_numbers(a, b);
  sort_numbers(b, c);
  sort_numbers(a, b);
}

void sort_numbers(xreal *a, xreal *b, xreal *c, xreal *d) {
  // bubblesort
  sort_numbers(a, b);
  sort_numbers(b, c);
  sort_numbers(c, d);
  sort_numbers(a, b, c);
}


















