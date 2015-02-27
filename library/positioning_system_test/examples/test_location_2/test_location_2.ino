
#include "positioning_system_test.h"

#define TEST_LOCATE(X, Y) test(locate_##X##_##Y) { assertLocates(X / 100., Y / 100.); }

TEST_LOCATE(20, 50)
//TEST_LOCATE(10, 80)

void setup() {
  TEST_APPROXIMATION_EPSILON = 0.01;
  Serial.begin(9600);
}

void loop() {
  Test::run();
}
