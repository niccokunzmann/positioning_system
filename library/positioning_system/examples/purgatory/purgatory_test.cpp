void test_refine_zero() {
  double a = 0;
  double b = 0;
  double c = 0;
  double d = 0;
  double e = 0;
  double zero = 0;

  get_coefficients_from_zeros(88, 8, 888, &b, &c, &d, &e);
  
  zero = refine_zero(a, b, c, d, e, 40, 400);
//  test_println("zero: ", zero);
//  test_println("call: ", call(a, b, c, d, e, zero));
  assert_equals(zero, 88);
  
  zero = refine_zero(a, b, c, d, e, -40, 40);
//  test_println("zero: ", zero);
//  test_println("call: ", call(a, b, c, d, e, zero));
  assert_equals(zero, 8);
  
  zero = refine_zero(a, b, c, d, e, 400, 1200);
//  test_println("zero: ", zero);
//  test_println("call: ", call(a, b, c, d, e, zero));
  assert_equals(zero, 888);
}