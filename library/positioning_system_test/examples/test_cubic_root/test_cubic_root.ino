
#include "positioning_system_test.h"

test(curt_of_0) {
  assertEqual(curt(0), 0);
}

test(curt_of_1) {
  assertEqual(curt(1), 1);
}

test(curt_of_negative) {
  assertEqual(curt(-1), -1);
}

test(curt_of_negative_8) {
  assertEqual(curt(-8), -2);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}