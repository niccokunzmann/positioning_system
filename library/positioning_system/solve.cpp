
#include "solve.h"
#include "Arduino.h"

Coefficients get_coefficients() {
  return get_coefficients(0, 0, 0, 0, 0);
};
Coefficients get_coefficients(double e) {
  return get_coefficients(0, 0, 0, 0, e);
};
Coefficients get_coefficients(double d, double e) {
  return get_coefficients(0, 0, 0, d, e);
};
Coefficients get_coefficients(double c, double d, double e) {
  return get_coefficients(0, 0, c, d, e);
};
Coefficients get_coefficients(double b, double c, double d, double e) {
  return get_coefficients(0, b, c, d, e);
};
Coefficients get_coefficients(double a, double b, double c, double d, double e) {
  return get_coefficients(a, b, c, d, e);
};

Coefficients get_coefficients_from_zeros() {
  // const 
  return get_coefficients(0);
};
Coefficients get_coefficients_from_zeros(double zero1) {
  // (x - zero1)
  return get_coefficients(1, -zero1);
};
Coefficients get_coefficients_from_zeros(double zero1, double zero2) {
  // (x - zero1) * (x - zero2)
  return get_coefficients(1, 
                          -zero1 - zero2, 
                          zero1 * zero2);
};
Coefficients get_coefficients_from_zeros(double zero1, double zero2, double zero3) {
  // (x - zero1) * (x - zero2) * (x - zero3)
  return get_coefficients(1, 
                          -zero1 - zero2 - zero3, 
                          zero1 * zero2 + zero1 * zero3 + zero2 * zero3, 
                          -zero1 * zero2 * zero3);
};
Coefficients get_coefficients_from_zeros(double zero1, double zero2, double zero3, double zero4) {
  // (x - zero1) * (x - zero2) * (x - zero3) * (x - zero4)
  return get_coefficients(1, 
                          -zero1 - zero2 - zero3 - zero4, 
                          zero1 * zero2 + zero1 * zero3 + zero1 * zero4 + zero2 * zero3 + zero2 * zero4 +  + zero3 * zero4, 
                          - zero2 * zero3 * zero4 - zero1 * zero3 * zero4 - zero1 * zero2 * zero4 - zero1 * zero2 * zero3,
                          zero1 * zero2 * zero3 * zero4);
};

double call(const Coefficients coefficients, double x){
  return (((coefficients.a * x + coefficients.b) * x + coefficients.c) * x + coefficients.d) * x + coefficients.e;
};

void print_coefficients_to_serial(const Coefficients coefficients){
  if (coefficients.a != 0) {
    Serial.print(coefficients.a);
    Serial.print("*x^4 + ");
  }
  if (coefficients.b != 0) {
    Serial.print(coefficients.b);
    Serial.print("*x^3 + ");
  }
  if (coefficients.c != 0) {
    Serial.print(coefficients.c);
    Serial.print("*x^2 + ");
  }
  if (coefficients.d != 0) {
    Serial.print(coefficients.d);
    Serial.print("*x + ");
  }
  Serial.print(coefficients.e);
};





