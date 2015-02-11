
#ifndef approximation_hpp
#define approximation_hpp

#include "numbers.hpp"

bool approximates(NumberArgument a, NumberArgument b);
bool approximates(NumberArgument a, NumberArgument b, NumberArgument epsilon);
Number get_epsilon();
Number get_default_epsilon();
void set_epsilon(NumberArgument new_epsilon);

#endif