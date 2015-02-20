
#include "positioning_system_test.h"



test(position_n_eq_0) {
  test_position(12, -0.5);
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

