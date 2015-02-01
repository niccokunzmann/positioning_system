
#include "solve.h"
#include "Arduino.h"

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
  *e -zero1 * zero2 * zero3;
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
    Serial.print(a);
    Serial.print("*x^4 + ");
  }
  if (b != 0) {
    Serial.print(b);
    Serial.print("*x^3 + ");
  }
  if (c != 0) {
    Serial.print(c);
    Serial.print("*x^2 + ");
  }
  if (d != 0) {
    Serial.print(d);
    Serial.print("*x + ");
  }
  Serial.print(e);
};





