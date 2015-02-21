
#include "test_position_functions.hpp"

double dt1;
double dt2;
double x; 
double y;
double x3;
double x4;
double x1;
double x2;

void compute_dt(double a, double b, double x, double y) {
  double CP = sqrt(x*x + y*y);
  double AP = sqrt(y*y + (a - x)*(a - x));
  double BP = sqrt((b + y)*(b + y) + x*x);
   
  dt1 = BP - CP;
  dt2 = BP - AP;
}


void test_position(double x0, double y0, double a, double b) {
  //println5(" ----- Test x: ", x0, " y: ", y0, " ----- ");
  compute_dt(a, b, x0, y0);
  position(dt1, dt2, a, b, &x, &y);
  //println6("{{test}} dt1, dt2 = ", dt1, ", ", dt2);
  assertApproximately(x, x0);
  assertApproximately(y, y0);
}
