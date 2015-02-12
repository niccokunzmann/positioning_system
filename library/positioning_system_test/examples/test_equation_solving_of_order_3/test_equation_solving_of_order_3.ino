
#include "positioning_system_test.h"

Number b;
Number c;
Number d;
Number e;
Number zero1;
Number zero2;
Number zero3;

void print_zeros() {
  println6("zero1: ", zero1, "zero2: ", zero2, "zero3: ", zero3);  
}

test(equation_3_with_D_lower_0) {
  get_coefficients_from_zeros(36., 11., 33., &b, &c, &d, &e);
  solve_equation(b, c, d, e, &zero1, &zero2, &zero3);
  sort_numbers(&zero1, &zero2, &zero3);
  
  assertApproximately(zero1, 11.);
  assertApproximately(zero2, 33.);
  assertApproximately(zero3, 36.);

  assertEqual(call(0, b, c, d, e, zero1), 0);
  assertEqual(call(0, b, c, d, e, zero2), 0);
  assertEqual(call(0, b, c, d, e, zero3), 0);
}

test(equation_3_with_D_is_0_and_2_zeros) {
  get_coefficients_from_zeros(31, 31, 37, &b, &c, &d, &e);
  solve_equation(b, c, d, e, &zero1, &zero2, &zero3);
  sort_numbers(&zero1, &zero2);
  
  assertEqual(zero1, 31);
  assertEqual(zero2, 37);
  assertTrue(is_not_a_number(zero3));
}

test(equation_3_with_D_is_0_and_1_zero) {
  get_coefficients_from_zeros(30, 30, 30, &b, &c, &d, &e);
  solve_equation(b, c, d, e, &zero1, &zero2, &zero3);
  
  assertEqual(zero1, 30);
  assertTrue(is_not_a_number(zero2));
  assertTrue(is_not_a_number(zero3));
}

test(equation_3_with_D_greater_0) {
  solve_equation(1, 0, 1, 30, &zero1, &zero2, &zero3); // one solution only
  
  print_zeros();
  assertApproximately(zero1, -3.);
  assertTrue(is_not_a_number(zero2));
  assertTrue(is_not_a_number(zero3));
}

test(equation_2_with_2_zeros) {
  // test quadratic solving
  get_coefficients_from_zeros(32, 34, &c, &d, &e);
  solve_equation(0, c, d, e, &zero1, &zero2, &zero3);
  sort_numbers(&zero1, &zero2);
  assertEqual(zero1, 32);
  assertEqual(zero2, 34);
  assertTrue(is_not_a_number(zero3));
}

test(equation_2_with_1_zero) {
  get_coefficients_from_zeros(38, 38, &c, &d, &e);
  solve_equation(0, c, d, e, &zero1, &zero2, &zero3);
  sort_numbers(&zero1, &zero2);
  assertEqual(zero1, 38);
  assertTrue(is_not_a_number(zero2));
  assertTrue(is_not_a_number(zero3));
}

test(equation_2_with_0_zeros) {
  solve_equation(0, 3, 0, 3, &zero1, &zero2, &zero3);
  assertTrue(is_not_a_number(zero1));
  assertTrue(is_not_a_number(zero2));
  assertTrue(is_not_a_number(zero3));
}

test(equation_1_with_1_zeros) {
  // test linear solving
  get_coefficients_from_zeros(399, &d, &e);
  solve_equation(0, 0, d, e, &zero1, &zero2, &zero3);
  assertEqual(zero1, 399);
  assertTrue(is_not_a_number(zero2));
  assertTrue(is_not_a_number(zero3));
}

test(equation_0_with_0_zeros) {
  // test constant solving
  solve_equation(0, 0, 0, 3, &zero1, &zero2, &zero3);
  assertTrue(is_not_a_number(zero1));
  assertTrue(is_not_a_number(zero2));
  assertTrue(is_not_a_number(zero3));

}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}