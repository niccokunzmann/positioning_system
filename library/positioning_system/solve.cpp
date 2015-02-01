
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

double epsilon = 0.00000001;
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
  static double infinity;
  if (infinity + infinity + 1 == infinity) {
    return infinity;
  }
  infinity = 2;
  while (infinity != infinity + infinity) {
    infinity = infinity * infinity;
  }
  return infinity;
}


double get_not_a_number() {
  static double not_a_number;
  if (not_a_number - not_a_number == 0) {
    double infinity = get_infinity();
    not_a_number = infinity - infinity;
    return not_a_number;
  }
  return not_a_number;
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
void solve(double b, double c, double d, double e, double *zero1, double *zero2, double *zero3) {
  if (b == 0) {
    solve(c, d, e, zero1, zero2);
    *zero3 = get_not_a_number();
  } else {
    
  }
}
void solve(double a, double b, double c, double d, double e, double *zero1, double *zero2, double *zero3, double *zero4);

