
#include "test_solve.h"
#include "test.h"
#include "solve.h"

void test_coefficients() {
  Coefficients c;
  Serial.println("a3");
  c = get_coefficients_from_zeros();
  Serial.println("a4");
  Serial.print(call(c, 0));
  /*assert_equals(call(c, 0), 0);
  assert_equals(call(c, 1), 0);
  
  c = get_coefficients_from_zeros(1);
  assert_not_equals(call(c, 0), 0);
  assert_equals(call(c, 1), 0);

  c = get_coefficients_from_zeros(1, 2);
  assert_not_equals(call(c, 0), 0);
  assert_equals(call(c, 1), 0);
  assert_equals(call(c, 2), 0);
  assert_not_equals(call(c, 3), 0);

  c = get_coefficients_from_zeros(1, 2, 3);
  assert_not_equals(call(c, 0), 0);
  assert_equals(call(c, 1), 0);
  assert_equals(call(c, 2), 0);
  assert_equals(call(c, 3), 0);
  assert_not_equals(call(c, 4), 0);
  
  c = get_coefficients_from_zeros(1, 2, 3, 4);
  assert_not_equals(call(c, 0), 0);
  assert_equals(call(c, 1), 0);
  assert_equals(call(c, 2), 0);
  assert_equals(call(c, 3), 0);
  assert_equals(call(c, 4), 0);
  assert_not_equals(call(c, 5), 0);
  */
};