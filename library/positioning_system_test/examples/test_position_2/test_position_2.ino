
#include "positioning_system_test.h"

test(position_1) {
  test_position(2, -1);
}

test(position_2) {
  test_position(30, -12);
}

test(position_3) {
  test_position(30, -30);
}

test(position_4) {
  test_position(-33.213, -12);
}


void setup() {
  TEST_APPROXIMATION_EPSILON = 0.001;
  Serial.begin(9600);
}

void loop() {
  Test::run();
}