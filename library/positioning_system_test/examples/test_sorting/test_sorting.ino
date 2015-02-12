
#include "positioning_system_test.h"

Number a;
Number b;
Number c;
Number n;

void setup_numbers() {
  a = 1;
  b = 2;
  c = 3;
  n = get_not_a_number();
}


test(sort_2_numbers_sorted) {
  setup_numbers();
  sort_numbers(&a, &b);
  assertEqual(a, 1);
  assertEqual(b, 2);
}

test(sort_2_numbers_reversed) {
  setup_numbers();
  sort_numbers(&b, &a);
  assertEqual(b, 1);
  assertEqual(a, 2);
}

test(sort_2_numbers_nan) {
  setup_numbers();
  sort_numbers(&b, &n);
  assertEqual(b, 2);
  assertTrue(is_not_a_number(n));
}

test(sort_2_numbers_nan_reversed) {
  setup_numbers();
  sort_numbers(&n, &b);
  assertEqual(n, 2);
  assertTrue(is_not_a_number(b));
}

test(sort_3_numbers) {
  setup_numbers();
  sort_numbers(&a, &b, &c);
  assertEqual(a, 1);
  assertEqual(b, 2);
  assertEqual(c, 3);
}

test(sort_3_numbers_with_nan) {
  setup_numbers();
  sort_numbers(&b, &a, &n);
  assertEqual(b, 1);
  assertEqual(a, 2);
  assertTrue(is_not_a_number(n));
}

test(sort_3_numbers_with_nan_shuffled) {
  setup_numbers();
  sort_numbers(&n, &b, &a);
  assertEqual(n, 1);
  assertEqual(b, 2);
  assertTrue(is_not_a_number(a));
}

test(sort_3_numbers_with_2_nan) {
  setup_numbers();
  c = get_not_a_number();
  sort_numbers(&n, &b, &c);
  assertEqual(n, 2);
  assertTrue(is_not_a_number(b));
  assertTrue(is_not_a_number(c));
}

test(sort_4_numbers) {
  setup_numbers();
  sort_numbers(&n, &b, &a, &c);
  assertEqual(n, 1);
  assertEqual(b, 2);
  assertEqual(a, 3);
  assertTrue(is_not_a_number(c));
  
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}