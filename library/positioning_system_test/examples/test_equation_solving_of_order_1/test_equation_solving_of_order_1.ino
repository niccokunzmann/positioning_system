
#include "positioning_system_test.h"

Number d;
Number e;
Number zero1;

test(equation_0_zero) {
  solve_equation(0, &zero1);
  assertEqual(zero1, 0.);
}

test(equation_0_not_zero) {
  solve_equation(3, &zero1);
  assertTrue(is_not_a_number(zero1));
}

test(equation_1_1) {
  get_coefficients_from_zeros(11, &d, &e);
  solve_equation(d, e, &zero1);
  assertApproximately(zero1, 11.);
}

test(equation_1_2) {
  get_coefficients_from_zeros(12, &d, &e);
  solve_equation(d, e, &zero1);
  assertApproximately(zero1, 12.);
}

test(equation_1_constant_solving) {
  solve_equation(0, 1, &zero1);
  assertTrue(is_not_a_number(zero1));
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}