
#ifndef get_coefficients_hpp
#define get_coefficients_hpp

#include "positioning_system.h"

void get_coefficients_from_zeros(NumberArgument zero1, 
                                 NumberPointer d, NumberPointer e);
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, 
                                 NumberPointer c, NumberPointer d, NumberPointer e);
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberArgument zero3, 
                                 NumberPointer b, NumberPointer c, NumberPointer d, NumberPointer e);
void get_coefficients_from_zeros(NumberArgument zero1, NumberArgument zero2, NumberArgument zero3, NumberArgument zero4, 
                                 NumberPointer a, NumberPointer b, NumberPointer c, NumberPointer d, NumberPointer e);

#endif