
#include "test_position_functions.hpp"

double dt1;
double dt2;
double dt3;
double x; 
double y;
double x3;
double x4;
double x1;
double x2;

void compute_dt(double a, double b, double x, double y) {
    double u = sqrt(x*x + y*y);
    double w = sqrt(y*y + (b - x)*(b - x));
    double v = sqrt((a + y)*(a + y) + x*x);
     
    dt1 = v - u;
    dt2 = v - w;
    dt3 = u - w;
}


void test_position(double x0, double y0, double a, double b) {
  //println5(" ----- Test x: ", x0, " y: ", y0, " ----- ");
  compute_dt(a, b, x0, y0);
  position(dt1, dt2, a, b, &x, &y);
  //println6("{{test}} dt1, dt2, dt3 = ", dt1, ", ", dt2, ", ", dt3);
  assertApproximately(x, x0);
  assertApproximately(y, y0);
}
