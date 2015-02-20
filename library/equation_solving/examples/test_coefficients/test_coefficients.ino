
#include "positioning_system_test.h"

Number a = 0;
Number b = 0;
Number c = 0;
Number d = 0;
Number e = 0;

test(test_from_zeros_1) {
  get_coefficients_from_zeros(1, &d, &e);
  assertNotEqual(call(a, b, c, d, e, 0), 0);
  assertEqual(call(a, b, c, d, e, 1), 0);
}

test(test_from_zeros_2) {
  get_coefficients_from_zeros(1, 2, &c, &d, &e);
  assertNotEqual(call(a, b, c, d, e, 0), 0);
  assertEqual(call(a, b, c, d, e, 1), 0);
  assertEqual(call(a, b, c, d, e, 2), 0);
  assertNotEqual(call(a, b, c, d, e, 3), 0);
}

test(test_from_zeros_3) {
  get_coefficients_from_zeros(1, 2, 3, &b, &c, &d, &e);
  assertNotEqual(call(a, b, c, d, e, 0), 0);  
  assertEqual(call(a, b, c, d, e, 1), 0);
  assertEqual(call(a, b, c, d, e, 2), 0);
  assertEqual(call(a, b, c, d, e, 3), 0);
  assertNotEqual(call(a, b, c, d, e, 4), 0);
}

test(test_from_zeros_3_extended) {
  get_coefficients_from_zeros(36, -33, 33, &b, &c, &d, &e);
  assertNotEqual(call(a, b, c, d, e, 0), 0);  
  assertEqual(call(a, b, c, d, e, 36), 0);
  assertEqual(call(a, b, c, d, e, -33), 0);
  assertEqual(call(a, b, c, d, e, -33), 0);
  assertEqual(call(a, b, c, d, e, -33), 0);
  assertEqual(call(a, b, c, d, e, 33), 0);
  assertNotEqual(call(a, b, c, d, e, 4), 0);
}

test(test_from_zeros_4) {
  get_coefficients_from_zeros(1, 2, 3, 4, &a, &b, &c, &d, &e);
  assertNotEqual(call(a, b, c, d, e, 0), 0);
  assertEqual(call(a, b, c, d, e, 1), 0);
  assertEqual(call(a, b, c, d, e, 2), 0);
  assertEqual(call(a, b, c, d, e, 3), 0);
  assertEqual(call(a, b, c, d, e, 4), 0);
  assertNotEqual(call(a, b, c, d, e, 5), 0); 
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}