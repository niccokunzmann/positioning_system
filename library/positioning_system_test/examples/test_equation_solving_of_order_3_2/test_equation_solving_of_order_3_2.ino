
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