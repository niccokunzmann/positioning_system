

#ifndef solve_h
#define solve_h

#include "Arduino.h"

// a*x^4 + b * x^3 + c * x^2 + d * x + e
typedef struct Coefficients {
   double a;
   double b;
   double c;
   double d;
   double e;
} Coefficients;

Coefficients get_coefficients();
Coefficients get_coefficients(double a);
Coefficients get_coefficients(double a, double b);
Coefficients get_coefficients(double a, double b, double c);
Coefficients get_coefficients(double a, double b, double c, double d);
Coefficients get_coefficients(double a, double b, double c, double d, double e);

Coefficients get_coefficients_from_zeros();
Coefficients get_coefficients_from_zeros(double zero1);
Coefficients get_coefficients_from_zeros(double zero1, double zero2);
Coefficients get_coefficients_from_zeros(double zero1, double zero2, double zero3);
Coefficients get_coefficients_from_zeros(double zero1, double zero2, double zero3, double zero4);

double call(const Coefficients coefficients, double x);

void print_coefficients_to_serial(const Coefficients coefficients);

#endif