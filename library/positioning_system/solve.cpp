

#include "solve.hpp"
#include "test_positioning_system.hpp"

void get_coefficients_from_zeros(NumberArgument zero1, 
                                 NumberPointer d, NumberPointer e) {
  *d = 1;
  *e = -zero1;
}
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, 
                                 NumberPointer c, NumberPointer d, NumberPointer e) {
  *c = 1;
  *d = -zero1 - zero2;
  *e = zero1 * zero2;
}
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberArgument zero3, 
                                 NumberPointer b, NumberPointer c, NumberPointer d, NumberPointer e) {
  *b = 1;
  *c = -zero1 - zero2 - zero3;
  *d = zero1 * zero2 + zero1 * zero3 + zero2 * zero3;
  *e = - zero1 * zero2 * zero3;
}
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberArgument zero3, NumberArgument zero4, 
                                 NumberPointer a, NumberPointer b, NumberPointer c, NumberPointer d, NumberPointer e) {
  *a = 1;
  *b = -zero1 - zero2 - zero3 - zero4;
  *c = zero1 * zero2 + zero1 * zero3 + zero1 * zero4 + zero2 * zero3 + zero2 * zero4 + zero3 * zero4;
  *d = - zero2 * zero3 * zero4 - zero1 * zero3 * zero4 - zero1 * zero2 * zero4 - zero1 * zero2 * zero3;
  *e = zero1 * zero2 * zero3 * zero4;
}

Number call(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, NumberArgument x) {
  return HPA::xONE;
  //return (((a * x + b) * x + c) * x + d) * x + e;
}
Number call(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, double x){
  return call(a, b, c, d, e, Number(x));
}
Number call(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, int x){
  return call(a, b, c, d, e, Number(x));
}
/*
void print_coefficients_to_serial(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e){
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

const NumberArgument default_epsilon = NumberArgument(0.00000001);
NumberArgument get_default_epsilon() {
  return default_epsilon;
}
NumberArgument epsilon = default_epsilon;
NumberArgument get_epsilon() {
  return epsilon;
}

void set_epsilon(NumberArgument new_epsilon) {
  epsilon = new_epsilon;
}



boolean approximates(NumberArgument a, NumberArgument b) {
  return approximates(a, b, get_epsilon());
}

boolean approximates(NumberArgument a, NumberArgument b, NumberArgument epsilon) {
  if (a < b) {
    return b - a <= epsilon;
  } else {
    return a - b <= epsilon;
  }
}

NumberArgument get_infinity() {
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#ifdef INFINITY
  return INFINITY;
#else
  static NumberArgument infinity;
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


NumberArgument get_not_a_number() {
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#ifdef NAN
  return NAN;
#else
  static NumberArgument not_a_number;
  if (not_a_number - not_a_number == 0) {
    NumberArgument infinity = get_infinity();
    not_a_number = infinity - infinity;
    return not_a_number;
  }
  return not_a_number;
#endif
}

boolean is_not_a_number(NumberArgument number) {
#ifdef isnan
  return isnan(number);
#else
  return number != get_infinity() && number - number != 0;
#endif
}

void solve(NumberArgument e, NumberPointer zero1) {
  if (approximates(e, 0)) {
    *zero1 = 0;
  } else {
    *zero1 = get_not_a_number();
  }
}

void solve(NumberArgument d, NumberArgument e, NumberPointer zero1) {
  if (d == 0) {
    solve(e, zero1);
  } else {
    *zero1 = - e / d;
  }
}

void solve(NumberArgument c, NumberArgument d, NumberArgument e, NumberPointer zero1, NumberPointer zero2) {
  if (c == 0) {
    solve(d, e, zero1);
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

NumberArgument nth_root(NumberArgument x, int n) {
  // http://stackoverflow.com/a/10441069/1320237
  if (!(n%2) || x<0){
    return get_not_a_number(); // even root from negative is fail
  }
  boolean sign = (x >= 0);
  x = exp(log(abs(x))/n);
  return sign ? x : -x;
}

NumberArgument curt_1(NumberArgument x) {
  return nth_root(x, 3);
}

NumberArgument curt_2(NumberArgument x) {
  // http://stackoverflow.com/a/28273079/1320237
  if (x == 0) {
    // would otherwise return something like 4.257959840008151e-109
    return 0;
  }
  NumberArgument b = 1; // use any value except 0
  NumberArgument last_b_1 = 0;
  NumberArgument last_b_2 = 0;
  while (last_b_1 != b && last_b_2 != b) {
    last_b_1 = b;
    b = (b + x / b / b) / 2;
    last_b_2 = b;
    b = (b + x / b / b) / 2;
  }
  return b;
}

NumberArgument curt_3(NumberArgument x) {
  // http://stackoverflow.com/a/4269145/1320237
  if (x < 0)
    return -1.0 * pow(-1.0*x, 1.0 / 3.0);
  else
    return pow(x, 1.0 / 3.0);
}

NumberArgument curt(NumberArgument x) {
  // see the benchmark example for the decision
  //return curt_3(x); // fastest
  return curt_3(x);
};

void solve(NumberArgument A, NumberArgument B, NumberArgument C, NumberArgument D, NumberPointer zero1, NumberPointer zero2, NumberPointer zero3) {
  // https://de.wikipedia.org/wiki/Cardanische_Formeln
  if (A == 0) {
    solve(B, C, D, zero1, zero2);
    *zero3 = get_not_a_number();
  } else {
    // x³ + ax² + bx + c = 0
    NumberArgument a = B / A;
    NumberArgument b = C / A;
    NumberArgument c = D / A;
    
    NumberArgument a_2 = a*a;
    // x = z - a / 3
    // z³ + pz + q = 0
    NumberArgument p = b - a_2 / 3;
    NumberArgument q = 2 * a_2*a / 27 - a * b / 3 + c;
    
    NumberArgument discriminant = q*q / 4 + p*p*p / 27;
    if (discriminant > 0) {
//      test_println("{solve_3} -> discriminant > 0");
      NumberArgument sqrt_of_D = sqrt(discriminant);
      NumberArgument mins_q_half = - q / 2;
      NumberArgument u = curt(mins_q_half + sqrt_of_D);
      NumberArgument v = curt(mins_q_half - sqrt_of_D);
      NumberArgument z = u + v;
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
      NumberArgument u = curt(- q / 2);
      NumberArgument z1 = 2 * u;
      NumberArgument z23 = - u;
      NumberArgument minus_a_third =  - a/3;
      *zero1 = z1 + minus_a_third;
      *zero2 = z23 + minus_a_third;
      *zero3 = get_not_a_number();
    } else { // discriminant < 0
//      test_println("{solve_3} -> discriminant < 0");
      NumberArgument sq3p = sqrt(-3 / p);
//      test_println("sq3p: ", sq3p);
      NumberArgument m = 2 / sq3p;
//      test_println("m: ", m);
      NumberArgument n1 = -q/2 * sq3p * sq3p * sq3p;
//      test_println("n1: ", n1);
      NumberArgument n2 = acos(n1);
//      test_println("n2: ", n2);
      NumberArgument n = n2 / 3;
//      test_println("n: ", n);
      NumberArgument PI_3 = PI / 3;
      // the following can be more optimized, I guess
      NumberArgument z2 = -m * cos(n + PI_3);
      NumberArgument z1 =  m * cos(n);
      NumberArgument z3 = -m * cos(n - PI_3);
//      test_println("z2: ", z2);
//      test_println("z1: ", z1);
//      test_println("z3: ", z3);
      NumberArgument minus_a_third =  - a/3;
      *zero1 = z1 + minus_a_third;
      *zero2 = z2 + minus_a_third;
      *zero3 = z3 + minus_a_third;
    }
  }
}

void solve(NumberArgument e, NumberArgument f, NumberArgument g, NumberArgument h, NumberArgument i, NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4) {
  if (e == 0) {
    solve(f, g, h, i, zero1, zero2, zero3);
    *zero4 = get_not_a_number();
  } else {
    test_print("Solving "); print_coefficients_to_serial(e, f, g, h, i); test_println(" = 0");
    NumberArgument a = f / e;
    NumberArgument b = g / e;
    NumberArgument c = h / e;
    NumberArgument d = i / e;
    test_print("Solving "); print_coefficients_to_serial(1, a, b, c, d); test_println(" = 0");
    
    NumberArgument a_2 = a * a;
    NumberArgument a_3 = a_2 * a;
    NumberArgument a_4 = a_2 * a_2;

    // x = z - a/4    
    NumberArgument p = b - 3. / 8. * a_2;
    NumberArgument q = a_3 / 8. - a * b / 2. + c;
    NumberArgument r = (-3. /256. + d / a_4 * 3) * a_4;
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
      NumberArgument vs[2];
      solve(1, p, r, &vs[1], &vs[2]);
      NumberPointer zeros[4] = {zero1, zero2, zero3, zero4};
      int zero_index = 0;
      NumberArgument minus_a_4 = - a / 4;
      for (int i = 0; i < 2; ++i) {
        NumberArgument v = vs[i];
        if (is_not_a_number(v)) {
          continue;
        } else if (approximates(v, 0)) {
          *(zeros[zero_index]) = minus_a_4;
          ++zero_index;
        } else if (v < 0) {
          continue;
        } else {
          NumberArgument z1 = sqrt(v);
          NumberArgument z2 = -z1;
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
      NumberArgument Ps[3];
      NumberArgument Pb = 8;
      NumberArgument Pc = -4*p;
      NumberArgument Pd = -8*r;
      NumberArgument Pe = 4*p*r - q*q;
      test_print("Solving order 3:"); print_coefficients_to_serial(0, Pb, Pc, Pd, Pe); test_println();
      solve(Pb, Pc, Pd, Pe, &(Ps[0]), &(Ps[1]), &(Ps[2]));
      boolean has_solution = false;
      NumberArgument P;
      NumberArgument Q;
      NumberArgument R;
      for (int i = 0; i < 3; ++i) {
        P = Ps[i];
        if (is_not_a_number(P)) {
          continue;
        } 
        NumberArgument Q_squared = 2 * P - p;
        NumberArgument R_squared = P * P - r;
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
        NumberArgument Q1 = sqrt(Q_squared);
        NumberArgument Q2 = -Q1;
        NumberArgument R1 = sqrt(R_squared);
        NumberArgument R2 = -R1;
        NumberArgument minus_q_half = -q / 2;
        NumberArgument QR[8] = {Q1, R1, Q2, R1, Q1, R2, Q2, R2};
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
        NumberArgument minus_a_4 = - a / 4;
        NumberArgument Zs[4];
        NumberPointer zeros[4] = {zero1, zero2, zero3, zero4};
        solve(1, Q, P + R, &(Zs[0]), &(Zs[1]));
        solve(1, -Q, P - R, &(Zs[2]), &(Zs[3]));
        int zero_index = 0;
        for (int i = 0; i < 4; ++i) {
          NumberArgument z = Zs[i];
          if (is_not_a_number(z)) {
            continue;
          } else {
            NumberArgument x = z + minus_a_4;
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

void switch_numbers(NumberPointer a, NumberPointer b) {
  NumberArgument temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void sort_numbers(NumberPointer a, NumberPointer b) {
  if ((*a > *b) || is_not_a_number(*a)) {
    switch_numbers(a, b);
  }
}

void sort_numbers(NumberPointer a, NumberPointer b, NumberPointer c) {
  // bubblesort
  sort_numbers(a, b);
  sort_numbers(b, c);
  sort_numbers(a, b);
}

void sort_numbers(NumberPointer a, NumberPointer b, NumberPointer c, NumberPointer d) {
  // bubblesort
  sort_numbers(a, b);
  sort_numbers(b, c);
  sort_numbers(c, d);
  sort_numbers(a, b, c);
}












*/





