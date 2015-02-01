

#ifndef solve_h
#define solve_h

#include "Arduino.h"

// a*x^4 + b * x^3 + c * x^2 + d * x + e

void get_coefficients_from_zeros(double zero1, double *d, double* e);
void get_coefficients_from_zeros(double zero1, double zero2, double *c, double *d, double *e);
void get_coefficients_from_zeros(double zero1, double zero2, double zero3, double *b, double *c, double *d, double *e);
void get_coefficients_from_zeros(double zero1, double zero2, double zero3, double zero4, double *a, double *b, double *c, double *d, double *e);

double call(double a, double b, double c, double d, double e, double x);


void print_coefficients_to_serial(double a, double b, double c, double d, double e);

#endif