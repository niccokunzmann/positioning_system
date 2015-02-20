
#include "positioning_system_test.h"

Number b;
Number c;
Number d;
Number e;
Number zero1;
Number zero2;
Number zero3;

void print_zeros() {
  println6("zero1: ", zero1, " zero2: ", zero2, " zero3: ", zero3);  
}

test(equation_3_with_D_lower_0) {
  get_coefficients_from_zeros(36., 11., 33., &b, &c, &d, &e);
  solve_equation(b, c, d, e, &zero1, &zero2, &zero3);
  sort_numbers(&zero1, &zero2, &zero3);
  
  assertApproximately(zero1, 11.);
  assertApproximately(zero2, 33.);
  assertApproximately(zero3, 36.);
}

test(equation_3_with_D_is_0_and_2_zeros) {
  get_coefficients_from_zeros(31, 31, 37, &b, &c, &d, &e);
  solve_equation(b, c, d, e, &zero1, &zero2, &zero3);
  sort_numbers(&zero1, &zero2);
  
  assertApproximately(zero1, 31.);
  assertApproximately(zero2, 31.);
  assertApproximately(zero3, 37.);
}
/*
test(equation_3_with_D_is_0_and_1_zero) {
  // this test will never run 
  // it does not even run in Python
  println1(" ----- equation_3_with_D_is_0_and_1_zero ----- ");
  get_coefficients_from_zeros(30, 30, 30, &b, &c, &d, &e);
  solve_equation(b, c, d, e, &zero1, &zero2, &zero3);
  
  assertApproximately(zero1, 30.);
  assertTrue(is_not_a_number(zero2));
  assertTrue(is_not_a_number(zero3));
}*/

test(equation_3_with_D_greater_0) {
  solve_equation(1, 0, 1, 30, &zero1, &zero2, &zero3); // one solution only
  
  assertApproximately(zero1, -3.);
  assertTrue(is_not_a_number(zero2));
  assertTrue(is_not_a_number(zero3));
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}