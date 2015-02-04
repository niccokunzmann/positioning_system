

#ifndef solve_h
#define solve_h

#include "hpa.h"

#include "Arduino.h"

// a*x^4 + b * x^3 + c * x^2 + d * x + e

typedef HPA::xreal xreal;

void get_coefficients_from_zeros(xreal zero1, xreal *d, xreal* e);
void get_coefficients_from_zeros(xreal zero1, xreal zero2, xreal *c, xreal *d, xreal *e);
void get_coefficients_from_zeros(xreal zero1, xreal zero2, xreal zero3, xreal *b, xreal *c, xreal *d, xreal *e);
void get_coefficients_from_zeros(xreal zero1, xreal zero2, xreal zero3, xreal zero4, xreal *a, xreal *b, xreal *c, xreal *d, xreal *e);

xreal call(xreal a, xreal b, xreal c, xreal d, xreal e, xreal x);

void print_coefficients_to_serial(xreal a, xreal b, xreal c, xreal d, xreal e);

xreal get_epsilon();
void set_epsilon(xreal epsilon);
xreal get_default_epsilon();
boolean approximates(xreal a, xreal b);
boolean approximates(xreal a, xreal b, xreal epsilon);

void solve(xreal e, xreal *zero1);
void solve(xreal d, xreal e, xreal *zero1);
void solve(xreal c, xreal d, xreal e, xreal *zero1, xreal *zero2);
void solve(xreal b, xreal c, xreal d, xreal e, xreal *zero1, xreal *zero2, xreal *zero3);
void solve(xreal a, xreal b, xreal c, xreal d, xreal e, xreal *zero1, xreal *zero2, xreal *zero3, xreal *zero4);

xreal get_infinity();
xreal get_not_a_number();
boolean is_not_a_number(xreal number);

xreal nth_root(xreal x, int n);
xreal curt_1(xreal x);
xreal curt_2(xreal x);
xreal curt_3(xreal x);
xreal curt(xreal x);

void sort_numbers(xreal *a, xreal *b);
void sort_numbers(xreal *a, xreal *b, xreal *c);
void sort_numbers(xreal *a, xreal *b, xreal *c, xreal *d);

xreal newton(xreal a, xreal b, xreal c, xreal d, xreal e, xreal x, xreal epsilon);
xreal newton(xreal a, xreal b, xreal c, xreal d, xreal e, xreal x, xreal epsilon, long maximum_iterations);

void refine_zeros_of_order_3_with_3_solutions(xreal b, xreal c, xreal d, xreal e, xreal *zero1, xreal *zero2, xreal *zero3);
xreal refine_zero(xreal a, xreal b, xreal c, xreal d, xreal e, xreal upper_bound, xreal lower_bound);

#endif