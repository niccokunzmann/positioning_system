
#include "solve.h"
#include "Arduino.h"
#include "test_positioning_system.h"
#include "math.h"

void get_coefficients_from_zeros(double zero1, double *d, double* e) {
  *d = 1;
  *e = -zero1;
};
void get_coefficients_from_zeros(double zero1, double zero2, double *c, double *d, double *e) {
  *c = 1;
  *d = -zero1 - zero2;
  *e = zero1 * zero2;
};
void get_coefficients_from_zeros(double zero1, double zero2, double zero3, double* b, double *c, double* d, double *e) {
  *b = 1;
  *c = -zero1 - zero2 - zero3;
  *d = zero1 * zero2 + zero1 * zero3 + zero2 * zero3;
  *e = - zero1 * zero2 * zero3;
};
void get_coefficients_from_zeros(double zero1, double zero2, double zero3, double zero4, double *a, double* b, double *c, double* d, double *e) {
  *a = 1;
  *b = -zero1 - zero2 - zero3 - zero4;
  *c = zero1 * zero2 + zero1 * zero3 + zero1 * zero4 + zero2 * zero3 + zero2 * zero4 +  + zero3 * zero4;
  *d = - zero2 * zero3 * zero4 - zero1 * zero3 * zero4 - zero1 * zero2 * zero4 - zero1 * zero2 * zero3;
  *e = zero1 * zero2 * zero3 * zero4;
};

double call(double a, double b, double c, double d, double e, double x){
  return (((a * x + b) * x + c) * x + d) * x + e;
};

void print_coefficients_to_serial(double a, double b, double c, double d, double e){
  if (a != 0) {
    test_print(a);
    test_print("*x^4 + ");
  }
  if (b != 0) {
    test_print(b);
    test_print("*x^3 + ");
  }
  if (c != 0) {
    test_print(c);
    test_print("*x^2 + ");
  }
  if (d != 0) {
    test_print(d);
    test_print("*x + ");
  }
  test_print(e);
};

const double default_epsilon = 0.00000001;
double get_default_epsilon() {
  return default_epsilon;
}
double epsilon = default_epsilon;
double get_epsilon() {
  return epsilon;
}

void set_epsilon(double new_epsilon) {
  epsilon = new_epsilon;
}



boolean approximates(double a, double b) {
  if (a < b) {
    return b - a <= epsilon;
  } else {
    return a - b <= epsilon;
  }
}

double get_infinity() {
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#ifdef INFINITY
  return INFINITY;
#else
  static double infinity;
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


double get_not_a_number() {
  // http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#ifdef NAN
  return NAN;
#else
  static double not_a_number;
  if (not_a_number - not_a_number == 0) {
    double infinity = get_infinity();
    not_a_number = infinity - infinity;
    return not_a_number;
  }
  return not_a_number;
#endif
}

boolean is_not_a_number(double number) {
  return number != get_infinity() && number - number != 0;
}

void solve(double e, double *zero1) {
  if (approximates(e, 0)) {
    *zero1 = 0;
  } else {
    *zero1 = get_not_a_number();
  }
}

void solve(double d, double e, double *zero1) {
  if (d == 0) {
    solve(e, zero1);
  } else {
    *zero1 = - e / d;
  }
}

void solve(double c, double d, double e, double *zero1, double *zero2) {
  if (c == 0) {
    solve(d, e, zero1);
    *zero2 = get_not_a_number();
  } else {
    double p = d / c;
    double q = e / c;
    double D = p * p / 4 - q;
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
      double root_of_D = sqrt(D);
      double minus_p_half = - p / 2;
      *zero1 = minus_p_half + root_of_D;
      *zero2 = minus_p_half - root_of_D;
    }
  }
}

double nth_root(double x, int n) {
  // http://stackoverflow.com/a/10441069/1320237
  if (!(n%2) || x<0){
    return get_not_a_number(); // even root from negative is fail
  }
  boolean sign = (x >= 0);
  x = exp(log(abs(x))/n);
  return sign ? x : -x;
}

double curt_1(double x) {
  return nth_root(x, 3);
}

double curt_2(double x) {
  // http://stackoverflow.com/a/28273079/1320237
  if (x == 0) {
    // would otherwise return something like 4.257959840008151e-109
    return 0;
  }
  double b = 1; // use any value except 0
  double last_b_1 = 0;
  double last_b_2 = 0;
  while (last_b_1 != b && last_b_2 != b) {
    last_b_1 = b;
    b = (b + x / b / b) / 2;
    last_b_2 = b;
    b = (b + x / b / b) / 2;
  }
  return b;
}

double curt_3(double x) {
  // http://stackoverflow.com/a/4269145/1320237
  if (x < 0)
    return -1.0 * pow(-1.0*x, 1.0 / 3.0);
  else
    return pow(x, 1.0 / 3.0);
}

double curt(double x) {
  // see the benchmark example for the decision
  //return curt_3(x); // fastest
  return curt_3(x);
};

void solve(double A, double B, double C, double D, double *zero1, double *zero2, double *zero3) {
  // https://de.wikipedia.org/wiki/Cardanische_Formeln
  if (A == 0) {
    solve(B, C, D, zero1, zero2);
    *zero3 = get_not_a_number();
  } else {
    // x³ + ax² + bx + c = 0
    double a = B / A;
    double b = C / A;
    double c = D / A;
    
    // x = z - a / 3
    // z³ + pz + q = 0
    double p = b - a*a / 3;
    double q = 2 * a*a*a / 27 - a * b / 3 + c;
    
    D = q*q / 4 + p*p*p / 27;
    if (D > 0) {
//      test_println("{solve_3} -> D > 0");
      double sqrt_of_D = sqrt(D);
      double u = curt(- q / 2 + sqrt_of_D);
      double v = curt(- q / 2 - sqrt_of_D);
      double z = u + v;
      *zero1 = z - a/3;
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
    } else if (p == 0 and q == 0) {
//      test_println("{solve_3} -> p == 0 and q == 0");
      // z = 0
      *zero1 = - a / 3;
      *zero2 = get_not_a_number();
      *zero3 = get_not_a_number();
    } else if (D == 0) { // and (p != 0 or q != 0)
//      test_println("{solve_3} -> D == 0 and (p != 0 or q != 0)");
      double u = curt(- q / 2);
      double z1 = 2 * u;
      double z23 = - u;
      *zero1 = z1 - a/3;
      *zero2 = z23 - a/3;
      *zero3 = get_not_a_number();
    } else { // D < 0
//      test_println("{solve_3} -> D < 0");
      double sq3p = sqrt(-3 / p);
//      test_println("sq3p: ", sq3p);
      double m = 2 / sq3p;
//      test_println("m: ", m);
      double n1 = -q/2 * sq3p * sq3p * sq3p;
//      test_println("n1: ", n1);
      double n2 = acos(n1);
//      test_println("n2: ", n2);
      double n = n2 / 3;
//      test_println("n: ", n);
      // the following can be more optimized, I guess
      double z2 = -m * cos(n + PI / 3);
      double z1 =  m * cos(n);
      double z3 = -m * cos(n - PI / 3);
//      test_println("z2: ", z2);
//      test_println("z1: ", z1);
//      test_println("z3: ", z3);
      *zero1 = z1 - a/3;
      *zero2 = z2 - a/3;
      *zero3 = z3 - a/3;
    }
  }
}
void solve(double a, double b, double c, double d, double e, double *zero1, double *zero2, double *zero3, double *zero4);

