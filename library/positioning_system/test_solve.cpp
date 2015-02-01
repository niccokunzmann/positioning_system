
#include "test_solve.h"
#include "test_positioning_system.h"
#include "solve.h"

void test_from_zeros() {
  double a = 0;
  double b = 0;
  double c = 0;
  double d = 0;
  double e = 0;
  test_println("a3");
  
  get_coefficients_from_zeros(1, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);
  assert_equals(call(a, b, c, d, e, 1), 0);
  
  get_coefficients_from_zeros(1, 2, &c, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);
  assert_equals(call(a, b, c, d, e, 1), 0);
  assert_equals(call(a, b, c, d, e, 2), 0);
  assert_not_equals(call(a, b, c, d, e, 3), 0);

  get_coefficients_from_zeros(1, 2, 3, &b, &c, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);
//  test_println();
//  print_coefficients_to_serial(a, b, c, d, e);
//  test_println();
//  test_println("call(a, b, c, d, e, 1):", call(a, b, c, d, e, 1));
  
  assert_equals(call(a, b, c, d, e, 1), 0);
  assert_equals(call(a, b, c, d, e, 2), 0);
  assert_equals(call(a, b, c, d, e, 3), 0);
  assert_not_equals(call(a, b, c, d, e, 4), 0);
  
  get_coefficients_from_zeros(1, 2, 3, 4, &a, &b, &c, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);
  assert_equals(call(a, b, c, d, e, 1), 0);
  assert_equals(call(a, b, c, d, e, 2), 0);
  assert_equals(call(a, b, c, d, e, 3), 0);
  assert_equals(call(a, b, c, d, e, 4), 0);
  assert_not_equals(call(a, b, c, d, e, 5), 0); 
}

  
void test_coefficients() {
  test_from_zeros();
};