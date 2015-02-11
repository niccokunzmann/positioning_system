
#ifndef numbers_hpp
#define numbers_hpp

typedef double       Number;
typedef const double NumberArgument;
typedef double*      NumberPointer;

Number get_infinity();
int is_infinity(NumberArgument a_number);
Number get_not_a_number();
int is_not_a_number(NumberArgument a_number);

#endif