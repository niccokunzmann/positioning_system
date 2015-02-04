

#ifndef solve_h
#define solve_h

#include "Arduino.h"
#include "hpa.h"

typedef HPA::xreal       Number;
typedef const HPA::xreal NumberArgument;
typedef HPA::xreal*      NumberPointer;


// a*x^4 + b * x^3 + c * x^2 + d * x + e

void get_coefficients_from_zeros(NumberArgument zero1, NumberPointer d, NumberPointer e);
/*
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberPointer c, NumberPointer d, NumberPointer e);
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberArgument zero3, NumberPointer b, NumberPointer c, NumberPointer d, NumberPointer e);
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberArgument zero3, NumberArgument zero4, NumberPointer a, NumberPointer b, NumberPointer c, NumberPointer d, NumberPointer e);
*/
Number call(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, int x);
Number call(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, double x);
Number call(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, NumberArgument x);
/*
void print_coefficients_to_serial(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e);

Number get_epsilon();
void set_epsilon(NumberArgument epsilon);
Number get_default_epsilon();
boolean approximates(NumberArgument a, NumberArgument b);
boolean approximates(NumberArgument a, NumberArgument b, NumberArgument epsilon);

void solve(NumberArgument e, NumberPointer zero1);
void solve(NumberArgument d, NumberArgument e, NumberPointer zero1);
void solve(NumberArgument c, NumberArgument d, NumberArgument e, NumberPointer zero1, NumberPointer zero2);
void solve(NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, NumberPointer zero1, NumberPointer zero2, NumberPointer zero3);
void solve(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4);

Number get_infinity();
Number get_not_a_number();
boolean is_not_a_number(NumberArgument number);

Number nth_root(NumberArgument x, int n);
Number curt_1(NumberArgument x);
Number curt_2(NumberArgument x);
Number curt_3(NumberArgument x);
Number curt(NumberArgument x);

void sort_numbers(NumberPointer a, NumberPointer b);
void sort_numbers(NumberPointer a, NumberPointer b, NumberPointer c);
void sort_numbers(NumberPointer a, NumberPointer b, NumberPointer c, NumberPointer d);

Number newton(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, NumberArgument x, NumberArgument epsilon);
Number newton(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, NumberArgument x, NumberArgument epsilon, long maximum_iterations);

void refine_zeros_of_order_3_with_3_solutions(NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, NumberPointer zero1, NumberPointer zero2, NumberPointer zero3);
Number refine_zero(NumberArgument a, NumberArgument b, NumberArgument c, NumberArgument d, NumberArgument e, NumberArgument upper_bound, NumberArgument lower_bound);
*/
#endif