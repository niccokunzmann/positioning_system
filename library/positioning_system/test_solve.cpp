
#include "test_solve.h"
#include "test_positioning_system.h"
#include "solve.h"

void test_from_zeros() {
  double a = 0;
  double b = 0;
  double c = 0;
  double d = 0;
  double e = 0;
  
  // 1 zero
  get_coefficients_from_zeros(1, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);
  assert_equals(call(a, b, c, d, e, 1), 0);
  
  // 2 zeros
  get_coefficients_from_zeros(1, 2, &c, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);
  assert_equals(call(a, b, c, d, e, 1), 0);
  assert_equals(call(a, b, c, d, e, 2), 0);
  assert_not_equals(call(a, b, c, d, e, 3), 0);

  // 3 zeros
  get_coefficients_from_zeros(1, 2, 3, &b, &c, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);  
  assert_equals(call(a, b, c, d, e, 1), 0);
  assert_equals(call(a, b, c, d, e, 2), 0);
  assert_equals(call(a, b, c, d, e, 3), 0);
  assert_not_equals(call(a, b, c, d, e, 4), 0);

  get_coefficients_from_zeros(36, -33, 33, &b, &c, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);  
  assert_equals(call(a, b, c, d, e, 36), 0);
  assert_equals(call(a, b, c, d, e, -33), 0);
  assert_equals(call(a, b, c, d, e, 33), 0);
  assert_not_equals(call(a, b, c, d, e, 4), 0);
  
  // 4 zeros
  get_coefficients_from_zeros(1, 2, 3, 4, &a, &b, &c, &d, &e);
  assert_not_equals(call(a, b, c, d, e, 0), 0);
  assert_equals(call(a, b, c, d, e, 1), 0);
  assert_equals(call(a, b, c, d, e, 2), 0);
  assert_equals(call(a, b, c, d, e, 3), 0);
  assert_equals(call(a, b, c, d, e, 4), 0);
  assert_not_equals(call(a, b, c, d, e, 5), 0); 
}

void test_epsilon() {
  assert_not_equals(get_epsilon(), 0);
  
  assert1(approximates(0.0001, 0.0001));
  assert1(approximates(1, 1));
  assert1(approximates(9000000000., 9000000000.));
  assert1(approximates(get_epsilon(), 0));
  
  assert1(!approximates(9000000000., 1));
  assert1(!approximates(1, 2));
}

void test_infinity() {
  assert_equals(get_infinity(), get_infinity() + 1);
  assert_equals(0 / get_infinity(), 0);
}

void test_nan() {
  assert_not_equals(get_not_a_number(), get_not_a_number() + 1);
  assert_not_equals(0 / get_not_a_number(), get_not_a_number());
  assert_not_equals(get_not_a_number() - get_not_a_number(), 0);
  assert_not_equals(get_not_a_number(), get_infinity());
  
  assert1(is_not_a_number(get_not_a_number()));
  assert1(!is_not_a_number(get_infinity()));
  assert1(!is_not_a_number(23432432.0));
}

void test_solve_0() {
  double zero1;

  solve(0, &zero1);
  assert_equals(zero1, 0);

  solve(3, &zero1);
  assert1(is_not_a_number(zero1));
}

void test_solve_1() {
  double d = 0;
  double e = 0;
  double zero1;
  
  get_coefficients_from_zeros(11, &d, &e);
  solve(d, e, &zero1);
  assert_equals(zero1, 11);

  get_coefficients_from_zeros(12, &d, &e);
  solve(d, e, &zero1);
  assert_approximates(zero1, 12);
  
  // test constant solving
  solve(0, 1, &zero1);
  assert1(is_not_a_number(zero1));
}

void sort_zeros(double *zero1, double *zero2) {
  if (*zero1 > *zero2) {
    *zero1 += *zero2;
    *zero2 = *zero1 - *zero2;
    *zero1 = *zero1 - *zero2;
  }
}


void test_solve_2() {
  double c = 0;
  double d = 0;
  double e = 0;
  double zero1;
  double zero2;
  
  get_coefficients_from_zeros(22, 24, &c, &d, &e);
  solve(c, d, e, &zero1, &zero2);
  sort_zeros(&zero1, &zero2);
  assert_equals(zero1, 22);
  assert_equals(zero2, 24);

  get_coefficients_from_zeros(22, 22, &c, &d, &e);
  solve(c, d, e, &zero1, &zero2);
  sort_zeros(&zero1, &zero2);
  assert_equals(zero1, 22);
  assert1(is_not_a_number(zero2));

  solve(1, 0, 1, &zero1, &zero2);
  assert1(is_not_a_number(zero1));
  assert1(is_not_a_number(zero2));
  
  // test linear solving
  get_coefficients_from_zeros(22, &d, &e);
  solve(0, d, e, &zero1, &zero2);
  assert_equals(zero1, 22);
  assert1(is_not_a_number(zero2));

  // test constant solving
  solve(0, 0, 2, &zero1, &zero2);
  assert1(is_not_a_number(zero1));
  assert1(is_not_a_number(zero2));
}

void sort_zeros(double *zero1, double *zero2, double *zero3) {
  // bubblesort
  sort_zeros(zero1, zero2);
  sort_zeros(zero2, zero3);
  sort_zeros(zero1, zero2);
}

void test_curt() {
  assert_equals(curt(0), 0);
  assert_equals(curt(1), 1);
  assert_equals(curt(-1), -1);
  assert_equals(curt(-8), -2);
}

void test_solve_3() {
  double b = 0;
  double c = 0;
  double d = 0;
  double e = 0;
  double zero1;
  double zero2;
  double zero3;
  
  // test cubic solving
  set_epsilon(0.0003);

  get_coefficients_from_zeros(36, 311, 33, &b, &c, &d, &e);
  solve(b, c, d, e, &zero1, &zero2, &zero3);
  sort_zeros(&zero1, &zero2, &zero3);
  assert_approximates(zero1, 33);
  assert_approximates(zero2, 36);
  assert_approximates(zero3, 311);
 
  set_epsilon(get_default_epsilon());

  get_coefficients_from_zeros(31, 31, 37, &b, &c, &d, &e);
  solve(b, c, d, e, &zero1, &zero2, &zero3);
  sort_zeros(&zero1, &zero2);
  assert_equals(zero1, 31);
  assert_equals(zero2, 37);
  assert1(is_not_a_number(zero3));

  get_coefficients_from_zeros(30, 30, 30, &b, &c, &d, &e);
  solve(b, c, d, e, &zero1, &zero2, &zero3);
  assert_equals(zero1, 30);
  assert1(is_not_a_number(zero2));
  assert1(is_not_a_number(zero3));

  set_epsilon(0.00002);
  
  solve(1, 0, 1, 30, &zero1, &zero2, &zero3); // one solution only
  assert_approximates(zero1, -3);
  assert1(is_not_a_number(zero2));
  assert1(is_not_a_number(zero3));

  set_epsilon(get_default_epsilon());

  // test quadratic solving
  get_coefficients_from_zeros(32, 34, &c, &d, &e);
  solve(0, c, d, e, &zero1, &zero2, &zero3);
  sort_zeros(&zero1, &zero2);
  assert_equals(zero1, 32);
  assert_equals(zero2, 34);
  assert1(is_not_a_number(zero3));

  get_coefficients_from_zeros(38, 38, &c, &d, &e);
  solve(0, c, d, e, &zero1, &zero2, &zero3);
  sort_zeros(&zero1, &zero2);
  assert_equals(zero1, 38);
  assert1(is_not_a_number(zero2));
  assert1(is_not_a_number(zero3));

  solve(0, 3, 0, 3, &zero1, &zero2, &zero3);
  assert1(is_not_a_number(zero1));
  assert1(is_not_a_number(zero2));
  assert1(is_not_a_number(zero3));
  
  // test linear solving
  get_coefficients_from_zeros(399, &d, &e);
  solve(0, 0, d, e, &zero1, &zero2, &zero3);
  assert_equals(zero1, 399);
  assert1(is_not_a_number(zero2));
  assert1(is_not_a_number(zero3));

  // test constant solving
  solve(0, 0, 0, 3, &zero1, &zero2, &zero3);
  assert1(is_not_a_number(zero1));
  assert1(is_not_a_number(zero2));
  assert1(is_not_a_number(zero3));

}

/*void test_solve_2() {
  double a = 0;
  double b = 0;
  double c = 0;
  double d = 0;
  double e = 0;
  double zero1;
  double zero2;
  double zero3;
  double zero4;
  
  get_coefficients_from_zeros(3, &d, &e);
  solve(d, e, &zero1);
  assert_equals(zero1, 3);

  get_coefficients_from_zeros(0, &d, &e);
  solve(d, e, &zero1);
  assert_approximates(zero1, 0);
}*/


void test_solve() {
  test_from_zeros();
  test_epsilon();
  test_nan();
  test_infinity();
  test_solve_0();
  test_solve_1();
  test_solve_2();
  test_curt();
  test_solve_3();
}