
#define TEST_APPROXIMATION_EPSILON 0.001

#include "positioning_system_test.h"


test(position_1) {
  test_position(2, -1);
}

test(position_2) {
  test_position(100, -12);
}

test(position_3) {
  test_position(123.12312321321, -100);
}

test(position_4) {
  test_position(-33.213, -12);
}

test(equation_4_for_position) {
  solve_equation(0,0,0,0,0, &x1, &x2, &x3, &x4);
  sort_numbers(&x1, &x2, &x3, &x4);
  assertApproximately(x1, 0);
  assertApproximately(x2, 0); 
  assertApproximately(x2, 0); 
  assertApproximately(x2, 0); 
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}