
#include "positioning_system_test.h"

Number a;
Number b;
Number c;
Number d;
Number e;
Number zero1;
Number zero2;
Number zero3;
Number zero4;

void print_zeros() {
  println8("zero1: ", zero1, " zero2: ", zero2, " zero3: ", zero3, " zero4: ", zero4);  
}

test(equation_4_q_is_0) {
  get_coefficients_from_zeros(41, 42, 43, 44, &a, &b, &c, &d, &e);
  solve_equation(a, b, c, d, e, &zero1, &zero2, &zero3, &zero4);
  sort_numbers(&zero1, &zero2, &zero3, &zero4);
  assertEqual(zero1, 41);
  assertEqual(zero2, 42);
  assertEqual(zero3, 43);
  assertEqual(zero4, 44);
}

test(equation_3_for_equation_4) {
  b = 8;
  c = 17.5;
  d = -5.90625;
  e = -16.435546875;
  solve_equation(b, c, d, e, &zero1, &zero2, &zero3);
  sort_numbers(&zero1, &zero2, &zero3);
  
  assertApproximately(zero1, -2.0625);
  assertApproximately(zero2, -1.0625);
  assertApproximately(zero3, 0.9375);

  assertEqual(call(0, b, c, d, e, zero1), 0);
  assertEqual(call(0, b, c, d, e, zero2), 0);
  assertEqual(call(0, b, c, d, e, zero3), 0);
}

test(equation_4) {
  get_coefficients_from_zeros(40, 42, 43, 44, &a, &b, &c, &d, &e);
  solve_equation(a, b, c, d, e, &zero1, &zero2, &zero3, &zero4);
  sort_numbers(&zero1, &zero2, &zero3, &zero4);
  assertEqual(zero1, 40);
  assertEqual(zero2, 42);
  assertEqual(zero3, 43);
  assertEqual(zero4, 44);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}