#include "positioning_system_test.h"

Number c;
Number d;
Number e;
Number zero1;
Number zero2;

test(equation_2) {  
  get_coefficients_from_zeros(22, 24, &c, &d, &e);
  
  solve_equation(c, d, e, &zero1, &zero2);
  
  sort_numbers(&zero1, &zero2);
  
  assertEqual(zero1, 22);
  assertEqual(zero2, 24);
}

test(equation_2_one_zero) {  
  get_coefficients_from_zeros(22, 22, &c, &d, &e);
  
  solve_equation(c, d, e, &zero1, &zero2);
  
  assertEqual(zero1, 22);
  assertTrue(is_not_a_number(zero2));
}

test(equation_2_no_zero) {  
  solve_equation(1, 0, 1, &zero1, &zero2);
  
  assertTrue(is_not_a_number(zero1));
  assertTrue(is_not_a_number(zero2));
}

test(equation_2_linear_solving) {  
  get_coefficients_from_zeros(22, &d, &e);
  solve_equation(0, d, e, &zero1, &zero2);
  
  assertEqual(zero1, 22);
  assertTrue(is_not_a_number(zero2));
}

test(equation_2_constant_solving) {  
  solve_equation(0, 0, 2, &zero1, &zero2);
  
  assertTrue(is_not_a_number(zero1));
  assertTrue(is_not_a_number(zero2));
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}