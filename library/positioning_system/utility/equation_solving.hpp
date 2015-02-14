
#ifndef equation_solving_hpp
#define equation_solving_hpp

#include "hpaconf.h"
#include "hpa.h"
#include "numbers.hpp"

void solve_equation(NumberArgument e, 
                    NumberPointer zero1);
void solve_equation(NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1);
void solve_equation(NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2);
void solve_equation(NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3);
void solve_equation(NumberArgument a,    NumberArgument b,    NumberArgument c,    NumberArgument d,    NumberArgument e, 
                    NumberPointer zero1, NumberPointer zero2, NumberPointer zero3, NumberPointer zero4);

#endif