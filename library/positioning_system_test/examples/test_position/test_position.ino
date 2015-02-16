
#include "positioning_system_test.h"



test(position_n_eq_0) {
  test_position(12, -0.5);
}

test(equation2_for_position) {
  solve_equation(0.03326345818211429, -0.06652691636422858, -3.9916149818513342, &x1, &x2);
  sort_numbers(&x1, &x2);
  assertApproximately(x1, -10.);
  assertApproximately(x2, 12.);
}


test(position_r_eq_0_1) {
  test_position(1, 1);
}

test(position_r_eq_0_2) {
  test_position(1, 0);
}

test(position_r_eq_0_3) {
  test_position(1, -1);
}

test(position_r_eq_0_4) {
  test_position(0, 0);
}

test(position_r_eq_0_5) {
  test_position(1, -0.5);
}




void setup() {
  TEST_APPROXIMATION_EPSILON = 0.001;
  Serial.begin(9600);
}

void loop() {
  Test::run();
}

