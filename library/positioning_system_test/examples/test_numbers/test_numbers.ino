
#include "positioning_system_test.h"

test(infinity) {
  assertEqual(get_infinity(), get_infinity() + 1);
  assertEqual(0 / get_infinity(), 0);
  
  assertTrue(is_infinity(+get_infinity()));
  assertTrue(is_infinity(-get_infinity()));
  
  assertFalse(is_infinity(1));
  assertFalse(is_infinity(get_not_a_number()));
}

test(not_a_number) {
  assertNotEqual(get_not_a_number(), get_not_a_number() + 1);
  assertNotEqual(0 / get_not_a_number(), get_not_a_number());
  assertNotEqual(get_not_a_number(), get_infinity());
  
  assertTrue(is_not_a_number(get_not_a_number()));
  assertTrue(is_not_a_number(get_not_a_number() + 1));
  
  assertFalse(is_not_a_number(get_infinity()));
  assertFalse(is_not_a_number(23432432.0));
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}