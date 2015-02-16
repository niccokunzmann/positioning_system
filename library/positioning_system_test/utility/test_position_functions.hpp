
#ifndef test_position_functions_hpp
#define test_position_functions_hpp

#include "test_print.hpp"
#include "positioning_system.h"
#include "assertions.hpp"
#include "math.h"

extern double dt1;
extern double dt2;
extern double dt3;
extern double x; 
extern double y;
extern double x3;
extern double x4;
extern double x1;
extern double x2;

void compute_dt(double a, double b, double x, double y);
void test_position(double x0, double y0, double a = 1., double b = 2.);

#endif