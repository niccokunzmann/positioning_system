
#define TEST_APPROXIMATION_EPSILON 0.001

#include "positioning_system_test.h"

double dt1;
double dt2;
double dt3;

void compute_dt(double a, double b, double x, double y) {
    double u = sqrt(x*x + y*y);
    double w = sqrt(y*y + (b - x)*(b - x));
    double v = sqrt((a + y)*(a + y) + x*x);
     
    dt1 = v - u;
    dt2 = v - w;
    dt3 = u - w;
}

double x; 
double y;

void test_position(double x0, double y0, double a = 1., double b = 2.) {
  println5(" ----- Test x: ", x0, " y: ", y0, " ----- ");
  compute_dt(a, b, x0, y0);
  position(dt1, dt2, a, b, &x, &y);
  println6("{{test}} dt1, dt2, dt3 = ", dt1, ", ", dt2, ", ", dt3);
  assertApproximately(x, x0);
  assertApproximately(y, y0);
}

test(position_n_eq_0) {
  test_position(12, -0.5);
}

double x1;
double x2;

test(equation2_for_position) {
  solve_equation(0.03326345818211429, -0.06652691636422858, -3.9916149818513342, &x1, &x2);
  sort_numbers(&x1, &x2);
  assertApproximately(x1, -10.);
  assertApproximately(x2, 12.);
  
}

/*
test(position_r_eq_0_1) {
  test_position(1, 1);
}

test(position_r_eq_0_2) {
  test_position(1, 0);
}

test(position_r_eq_0_3) {
  test_position(1, -1);
}

test(position_r_eq_0_4) {
  test_position(0, 0);
}

test(position_r_eq_0_5) {
  test_position(1, -0.5);
}


test(position_1) {
  test_position(2, -1);
}

test(position_2) {
  test_position(100, -12);
}

test(position_3) {
  test_position(123.12312321321, -100);
}

test(position_4) {
  test_position(-333.213, -12);
}
*/
void setup() {
  Serial.begin(9600);
}

void loop() {
  Test::run();
}

