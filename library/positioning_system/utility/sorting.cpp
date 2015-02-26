
#include "sorting.hpp"
// http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html
#include "math.h"
#include "positioning_system.h"

double get_not_a_number() {
  return get_infinity() / get_infinity();
}
double get_infinity() {
  static double infinity;
  if (infinity == 0) {
    infinity = 1;
  }
  while (infinity + infinity != infinity) {
    infinity += infinity;
  }
  return infinity;
}
boolean is_not_a_number(double n) {
  return n != n;
}

template <>
void sort(double *a, double *b) {
  if ((*a > *b) || is_not_a_number(*a)) {
    exchange(a, b);
  }
}

void sort_numbers(double *a, double *b){
  sort(a, b);
}
void sort_numbers(double *a, double *b, double *c) {
  sort(a, b, c);
}
void sort_numbers(double *a, double *b, double *c, double *d) {
  sort(a, b, c, d);
}

