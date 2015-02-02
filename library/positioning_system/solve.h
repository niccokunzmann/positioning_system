

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

double get_epsilon();
void set_epsilon(double epsilon);
double get_default_epsilon();
boolean approximates(double a, double b);

void solve(double e, double *zero1);
void solve(double d, double e, double *zero1);
void solve(double c, double d, double e, double *zero1, double *zero2);
void solve(double b, double c, double d, double e, double *zero1, double *zero2, double *zero3);
void solve(double a, double b, double c, double d, double e, double *zero1, double *zero2, double *zero3, double *zero4);

double get_infinity();
double get_not_a_number();
boolean is_not_a_number(double number);

double nth_root(double x, int n);
double curt_1(double x);
double curt_2(double x);
double curt_3(double x);
double curt(double x);

#endif